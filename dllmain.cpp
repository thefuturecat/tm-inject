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

PFN_InternetConnectA  fpInternetConnectA = nullptr;
PFN_HttpOpenRequestA  fpHttpOpenRequestA = nullptr;
PFN_HttpSendRequestA  fpHttpSendRequestA = nullptr;
PFN_InternetCloseHandle fpInternetCloseHandle = nullptr;

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

    // Rewrite path and extract query string
    std::string query;
    std::string newPath = RewritePath(lpszObjectName, query);

    HINTERNET hReq = fpHttpOpenRequestA(hConnect, lpszVerb, newPath.c_str(),
        lpszVersion, lpszReferrer, lplpszAcceptTypes, dwFlags, dwContext);

    // Store query params keyed by the new handle
    if (hReq) StoreQuery(hReq, query);

    return hReq;
}

BOOL WINAPI Hook_HttpSendRequestA(
    HINTERNET hRequest, LPCSTR lpszHeaders, DWORD dwHeadersLength,
    LPVOID lpOptional, DWORD dwOptionalLength)
{
    std::string json = ConsumeJsonBody(hRequest);

    if (!json.empty()) {
        // Override headers to set Content-Type and send JSON body
        std::string headers = "Content-Type: application/json\r\n";
        return fpHttpSendRequestA(hRequest,
            headers.c_str(), (DWORD)headers.size(),
            (LPVOID)json.c_str(), (DWORD)json.size());
    }

    // No transform needed — pass through unchanged
    return fpHttpSendRequestA(hRequest, lpszHeaders, dwHeadersLength,
        lpOptional, dwOptionalLength);
}

BOOL WINAPI Hook_InternetCloseHandle(HINTERNET hInternet)
{
    ClearRequestData(hInternet); // clean up any leftover map entries
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