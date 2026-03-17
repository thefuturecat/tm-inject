#include "pch.h"
#include "proxy_exports.h"
#include <windows.h>
#include <wininet.h>
#include "MinHook.h"
#pragma comment(lib, "wininet.lib")

#define TARGET_HOST  "www.trackmania.com"
#define REPLACE_HOST "tm1.ms.trackmania.pt"

typedef HINTERNET(WINAPI* PFN_InternetConnectA)(HINTERNET, LPCSTR, INTERNET_PORT, LPCSTR, LPCSTR, DWORD, DWORD, DWORD_PTR);
typedef HINTERNET(WINAPI* PFN_HttpOpenRequestA)(HINTERNET, LPCSTR, LPCSTR, LPCSTR, LPCSTR, LPCSTR*, DWORD, DWORD_PTR);

PFN_InternetConnectA fpInternetConnectA = nullptr;
PFN_HttpOpenRequestA fpHttpOpenRequestA = nullptr;

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
    return fpHttpOpenRequestA(hConnect, lpszVerb, lpszObjectName,
        lpszVersion, lpszReferrer, lplpszAcceptTypes, dwFlags, dwContext);
}

static DWORD WINAPI InitThread(LPVOID)
{
    wchar_t path[MAX_PATH];
    GetSystemDirectoryW(path, MAX_PATH);
    wcscat_s(path, L"\\wininet.dll");
    HMODULE hWininet = LoadLibraryW(path);
    if (!hWininet) return 1;

    // Fill all the naked stub pointers
    InitProxyExports(hWininet);

    // Install our two hooks on top
    MH_Initialize();
    MH_CreateHook(GetProcAddress(hWininet, "InternetConnectA"),
        &Hook_InternetConnectA, (LPVOID*)&fpInternetConnectA);
    MH_CreateHook(GetProcAddress(hWininet, "HttpOpenRequestA"),
        &Hook_HttpOpenRequestA, (LPVOID*)&fpHttpOpenRequestA);
    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hInst);
        CreateThread(nullptr, 0, InitThread, nullptr, 0, nullptr);
    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        MH_DisableHook(MH_ALL_HOOKS);
        MH_Uninitialize();
    }
    return TRUE;
}