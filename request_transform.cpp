#include "pch.h"
#include "request_transform.h"
#include <bcrypt.h>
#include <map>
#include <sstream>
#include <vector>
#pragma comment(lib, "bcrypt.lib")

// -----------------------------------------------------------------------
// PATH REWRITE RULES
// Add as many as you need — exact match on the path part before '?'
// -----------------------------------------------------------------------
static const struct { const char* from; const char* to; } PATH_RULES[] =
{
    { "/online_game/subscribe.php",      "/one/game/subscribe"    },
    { "/online_game/unsubscribe.php",    "/one/game/unsubscribe"  },
    { "/online_game/login.php",          "/one/game/login"        },
    { "/online_game/get_ladder_zone.php","/one/game/ladder/zones" },
    // add more here as you discover them
};

// -----------------------------------------------------------------------
// FIELDS TO ENCRYPT  (SHA-256 hex, so server just stores/compares hashes)
// -----------------------------------------------------------------------
static const char* ENCRYPT_FIELDS[] = { "password", "passwd", "pass" };

// -----------------------------------------------------------------------
// Internal state
// -----------------------------------------------------------------------
static std::map<HINTERNET, std::string> g_queryStrings;
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
        return input; // crypto unavailable — return plaintext as fallback

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
    for (BYTE b : hash) {
        snprintf(hex, sizeof(hex), "%02x", b);
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

static std::map<std::string, std::string> ParseQuery(const std::string& query)
{
    std::map<std::string, std::string> params;
    std::istringstream ss(query);
    std::string pair;
    while (std::getline(ss, pair, '&')) {
        auto eq = pair.find('=');
        if (eq != std::string::npos) {
            std::string key = UrlDecode(pair.substr(0, eq));
            std::string val = UrlDecode(pair.substr(eq + 1));
            params[key] = val;
        }
    }
    return params;
}

static std::string JsonEscape(const std::string& s)
{
    std::string out;
    for (char c : s) {
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

static bool ShouldEncrypt(const std::string& key)
{
    for (auto& f : ENCRYPT_FIELDS)
        if (_stricmp(key.c_str(), f) == 0) return true;
    return false;
}

static std::string BuildJson(const std::map<std::string, std::string>& params)
{
    std::string json = "{";
    bool first = true;
    for (std::map<std::string, std::string>::const_iterator it = params.begin(); it != params.end(); ++it) {
        if (!first) json += ",";
        first = false;
        const std::string& key = it->first;
        const std::string& val = it->second;
        std::string outVal = ShouldEncrypt(key) ? SHA256Hex(val) : val;
        json += "\"" + JsonEscape(key) + "\":\"" + JsonEscape(outVal) + "\"";
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

std::string RewritePath(const char* objectName, std::string& outQuery)
{
    outQuery.clear();
    if (!objectName) return "";

    std::string full(objectName);
    std::string path = full;

    auto qpos = full.find('?');
    if (qpos != std::string::npos) {
        path = full.substr(0, qpos);
        outQuery = full.substr(qpos + 1);
    }

    for (auto& rule : PATH_RULES)
        if (_stricmp(path.c_str(), rule.from) == 0)
            return rule.to;

    return path; // no rule matched — still strip the query string
}

void StoreQuery(HINTERNET hRequest, const std::string& query)
{
    if (query.empty()) return;
    EnterCriticalSection(&g_cs);
    g_queryStrings[hRequest] = query;
    LeaveCriticalSection(&g_cs);
}

std::string ConsumeJsonBody(HINTERNET hRequest)
{
    EnterCriticalSection(&g_cs);
    auto it = g_queryStrings.find(hRequest);
    std::string query;
    if (it != g_queryStrings.end()) {
        query = it->second;
        g_queryStrings.erase(it);
    }
    LeaveCriticalSection(&g_cs);

    if (query.empty()) return "";
    return BuildJson(ParseQuery(query));
}

void ClearRequestData(HINTERNET hRequest)
{
    EnterCriticalSection(&g_cs);
    g_queryStrings.erase(hRequest);
    LeaveCriticalSection(&g_cs);
}