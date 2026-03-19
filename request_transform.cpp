#include "pch.h"
#include "request_transform.h"
#include <bcrypt.h>
#include <map>
#include <sstream>
#include <vector>
#include <wininet.h>
#pragma comment(lib, "bcrypt.lib")

static const char* ENCRYPT_FIELDS[] = { "password", "passwd", "pass", "passnew" };

struct RequestData {
    std::string action;
    std::string query;
    char* bodyBuf;   // heap-allocated, kept alive for async send
    DWORD       bodyLen;
};

static std::map<HINTERNET, RequestData> g_requests;
static CRITICAL_SECTION g_cs;

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

static std::string BuildJson(const std::string& action, const std::string& query)
{
    std::string params;
    bool first = true;

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
            if (!first) params += ",";
            first = false;
            params += "\"" + JsonEscape(key) + "\":\"" + JsonEscape(outVal) + "\"";
        }
    }

    return "[{\"game\":\"tm1\",\"request\":\"" + JsonEscape(action)
        + "\",\"params\":{" + params + "}}]";
}

void TransformInit()
{
    InitializeCriticalSection(&g_cs);
}

void StoreRequestData(HINTERNET hRequest, const std::string& action, const std::string& query)
{
    EnterCriticalSection(&g_cs);
    RequestData& rd = g_requests[hRequest];
    rd.action = action;
    rd.query = query;
    rd.bodyBuf = nullptr;
    rd.bodyLen = 0;
    LeaveCriticalSection(&g_cs);
}

bool ConsumeJsonBody(HINTERNET hRequest, char** outBuf, DWORD* outLen)
{
    EnterCriticalSection(&g_cs);
    auto it = g_requests.find(hRequest);
    if (it == g_requests.end()) {
        LeaveCriticalSection(&g_cs);
        return false;
    }

    std::string action = it->second.action;
    std::string query = it->second.query;

    // Free any previous buffer on this handle
    if (it->second.bodyBuf) {
        delete[] it->second.bodyBuf;
        it->second.bodyBuf = nullptr;
    }

    std::string json = BuildJson(action, query);

    // Heap-allocate so the buffer outlives our stack frame (async send)
    DWORD len = (DWORD)json.size();
    char* buf = new char[len];
    memcpy(buf, json.c_str(), len);

    it->second.bodyBuf = buf;
    it->second.bodyLen = len;

    *outBuf = buf;
    *outLen = len;

    LeaveCriticalSection(&g_cs);
    return true;
}

void ClearRequestData(HINTERNET hRequest)
{
    EnterCriticalSection(&g_cs);
    auto it = g_requests.find(hRequest);
    if (it != g_requests.end()) {
        if (it->second.bodyBuf) {
            delete[] it->second.bodyBuf;
        }
        g_requests.erase(it);
    }
    LeaveCriticalSection(&g_cs);
}

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
    auto it = g_requests.find(hRequest);
    if (it != g_requests.end())
        it->second.query = query;
    LeaveCriticalSection(&g_cs);
}