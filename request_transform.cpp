#include "pch.h"
#include "request_transform.h"
#include <bcrypt.h>
#include <map>
#include <sstream>
#include <vector>
#include <wininet.h>
#pragma comment(lib, "bcrypt.lib")

// Fields that get SHA-256 hashed instead of sent plain
static const char* ENCRYPT_FIELDS[] = { "password", "passwd", "pass", "passnew" };

// -----------------------------------------------------------------------
// Internal state — action name + query string per request handle
// -----------------------------------------------------------------------
struct RequestData {
    std::string action; // e.g. "subscribe"
    std::string query;  // raw query string e.g. "login=foo&password=bar"
};

static std::map<HINTERNET, RequestData> g_requests;
static CRITICAL_SECTION g_cs;

// -----------------------------------------------------------------------
// Helpers
// -----------------------------------------------------------------------
static std::string SHA256Hex(const std::string& input)
{
    BCRYPT_ALG_HANDLE  hAlg = nullptr;
    BCRYPT_HASH_HANDLE hHash = nullptr;
    std::string result;

    if (!BCRYPT_SUCCESS(BCryptOpenAlgorithmProvider(
        &hAlg, BCRYPT_SHA256_ALGORITHM, nullptr, 0)))
        return input;

    DWORD hashLen = 0, cbResult = 0;
    BCryptGetProperty(hAlg, BCRYPT_HASH_LENGTH,
        (PUCHAR)&hashLen, sizeof(DWORD), &cbResult, 0);

    std::vector<BYTE> hash(hashLen);
    BCryptCreateHash(hAlg, &hHash, nullptr, 0, nullptr, 0, 0);
    BCryptHashData(hHash, (PUCHAR)input.c_str(), (ULONG)input.size(), 0);
    BCryptFinishHash(hHash, hash.data(), hashLen, 0);
    BCryptDestroyHash(hHash);
    BCryptCloseAlgorithmProvider(hAlg, 0);

    char hex[3];
    for (size_t i = 0; i < hash.size(); i++) {
        snprintf(hex, sizeof(hex), "%02x", hash[i]);
        result += hex;
    }
    return result;
}

static std::string UrlDecode(const std::string& s)
{
    std::string out;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '+') {
            out += ' ';
        }
        else if (s[i] == '%' && i + 2 < s.size()) {
            char hex[3] = { s[i + 1], s[i + 2], '\0' };
            out += (char)strtol(hex, nullptr, 16);
            i += 2;
        }
        else {
            out += s[i];
        }
    }
    return out;
}

static bool ShouldEncrypt(const std::string& key)
{
    for (size_t i = 0; i < sizeof(ENCRYPT_FIELDS) / sizeof(ENCRYPT_FIELDS[0]); i++)
        if (_stricmp(key.c_str(), ENCRYPT_FIELDS[i]) == 0) return true;
    return false;
}

static std::string JsonEscape(const std::string& s)
{
    std::string out;
    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        switch (c) {
        case '"':  out += "\\\""; break;
        case '\\': out += "\\\\"; break;
        case '\n': out += "\\n";  break;
        case '\r': out += "\\r";  break;
        case '\t': out += "\\t";  break;
        default:   out += c;      break;
        }
    }
    return out;
}

// "/online_game/subscribe.php" -> "subscribe"
static std::string ExtractAction(const std::string& path)
{
    auto slash = path.rfind('/');
    std::string name = (slash != std::string::npos) ? path.substr(slash + 1) : path;
    auto dot = name.rfind('.');
    if (dot != std::string::npos) name = name.substr(0, dot);
    return name;
}

static std::string BuildJson(const std::string& action, const std::string& query)
{
    std::string json = "{";

    // Fixed fields always first
    json += "\"game\":\"tm1\"";
    json += ",\"request\":\"" + JsonEscape(action) + "\"";

    // Parse and append query params
    if (!query.empty()) {
        std::istringstream ss(query);
        std::string pair;
        while (std::getline(ss, pair, '&')) {
            if (pair.empty()) continue;
            auto eq = pair.find('=');
            if (eq == std::string::npos) continue;

            std::string key = UrlDecode(pair.substr(0, eq));
            std::string val = UrlDecode(pair.substr(eq + 1));

            if (key.empty()) continue;

            std::string outVal = ShouldEncrypt(key) ? SHA256Hex(val) : val;
            json += ",\"" + JsonEscape(key) + "\":\"" + JsonEscape(outVal) + "\"";
        }
    }

    json += "}";
    return json;
}

// -----------------------------------------------------------------------
// Public API
// -----------------------------------------------------------------------
void TransformInit()
{
    InitializeCriticalSection(&g_cs);
}

std::string RewriteToSingleEndpoint(const char* objectName)
{
    if (!objectName) return "/request";

    std::string full(objectName);
    std::string path = full;
    auto qpos = full.find('?');
    if (qpos != std::string::npos)
        path = full.substr(0, qpos);

    // Only rewrite known game API paths — leave anything else alone
    if (path.find("/online_game/") != std::string::npos)
        return "/request";

    return path; // not a game API call, pass through unchanged
}

void StoreRequestData(HINTERNET hRequest, const std::string& action, const std::string& query)
{
    EnterCriticalSection(&g_cs);
    RequestData& rd = g_requests[hRequest];
    rd.action = action;
    rd.query = query;
    LeaveCriticalSection(&g_cs);
}

bool ConsumeJsonBody(HINTERNET hRequest, std::string& outJson)
{
    EnterCriticalSection(&g_cs);
    std::map<HINTERNET, RequestData>::iterator it = g_requests.find(hRequest);
    if (it == g_requests.end()) {
        LeaveCriticalSection(&g_cs);
        return false;
    }
    std::string action = it->second.action;
    std::string query = it->second.query;
    g_requests.erase(it);
    LeaveCriticalSection(&g_cs);

    outJson = BuildJson(action, query);
    return true;
}

void ClearRequestData(HINTERNET hRequest)
{
    EnterCriticalSection(&g_cs);
    g_requests.erase(hRequest);
    LeaveCriticalSection(&g_cs);
}

// request_transform.cpp — add these two
bool HasStoredAction(HINTERNET hRequest)
{
    EnterCriticalSection(&g_cs);
    bool found = g_requests.find(hRequest) != g_requests.end();
    LeaveCriticalSection(&g_cs);
    return found;
}

void UpdateStoredQuery(HINTERNET hRequest, const std::string& query)
{
    EnterCriticalSection(&g_cs);
    std::map<HINTERNET, RequestData>::iterator it = g_requests.find(hRequest);
    if (it != g_requests.end())
        it->second.query = query;
    LeaveCriticalSection(&g_cs);
}