#include "pch.h"
#include "proxy_exports.h"
#include "request_transform.h"
#include <windows.h>
#include <wininet.h>
#include "MinHook.h"
#pragma comment(lib, "wininet.lib")

#define TARGET_HOST  "www.trackmania.com"
#define REPLACE_HOST "tm1.ms.trackmania.pt"

typedef HINTERNET(WINAPI* PFN_InternetConnectA)(HINTERNET, LPCSTR, INTERNET_PORT, LPCSTR, LPCSTR, DWORD, DWORD, DWORD_PTR);
typedef HINTERNET(WINAPI* PFN_HttpOpenRequestA)(HINTERNET, LPCSTR, LPCSTR, LPCSTR, LPCSTR, LPCSTR*, DWORD, DWORD_PTR);
typedef BOOL(WINAPI* PFN_HttpSendRequestA)(HINTERNET, LPCSTR, DWORD, LPVOID, DWORD);
typedef BOOL(WINAPI* PFN_InternetCloseHandle)(HINTERNET);

PFN_InternetConnectA    fpInternetConnectA = nullptr;
PFN_HttpOpenRequestA    fpHttpOpenRequestA = nullptr;
PFN_HttpSendRequestA    fpHttpSendRequestA = nullptr;
PFN_InternetCloseHandle fpInternetCloseHandle = nullptr;

static void DebugLog(const char* fmt, ...)
{
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    char* slash = strrchr(path, '\\');
    if (slash) *(slash + 1) = '\0';
    strcat_s(path, "tm_debug.txt");

    FILE* f = nullptr;
    fopen_s(&f, path, "a");
    if (!f) return;
    va_list args;
    va_start(args, fmt);
    vfprintf(f, fmt, args);
    va_end(args);
    fclose(f);
}

HINTERNET WINAPI Hook_InternetConnectA(
    HINTERNET hInternet, LPCSTR lpszServerName,
    INTERNET_PORT nServerPort, LPCSTR lpszUserName,
    LPCSTR lpszPassword, DWORD dwService,
    DWORD dwFlags, DWORD_PTR dwContext)
{
    if (lpszServerName && _stricmp(lpszServerName, TARGET_HOST) == 0) {
        lpszServerName = REPLACE_HOST;
        nServerPort = INTERNET_DEFAULT_HTTPS_PORT;
    }
    return fpInternetConnectA(hInternet, lpszServerName, nServerPort,
        lpszUserName, lpszPassword, dwService, dwFlags, dwContext);
}

HINTERNET WINAPI Hook_HttpOpenRequestA(
    HINTERNET hConnect, LPCSTR lpszVerb, LPCSTR lpszObjectName,
    LPCSTR lpszVersion, LPCSTR lpszReferrer,
    LPCSTR* lplpszAcceptTypes, DWORD dwFlags, DWORD_PTR dwContext)
{
    dwFlags |= INTERNET_FLAG_SECURE;
    dwFlags |= INTERNET_FLAG_IGNORE_CERT_CN_INVALID;
    dwFlags |= INTERNET_FLAG_IGNORE_CERT_DATE_INVALID;

    DebugLog("HttpOpenRequestA verb=[%s] path=[%s]\n",
        lpszVerb ? lpszVerb : "NULL",
        lpszObjectName ? lpszObjectName : "NULL");

    const char* verbToUse = lpszVerb;
    std::string newPath;
    std::string action;
    std::string query;

    if (lpszObjectName) {
        std::string full(lpszObjectName);
        auto qpos = full.find('?');
        std::string path = (qpos != std::string::npos) ? full.substr(0, qpos) : full;
        query = (qpos != std::string::npos) ? full.substr(qpos + 1) : "";

        std::string pathLower = path;
        for (size_t i = 0; i < pathLower.size(); i++)
            pathLower[i] = (char)tolower((unsigned char)pathLower[i]);

        if (pathLower.find("online_game/") != std::string::npos) {
            auto slash = path.rfind('/');
            std::string filename = (slash != std::string::npos) ? path.substr(slash + 1) : path;
            auto dot = filename.rfind('.');
            action = (dot != std::string::npos) ? filename.substr(0, dot) : filename;
            newPath = "/request";
            verbToUse = "POST";
        }
        else {
            newPath = path;
            query.clear();
        }
    }

    HINTERNET hReq = fpHttpOpenRequestA(hConnect, verbToUse, newPath.c_str(),
        lpszVersion, lpszReferrer, lplpszAcceptTypes, dwFlags, dwContext);

    if (hReq && !action.empty())
        StoreRequestData(hReq, action, query);

    return hReq;
}

BOOL WINAPI Hook_HttpSendRequestA(
    HINTERNET hRequest, LPCSTR lpszHeaders, DWORD dwHeadersLength,
    LPVOID lpOptional, DWORD dwOptionalLength)
{
    char* bodyBuf = nullptr;
    DWORD  bodyLen = 0;

    if (!ConsumeJsonBody(hRequest, &bodyBuf, &bodyLen)) {
        return fpHttpSendRequestA(hRequest, lpszHeaders, dwHeadersLength,
            lpOptional, dwOptionalLength);
    }

    DebugLog("Sending JSON [%.*s]\n", (int)bodyLen, bodyBuf);

    // Set headers — bodyBuf is heap-allocated and stays alive for the async send
    char clHeader[128];
    snprintf(clHeader, sizeof(clHeader),
        "Content-Type: application/json\r\nContent-Length: %lu\r\n", bodyLen);

    HttpAddRequestHeadersA(hRequest, clHeader, (DWORD)strlen(clHeader),
        HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD);

    return fpHttpSendRequestA(hRequest,
        nullptr, 0,
        (LPVOID)bodyBuf, bodyLen);
    // bodyBuf is freed in ClearRequestData when the handle is closed
}

BOOL WINAPI Hook_InternetCloseHandle(HINTERNET hInternet)
{
    ClearRequestData(hInternet);   // frees heap buffer and map entry
    return fpInternetCloseHandle(hInternet);
}

static DWORD WINAPI InitThread(LPVOID)
{
    wchar_t path[MAX_PATH];
    GetSystemDirectoryW(path, MAX_PATH);
    wcscat_s(path, L"\\wininet.dll");
    HMODULE hWininet = LoadLibraryW(path);
    if (!hWininet) return 1;

    TransformInit();
    InitProxyExports(hWininet);

    MH_Initialize();
    MH_CreateHook(GetProcAddress(hWininet, "InternetConnectA"),
        &Hook_InternetConnectA, (LPVOID*)&fpInternetConnectA);
    MH_CreateHook(GetProcAddress(hWininet, "HttpOpenRequestA"),
        &Hook_HttpOpenRequestA, (LPVOID*)&fpHttpOpenRequestA);
    MH_CreateHook(GetProcAddress(hWininet, "HttpSendRequestA"),
        &Hook_HttpSendRequestA, (LPVOID*)&fpHttpSendRequestA);
    MH_CreateHook(GetProcAddress(hWininet, "InternetCloseHandle"),
        &Hook_InternetCloseHandle, (LPVOID*)&fpInternetCloseHandle);
    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hInst);
        CreateThread(nullptr, 0, InitThread, nullptr, 0, nullptr);
    }
    else if (reason == DLL_PROCESS_DETACH) {
        MH_DisableHook(MH_ALL_HOOKS);
        MH_Uninitialize();
    }
    return TRUE;
}