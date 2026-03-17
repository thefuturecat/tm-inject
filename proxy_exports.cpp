#include "pch.h"
#include "proxy_exports.h"
#include <windows.h>

// One pointer per export
static void* fp_AppCacheCheckManifest = nullptr;
static void* fp_AppCacheCloseHandle = nullptr;
static void* fp_AppCacheCreateAndCommitFile = nullptr;
static void* fp_AppCacheDeleteGroup = nullptr;
static void* fp_AppCacheDeleteIEGroup = nullptr;
static void* fp_AppCacheDuplicateHandle = nullptr;
static void* fp_AppCacheFinalize = nullptr;
static void* fp_AppCacheFreeDownloadList = nullptr;
static void* fp_AppCacheFreeGroupList = nullptr;
static void* fp_AppCacheFreeIESpace = nullptr;
static void* fp_AppCacheFreeSpace = nullptr;
static void* fp_AppCacheGetDownloadList = nullptr;
static void* fp_AppCacheGetFallbackUrl = nullptr;
static void* fp_AppCacheGetGroupList = nullptr;
static void* fp_AppCacheGetIEGroupList = nullptr;
static void* fp_AppCacheGetInfo = nullptr;
static void* fp_AppCacheGetManifestUrl = nullptr;
static void* fp_AppCacheLookup = nullptr;
static void* fp_CommitUrlCacheEntryA = nullptr;
static void* fp_CommitUrlCacheEntryBinaryBlob = nullptr;
static void* fp_CommitUrlCacheEntryW = nullptr;
static void* fp_CreateMD5SSOHash = nullptr;
static void* fp_CreateUrlCacheContainerA = nullptr;
static void* fp_CreateUrlCacheContainerW = nullptr;
static void* fp_CreateUrlCacheEntryA = nullptr;
static void* fp_CreateUrlCacheEntryExW = nullptr;
static void* fp_CreateUrlCacheEntryW = nullptr;
static void* fp_CreateUrlCacheGroup = nullptr;
static void* fp_DeleteIE3Cache = nullptr;
static void* fp_DeleteUrlCacheContainerA = nullptr;
static void* fp_DeleteUrlCacheContainerW = nullptr;
static void* fp_DeleteUrlCacheEntry = nullptr;
static void* fp_DeleteUrlCacheEntryA = nullptr;
static void* fp_DeleteUrlCacheEntryW = nullptr;
static void* fp_DeleteUrlCacheGroup = nullptr;
static void* fp_DeleteWpadCacheForNetworks = nullptr;
static void* fp_DetectAutoProxyUrl = nullptr;
static void* fp_DispatchAPICall = nullptr;
static void* fp_DllCanUnloadNow = nullptr;
static void* fp_DllGetClassObject = nullptr;
static void* fp_DllInstall = nullptr;
static void* fp_DllRegisterServer = nullptr;
static void* fp_DllUnregisterServer = nullptr;
static void* fp_FindCloseUrlCache = nullptr;
static void* fp_FindFirstUrlCacheContainerA = nullptr;
static void* fp_FindFirstUrlCacheContainerW = nullptr;
static void* fp_FindFirstUrlCacheEntryA = nullptr;
static void* fp_FindFirstUrlCacheEntryExA = nullptr;
static void* fp_FindFirstUrlCacheEntryExW = nullptr;
static void* fp_FindFirstUrlCacheEntryW = nullptr;
static void* fp_FindFirstUrlCacheGroup = nullptr;
static void* fp_FindNextUrlCacheContainerA = nullptr;
static void* fp_FindNextUrlCacheContainerW = nullptr;
static void* fp_FindNextUrlCacheEntryA = nullptr;
static void* fp_FindNextUrlCacheEntryExA = nullptr;
static void* fp_FindNextUrlCacheEntryExW = nullptr;
static void* fp_FindNextUrlCacheEntryW = nullptr;
static void* fp_FindNextUrlCacheGroup = nullptr;
static void* fp_ForceNexusLookup = nullptr;
static void* fp_ForceNexusLookupExW = nullptr;
static void* fp_FreeUrlCacheSpaceA = nullptr;
static void* fp_FreeUrlCacheSpaceW = nullptr;
static void* fp_FtpCommandA = nullptr;
static void* fp_FtpCommandW = nullptr;
static void* fp_FtpCreateDirectoryA = nullptr;
static void* fp_FtpCreateDirectoryW = nullptr;
static void* fp_FtpDeleteFileA = nullptr;
static void* fp_FtpDeleteFileW = nullptr;
static void* fp_FtpFindFirstFileA = nullptr;
static void* fp_FtpFindFirstFileW = nullptr;
static void* fp_FtpGetCurrentDirectoryA = nullptr;
static void* fp_FtpGetCurrentDirectoryW = nullptr;
static void* fp_FtpGetFileA = nullptr;
static void* fp_FtpGetFileEx = nullptr;
static void* fp_FtpGetFileSize = nullptr;
static void* fp_FtpGetFileW = nullptr;
static void* fp_FtpOpenFileA = nullptr;
static void* fp_FtpOpenFileW = nullptr;
static void* fp_FtpPutFileA = nullptr;
static void* fp_FtpPutFileEx = nullptr;
static void* fp_FtpPutFileW = nullptr;
static void* fp_FtpRemoveDirectoryA = nullptr;
static void* fp_FtpRemoveDirectoryW = nullptr;
static void* fp_FtpRenameFileA = nullptr;
static void* fp_FtpRenameFileW = nullptr;
static void* fp_FtpSetCurrentDirectoryA = nullptr;
static void* fp_FtpSetCurrentDirectoryW = nullptr;
static void* fp_GetProxyDllInfo = nullptr;
static void* fp_GetUrlCacheConfigInfoA = nullptr;
static void* fp_GetUrlCacheConfigInfoW = nullptr;
static void* fp_GetUrlCacheEntryBinaryBlob = nullptr;
static void* fp_GetUrlCacheEntryInfoA = nullptr;
static void* fp_GetUrlCacheEntryInfoExA = nullptr;
static void* fp_GetUrlCacheEntryInfoExW = nullptr;
static void* fp_GetUrlCacheEntryInfoW = nullptr;
static void* fp_GetUrlCacheGroupAttributeA = nullptr;
static void* fp_GetUrlCacheGroupAttributeW = nullptr;
static void* fp_GetUrlCacheHeaderData = nullptr;
static void* fp_GopherCreateLocatorA = nullptr;
static void* fp_GopherCreateLocatorW = nullptr;
static void* fp_GopherFindFirstFileA = nullptr;
static void* fp_GopherFindFirstFileW = nullptr;
static void* fp_GopherGetAttributeA = nullptr;
static void* fp_GopherGetAttributeW = nullptr;
static void* fp_GopherGetLocatorTypeA = nullptr;
static void* fp_GopherGetLocatorTypeW = nullptr;
static void* fp_GopherOpenFileA = nullptr;
static void* fp_GopherOpenFileW = nullptr;
static void* fp_HttpAddRequestHeadersA = nullptr;
static void* fp_HttpAddRequestHeadersW = nullptr;
static void* fp_HttpCheckDavCompliance = nullptr;
static void* fp_HttpCloseDependencyHandle = nullptr;
static void* fp_HttpDuplicateDependencyHandle = nullptr;
static void* fp_HttpEndRequestA = nullptr;
static void* fp_HttpEndRequestW = nullptr;
static void* fp_HttpGetServerCredentials = nullptr;
static void* fp_HttpGetTunnelSocket = nullptr;
static void* fp_HttpIndicatePageLoadComplete = nullptr;
static void* fp_HttpIsHostHstsEnabled = nullptr;
static void* fp_HttpOpenDependencyHandle = nullptr;
static void* fp_HttpOpenRequestA = nullptr;
static void* fp_HttpOpenRequestW = nullptr;
static void* fp_HttpPushClose = nullptr;
static void* fp_HttpPushEnable = nullptr;
static void* fp_HttpPushWait = nullptr;
static void* fp_HttpQueryInfoA = nullptr;
static void* fp_HttpQueryInfoW = nullptr;
static void* fp_HttpSendRequestA = nullptr;
static void* fp_HttpSendRequestExA = nullptr;
static void* fp_HttpSendRequestExW = nullptr;
static void* fp_HttpSendRequestW = nullptr;
static void* fp_HttpWebSocketClose = nullptr;
static void* fp_HttpWebSocketCompleteUpgrade = nullptr;
static void* fp_HttpWebSocketQueryCloseStatus = nullptr;
static void* fp_HttpWebSocketReceive = nullptr;
static void* fp_HttpWebSocketSend = nullptr;
static void* fp_HttpWebSocketShutdown = nullptr;
static void* fp_IncrementUrlCacheHeaderData = nullptr;
static void* fp_InternetAlgIdToStringA = nullptr;
static void* fp_InternetAlgIdToStringW = nullptr;
static void* fp_InternetAttemptConnect = nullptr;
static void* fp_InternetAutodial = nullptr;
static void* fp_InternetAutodialCallback = nullptr;
static void* fp_InternetAutodialHangup = nullptr;
static void* fp_InternetCanonicalizeUrlA = nullptr;
static void* fp_InternetCanonicalizeUrlW = nullptr;
static void* fp_InternetCheckConnectionA = nullptr;
static void* fp_InternetCheckConnectionW = nullptr;
static void* fp_InternetClearAllPerSiteCookieDecisions = nullptr;
static void* fp_InternetCloseHandle = nullptr;
static void* fp_InternetCombineUrlA = nullptr;
static void* fp_InternetCombineUrlW = nullptr;
static void* fp_InternetConfirmZoneCrossing = nullptr;
static void* fp_InternetConfirmZoneCrossingA = nullptr;
static void* fp_InternetConfirmZoneCrossingW = nullptr;
static void* fp_InternetConnectA = nullptr;
static void* fp_InternetConnectW = nullptr;
static void* fp_InternetConvertUrlFromWireToWideChar = nullptr;
static void* fp_InternetCrackUrlA = nullptr;
static void* fp_InternetCrackUrlW = nullptr;
static void* fp_InternetCreateUrlA = nullptr;
static void* fp_InternetCreateUrlW = nullptr;
static void* fp_InternetDial = nullptr;
static void* fp_InternetDialA = nullptr;
static void* fp_InternetDialW = nullptr;
static void* fp_InternetEnumPerSiteCookieDecisionA = nullptr;
static void* fp_InternetEnumPerSiteCookieDecisionW = nullptr;
static void* fp_InternetErrorDlg = nullptr;
static void* fp_InternetFindNextFileA = nullptr;
static void* fp_InternetFindNextFileW = nullptr;
static void* fp_InternetFortezzaCommand = nullptr;
static void* fp_InternetFreeCookies = nullptr;
static void* fp_InternetFreeProxyInfoList = nullptr;
static void* fp_InternetGetCertByURL = nullptr;
static void* fp_InternetGetCertByURLA = nullptr;
static void* fp_InternetGetConnectedState = nullptr;
static void* fp_InternetGetConnectedStateEx = nullptr;
static void* fp_InternetGetConnectedStateExA = nullptr;
static void* fp_InternetGetConnectedStateExW = nullptr;
static void* fp_InternetGetCookieA = nullptr;
static void* fp_InternetGetCookieEx2 = nullptr;
static void* fp_InternetGetCookieExA = nullptr;
static void* fp_InternetGetCookieExW = nullptr;
static void* fp_InternetGetCookieW = nullptr;
static void* fp_InternetGetLastResponseInfoA = nullptr;
static void* fp_InternetGetLastResponseInfoW = nullptr;
static void* fp_InternetGetPerSiteCookieDecisionA = nullptr;
static void* fp_InternetGetPerSiteCookieDecisionW = nullptr;
static void* fp_InternetGetProxyForUrl = nullptr;
static void* fp_InternetGetSecurityInfoByURL = nullptr;
static void* fp_InternetGetSecurityInfoByURLA = nullptr;
static void* fp_InternetGetSecurityInfoByURLW = nullptr;
static void* fp_InternetGoOnline = nullptr;
static void* fp_InternetGoOnlineA = nullptr;
static void* fp_InternetGoOnlineW = nullptr;
static void* fp_InternetHangUp = nullptr;
static void* fp_InternetInitializeAutoProxyDll = nullptr;
static void* fp_InternetLockRequestFile = nullptr;
static void* fp_InternetOpenA = nullptr;
static void* fp_InternetOpenUrlA = nullptr;
static void* fp_InternetOpenUrlW = nullptr;
static void* fp_InternetOpenW = nullptr;
static void* fp_InternetQueryDataAvailable = nullptr;
static void* fp_InternetQueryFortezzaStatus = nullptr;
static void* fp_InternetQueryOptionA = nullptr;
static void* fp_InternetQueryOptionW = nullptr;
static void* fp_InternetReadFile = nullptr;
static void* fp_InternetReadFileExA = nullptr;
static void* fp_InternetReadFileExW = nullptr;
static void* fp_InternetSecurityProtocolToStringA = nullptr;
static void* fp_InternetSecurityProtocolToStringW = nullptr;
static void* fp_InternetSetCookieA = nullptr;
static void* fp_InternetSetCookieEx2 = nullptr;
static void* fp_InternetSetCookieExA = nullptr;
static void* fp_InternetSetCookieExW = nullptr;
static void* fp_InternetSetCookieW = nullptr;
static void* fp_InternetSetDialState = nullptr;
static void* fp_InternetSetDialStateA = nullptr;
static void* fp_InternetSetDialStateW = nullptr;
static void* fp_InternetSetFilePointer = nullptr;
static void* fp_InternetSetOptionA = nullptr;
static void* fp_InternetSetOptionExA = nullptr;
static void* fp_InternetSetOptionExW = nullptr;
static void* fp_InternetSetOptionW = nullptr;
static void* fp_InternetSetPerSiteCookieDecisionA = nullptr;
static void* fp_InternetSetPerSiteCookieDecisionW = nullptr;
static void* fp_InternetSetSecureLegacyServersAppCompat = nullptr;
static void* fp_InternetSetStatusCallback = nullptr;
static void* fp_InternetSetStatusCallbackA = nullptr;
static void* fp_InternetSetStatusCallbackW = nullptr;
static void* fp_InternetShowSecurityInfoByURL = nullptr;
static void* fp_InternetShowSecurityInfoByURLA = nullptr;
static void* fp_InternetShowSecurityInfoByURLW = nullptr;
static void* fp_InternetTimeFromSystemTime = nullptr;
static void* fp_InternetTimeFromSystemTimeA = nullptr;
static void* fp_InternetTimeFromSystemTimeW = nullptr;
static void* fp_InternetTimeToSystemTime = nullptr;
static void* fp_InternetTimeToSystemTimeA = nullptr;
static void* fp_InternetTimeToSystemTimeW = nullptr;
static void* fp_InternetUnlockRequestFile = nullptr;
static void* fp_InternetWriteFile = nullptr;
static void* fp_InternetWriteFileExA = nullptr;
static void* fp_InternetWriteFileExW = nullptr;
static void* fp_IsHostInProxyBypassList = nullptr;
static void* fp_IsUrlCacheEntryExpiredA = nullptr;
static void* fp_IsUrlCacheEntryExpiredW = nullptr;
static void* fp_LoadUrlCacheContent = nullptr;
static void* fp_ParseX509EncodedCertificateForListBoxEntry = nullptr;
static void* fp_PrivacyGetZonePreferenceW = nullptr;
static void* fp_PrivacySetZonePreferenceW = nullptr;
static void* fp_ReadUrlCacheEntryStream = nullptr;
static void* fp_ReadUrlCacheEntryStreamEx = nullptr;
static void* fp_RegisterUrlCacheNotification = nullptr;
static void* fp_ResumeSuspendedDownload = nullptr;
static void* fp_RetrieveUrlCacheEntryFileA = nullptr;
static void* fp_RetrieveUrlCacheEntryFileW = nullptr;
static void* fp_RetrieveUrlCacheEntryStreamA = nullptr;
static void* fp_RetrieveUrlCacheEntryStreamW = nullptr;
static void* fp_RunOnceUrlCache = nullptr;
static void* fp_SetUrlCacheConfigInfoA = nullptr;
static void* fp_SetUrlCacheConfigInfoW = nullptr;
static void* fp_SetUrlCacheEntryGroup = nullptr;
static void* fp_SetUrlCacheEntryGroupA = nullptr;
static void* fp_SetUrlCacheEntryGroupW = nullptr;
static void* fp_SetUrlCacheEntryInfoA = nullptr;
static void* fp_SetUrlCacheEntryInfoW = nullptr;
static void* fp_SetUrlCacheGroupAttributeA = nullptr;
static void* fp_SetUrlCacheGroupAttributeW = nullptr;
static void* fp_SetUrlCacheHeaderData = nullptr;
static void* fp_ShowCertificate = nullptr;
static void* fp_ShowClientAuthCerts = nullptr;
static void* fp_ShowSecurityInfo = nullptr;
static void* fp_ShowX509EncodedCertificate = nullptr;
static void* fp_UnlockUrlCacheEntryFile = nullptr;
static void* fp_UnlockUrlCacheEntryFileA = nullptr;
static void* fp_UnlockUrlCacheEntryFileW = nullptr;
static void* fp_UnlockUrlCacheEntryStream = nullptr;
static void* fp_UpdateUrlCacheContentPath = nullptr;
static void* fp_UrlCacheCheckEntriesExist = nullptr;
static void* fp_UrlCacheCloseEntryHandle = nullptr;
static void* fp_UrlCacheContainerSetEntryMaximumAge = nullptr;
static void* fp_UrlCacheCreateContainer = nullptr;
static void* fp_UrlCacheFindFirstEntry = nullptr;
static void* fp_UrlCacheFindNextEntry = nullptr;
static void* fp_UrlCacheFreeEntryInfo = nullptr;
static void* fp_UrlCacheFreeGlobalSpace = nullptr;
static void* fp_UrlCacheGetContentPaths = nullptr;
static void* fp_UrlCacheGetEntryInfo = nullptr;
static void* fp_UrlCacheGetGlobalCacheSize = nullptr;
static void* fp_UrlCacheGetGlobalLimit = nullptr;
static void* fp_UrlCacheReadEntryStream = nullptr;
static void* fp_UrlCacheReloadSettings = nullptr;
static void* fp_UrlCacheRetrieveEntryFile = nullptr;
static void* fp_UrlCacheRetrieveEntryStream = nullptr;
static void* fp_UrlCacheServer = nullptr;
static void* fp_UrlCacheSetGlobalLimit = nullptr;
static void* fp_UrlCacheUpdateEntryExtraData = nullptr;
static void* fp_UrlZonesDetach = nullptr;
static void* fp_GetFileExtensionFromUrl = nullptr;

// Called from InitThread — fills every pointer above
void InitProxyExports(HMODULE h)
{
#define LOAD(name) fp_##name = GetProcAddress(h, #name)
    LOAD(AppCacheCheckManifest);
    LOAD(AppCacheCloseHandle);
    LOAD(AppCacheCreateAndCommitFile);
    LOAD(AppCacheDeleteGroup);
    LOAD(AppCacheDeleteIEGroup);
    LOAD(AppCacheDuplicateHandle);
    LOAD(AppCacheFinalize);
    LOAD(AppCacheFreeDownloadList);
    LOAD(AppCacheFreeGroupList);
    LOAD(AppCacheFreeIESpace);
    LOAD(AppCacheFreeSpace);
    LOAD(AppCacheGetDownloadList);
    LOAD(AppCacheGetFallbackUrl);
    LOAD(AppCacheGetGroupList);
    LOAD(AppCacheGetIEGroupList);
    LOAD(AppCacheGetInfo);
    LOAD(AppCacheGetManifestUrl);
    LOAD(AppCacheLookup);
    LOAD(CommitUrlCacheEntryA);
    LOAD(CommitUrlCacheEntryBinaryBlob);
    LOAD(CommitUrlCacheEntryW);
    LOAD(CreateMD5SSOHash);
    LOAD(CreateUrlCacheContainerA);
    LOAD(CreateUrlCacheContainerW);
    LOAD(CreateUrlCacheEntryA);
    LOAD(CreateUrlCacheEntryExW);
    LOAD(CreateUrlCacheEntryW);
    LOAD(CreateUrlCacheGroup);
    LOAD(DeleteIE3Cache);
    LOAD(DeleteUrlCacheContainerA);
    LOAD(DeleteUrlCacheContainerW);
    LOAD(DeleteUrlCacheEntry);
    LOAD(DeleteUrlCacheEntryA);
    LOAD(DeleteUrlCacheEntryW);
    LOAD(DeleteUrlCacheGroup);
    LOAD(DeleteWpadCacheForNetworks);
    LOAD(DetectAutoProxyUrl);
    LOAD(DispatchAPICall);
    LOAD(DllCanUnloadNow);
    LOAD(DllGetClassObject);
    LOAD(DllInstall);
    LOAD(DllRegisterServer);
    LOAD(DllUnregisterServer);
    LOAD(FindCloseUrlCache);
    LOAD(FindFirstUrlCacheContainerA);
    LOAD(FindFirstUrlCacheContainerW);
    LOAD(FindFirstUrlCacheEntryA);
    LOAD(FindFirstUrlCacheEntryExA);
    LOAD(FindFirstUrlCacheEntryExW);
    LOAD(FindFirstUrlCacheEntryW);
    LOAD(FindFirstUrlCacheGroup);
    LOAD(FindNextUrlCacheContainerA);
    LOAD(FindNextUrlCacheContainerW);
    LOAD(FindNextUrlCacheEntryA);
    LOAD(FindNextUrlCacheEntryExA);
    LOAD(FindNextUrlCacheEntryExW);
    LOAD(FindNextUrlCacheEntryW);
    LOAD(FindNextUrlCacheGroup);
    LOAD(ForceNexusLookup);
    LOAD(ForceNexusLookupExW);
    LOAD(FreeUrlCacheSpaceA);
    LOAD(FreeUrlCacheSpaceW);
    LOAD(FtpCommandA);
    LOAD(FtpCommandW);
    LOAD(FtpCreateDirectoryA);
    LOAD(FtpCreateDirectoryW);
    LOAD(FtpDeleteFileA);
    LOAD(FtpDeleteFileW);
    LOAD(FtpFindFirstFileA);
    LOAD(FtpFindFirstFileW);
    LOAD(FtpGetCurrentDirectoryA);
    LOAD(FtpGetCurrentDirectoryW);
    LOAD(FtpGetFileA);
    LOAD(FtpGetFileEx);
    LOAD(FtpGetFileSize);
    LOAD(FtpGetFileW);
    LOAD(FtpOpenFileA);
    LOAD(FtpOpenFileW);
    LOAD(FtpPutFileA);
    LOAD(FtpPutFileEx);
    LOAD(FtpPutFileW);
    LOAD(FtpRemoveDirectoryA);
    LOAD(FtpRemoveDirectoryW);
    LOAD(FtpRenameFileA);
    LOAD(FtpRenameFileW);
    LOAD(FtpSetCurrentDirectoryA);
    LOAD(FtpSetCurrentDirectoryW);
    LOAD(GetProxyDllInfo);
    LOAD(GetUrlCacheConfigInfoA);
    LOAD(GetUrlCacheConfigInfoW);
    LOAD(GetUrlCacheEntryBinaryBlob);
    LOAD(GetUrlCacheEntryInfoA);
    LOAD(GetUrlCacheEntryInfoExA);
    LOAD(GetUrlCacheEntryInfoExW);
    LOAD(GetUrlCacheEntryInfoW);
    LOAD(GetUrlCacheGroupAttributeA);
    LOAD(GetUrlCacheGroupAttributeW);
    LOAD(GetUrlCacheHeaderData);
    LOAD(GopherCreateLocatorA);
    LOAD(GopherCreateLocatorW);
    LOAD(GopherFindFirstFileA);
    LOAD(GopherFindFirstFileW);
    LOAD(GopherGetAttributeA);
    LOAD(GopherGetAttributeW);
    LOAD(GopherGetLocatorTypeA);
    LOAD(GopherGetLocatorTypeW);
    LOAD(GopherOpenFileA);
    LOAD(GopherOpenFileW);
    LOAD(HttpAddRequestHeadersA);
    LOAD(HttpAddRequestHeadersW);
    LOAD(HttpCheckDavCompliance);
    LOAD(HttpCloseDependencyHandle);
    LOAD(HttpDuplicateDependencyHandle);
    LOAD(HttpEndRequestA);
    LOAD(HttpEndRequestW);
    LOAD(HttpGetServerCredentials);
    LOAD(HttpGetTunnelSocket);
    LOAD(HttpIndicatePageLoadComplete);
    LOAD(HttpIsHostHstsEnabled);
    LOAD(HttpOpenDependencyHandle);
    LOAD(HttpOpenRequestA);
    LOAD(HttpOpenRequestW);
    LOAD(HttpPushClose);
    LOAD(HttpPushEnable);
    LOAD(HttpPushWait);
    LOAD(HttpQueryInfoA);
    LOAD(HttpQueryInfoW);
    LOAD(HttpSendRequestA);
    LOAD(HttpSendRequestExA);
    LOAD(HttpSendRequestExW);
    LOAD(HttpSendRequestW);
    LOAD(HttpWebSocketClose);
    LOAD(HttpWebSocketCompleteUpgrade);
    LOAD(HttpWebSocketQueryCloseStatus);
    LOAD(HttpWebSocketReceive);
    LOAD(HttpWebSocketSend);
    LOAD(HttpWebSocketShutdown);
    LOAD(IncrementUrlCacheHeaderData);
    LOAD(InternetAlgIdToStringA);
    LOAD(InternetAlgIdToStringW);
    LOAD(InternetAttemptConnect);
    LOAD(InternetAutodial);
    LOAD(InternetAutodialCallback);
    LOAD(InternetAutodialHangup);
    LOAD(InternetCanonicalizeUrlA);
    LOAD(InternetCanonicalizeUrlW);
    LOAD(InternetCheckConnectionA);
    LOAD(InternetCheckConnectionW);
    LOAD(InternetClearAllPerSiteCookieDecisions);
    LOAD(InternetCloseHandle);
    LOAD(InternetCombineUrlA);
    LOAD(InternetCombineUrlW);
    LOAD(InternetConfirmZoneCrossing);
    LOAD(InternetConfirmZoneCrossingA);
    LOAD(InternetConfirmZoneCrossingW);
    LOAD(InternetConnectA);
    LOAD(InternetConnectW);
    LOAD(InternetConvertUrlFromWireToWideChar);
    LOAD(InternetCrackUrlA);
    LOAD(InternetCrackUrlW);
    LOAD(InternetCreateUrlA);
    LOAD(InternetCreateUrlW);
    LOAD(InternetDial);
    LOAD(InternetDialA);
    LOAD(InternetDialW);
    LOAD(InternetEnumPerSiteCookieDecisionA);
    LOAD(InternetEnumPerSiteCookieDecisionW);
    LOAD(InternetErrorDlg);
    LOAD(InternetFindNextFileA);
    LOAD(InternetFindNextFileW);
    LOAD(InternetFortezzaCommand);
    LOAD(InternetFreeCookies);
    LOAD(InternetFreeProxyInfoList);
    LOAD(InternetGetCertByURL);
    LOAD(InternetGetCertByURLA);
    LOAD(InternetGetConnectedState);
    LOAD(InternetGetConnectedStateEx);
    LOAD(InternetGetConnectedStateExA);
    LOAD(InternetGetConnectedStateExW);
    LOAD(InternetGetCookieA);
    LOAD(InternetGetCookieEx2);
    LOAD(InternetGetCookieExA);
    LOAD(InternetGetCookieExW);
    LOAD(InternetGetCookieW);
    LOAD(InternetGetLastResponseInfoA);
    LOAD(InternetGetLastResponseInfoW);
    LOAD(InternetGetPerSiteCookieDecisionA);
    LOAD(InternetGetPerSiteCookieDecisionW);
    LOAD(InternetGetProxyForUrl);
    LOAD(InternetGetSecurityInfoByURL);
    LOAD(InternetGetSecurityInfoByURLA);
    LOAD(InternetGetSecurityInfoByURLW);
    LOAD(InternetGoOnline);
    LOAD(InternetGoOnlineA);
    LOAD(InternetGoOnlineW);
    LOAD(InternetHangUp);
    LOAD(InternetInitializeAutoProxyDll);
    LOAD(InternetLockRequestFile);
    LOAD(InternetOpenA);
    LOAD(InternetOpenUrlA);
    LOAD(InternetOpenUrlW);
    LOAD(InternetOpenW);
    LOAD(InternetQueryDataAvailable);
    LOAD(InternetQueryFortezzaStatus);
    LOAD(InternetQueryOptionA);
    LOAD(InternetQueryOptionW);
    LOAD(InternetReadFile);
    LOAD(InternetReadFileExA);
    LOAD(InternetReadFileExW);
    LOAD(InternetSecurityProtocolToStringA);
    LOAD(InternetSecurityProtocolToStringW);
    LOAD(InternetSetCookieA);
    LOAD(InternetSetCookieEx2);
    LOAD(InternetSetCookieExA);
    LOAD(InternetSetCookieExW);
    LOAD(InternetSetCookieW);
    LOAD(InternetSetDialState);
    LOAD(InternetSetDialStateA);
    LOAD(InternetSetDialStateW);
    LOAD(InternetSetFilePointer);
    LOAD(InternetSetOptionA);
    LOAD(InternetSetOptionExA);
    LOAD(InternetSetOptionExW);
    LOAD(InternetSetOptionW);
    LOAD(InternetSetPerSiteCookieDecisionA);
    LOAD(InternetSetPerSiteCookieDecisionW);
    LOAD(InternetSetSecureLegacyServersAppCompat);
    LOAD(InternetSetStatusCallback);
    LOAD(InternetSetStatusCallbackA);
    LOAD(InternetSetStatusCallbackW);
    LOAD(InternetShowSecurityInfoByURL);
    LOAD(InternetShowSecurityInfoByURLA);
    LOAD(InternetShowSecurityInfoByURLW);
    LOAD(InternetTimeFromSystemTime);
    LOAD(InternetTimeFromSystemTimeA);
    LOAD(InternetTimeFromSystemTimeW);
    LOAD(InternetTimeToSystemTime);
    LOAD(InternetTimeToSystemTimeA);
    LOAD(InternetTimeToSystemTimeW);
    LOAD(InternetUnlockRequestFile);
    LOAD(InternetWriteFile);
    LOAD(InternetWriteFileExA);
    LOAD(InternetWriteFileExW);
    LOAD(IsHostInProxyBypassList);
    LOAD(IsUrlCacheEntryExpiredA);
    LOAD(IsUrlCacheEntryExpiredW);
    LOAD(LoadUrlCacheContent);
    LOAD(ParseX509EncodedCertificateForListBoxEntry);
    LOAD(PrivacyGetZonePreferenceW);
    LOAD(PrivacySetZonePreferenceW);
    LOAD(ReadUrlCacheEntryStream);
    LOAD(ReadUrlCacheEntryStreamEx);
    LOAD(RegisterUrlCacheNotification);
    LOAD(ResumeSuspendedDownload);
    LOAD(RetrieveUrlCacheEntryFileA);
    LOAD(RetrieveUrlCacheEntryFileW);
    LOAD(RetrieveUrlCacheEntryStreamA);
    LOAD(RetrieveUrlCacheEntryStreamW);
    LOAD(RunOnceUrlCache);
    LOAD(SetUrlCacheConfigInfoA);
    LOAD(SetUrlCacheConfigInfoW);
    LOAD(SetUrlCacheEntryGroup);
    LOAD(SetUrlCacheEntryGroupA);
    LOAD(SetUrlCacheEntryGroupW);
    LOAD(SetUrlCacheEntryInfoA);
    LOAD(SetUrlCacheEntryInfoW);
    LOAD(SetUrlCacheGroupAttributeA);
    LOAD(SetUrlCacheGroupAttributeW);
    LOAD(SetUrlCacheHeaderData);
    LOAD(ShowCertificate);
    LOAD(ShowClientAuthCerts);
    LOAD(ShowSecurityInfo);
    LOAD(ShowX509EncodedCertificate);
    LOAD(UnlockUrlCacheEntryFile);
    LOAD(UnlockUrlCacheEntryFileA);
    LOAD(UnlockUrlCacheEntryFileW);
    LOAD(UnlockUrlCacheEntryStream);
    LOAD(UpdateUrlCacheContentPath);
    LOAD(UrlCacheCheckEntriesExist);
    LOAD(UrlCacheCloseEntryHandle);
    LOAD(UrlCacheContainerSetEntryMaximumAge);
    LOAD(UrlCacheCreateContainer);
    LOAD(UrlCacheFindFirstEntry);
    LOAD(UrlCacheFindNextEntry);
    LOAD(UrlCacheFreeEntryInfo);
    LOAD(UrlCacheFreeGlobalSpace);
    LOAD(UrlCacheGetContentPaths);
    LOAD(UrlCacheGetEntryInfo);
    LOAD(UrlCacheGetGlobalCacheSize);
    LOAD(UrlCacheGetGlobalLimit);
    LOAD(UrlCacheReadEntryStream);
    LOAD(UrlCacheReloadSettings);
    LOAD(UrlCacheRetrieveEntryFile);
    LOAD(UrlCacheRetrieveEntryStream);
    LOAD(UrlCacheServer);
    LOAD(UrlCacheSetGlobalLimit);
    LOAD(UrlCacheUpdateEntryExtraData);
    LOAD(UrlZonesDetach);
    fp_GetFileExtensionFromUrl = GetProcAddress(h, "_GetFileExtensionFromUrl");
#undef LOAD
}

// Naked stubs — no signature needed, just jmp to the real function
#define STUB(name) \
    extern "C" __declspec(dllexport) __declspec(naked) void name() \
    { __asm { jmp dword ptr [fp_##name] } }

extern "C" {
    STUB(AppCacheCheckManifest)
        STUB(AppCacheCloseHandle)
        STUB(AppCacheCreateAndCommitFile)
        STUB(AppCacheDeleteGroup)
        STUB(AppCacheDeleteIEGroup)
        STUB(AppCacheDuplicateHandle)
        STUB(AppCacheFinalize)
        STUB(AppCacheFreeDownloadList)
        STUB(AppCacheFreeGroupList)
        STUB(AppCacheFreeIESpace)
        STUB(AppCacheFreeSpace)
        STUB(AppCacheGetDownloadList)
        STUB(AppCacheGetFallbackUrl)
        STUB(AppCacheGetGroupList)
        STUB(AppCacheGetIEGroupList)
        STUB(AppCacheGetInfo)
        STUB(AppCacheGetManifestUrl)
        STUB(AppCacheLookup)
        STUB(CommitUrlCacheEntryA)
        STUB(CommitUrlCacheEntryBinaryBlob)
        STUB(CommitUrlCacheEntryW)
        STUB(CreateMD5SSOHash)
        STUB(CreateUrlCacheContainerA)
        STUB(CreateUrlCacheContainerW)
        STUB(CreateUrlCacheEntryA)
        STUB(CreateUrlCacheEntryExW)
        STUB(CreateUrlCacheEntryW)
        STUB(CreateUrlCacheGroup)
        STUB(DeleteIE3Cache)
        STUB(DeleteUrlCacheContainerA)
        STUB(DeleteUrlCacheContainerW)
        STUB(DeleteUrlCacheEntry)
        STUB(DeleteUrlCacheEntryA)
        STUB(DeleteUrlCacheEntryW)
        STUB(DeleteUrlCacheGroup)
        STUB(DeleteWpadCacheForNetworks)
        STUB(DetectAutoProxyUrl)
        STUB(DispatchAPICall)
        STUB(DllCanUnloadNow)
        STUB(DllGetClassObject)
        STUB(DllInstall)
        STUB(DllRegisterServer)
        STUB(DllUnregisterServer)
        STUB(FindCloseUrlCache)
        STUB(FindFirstUrlCacheContainerA)
        STUB(FindFirstUrlCacheContainerW)
        STUB(FindFirstUrlCacheEntryA)
        STUB(FindFirstUrlCacheEntryExA)
        STUB(FindFirstUrlCacheEntryExW)
        STUB(FindFirstUrlCacheEntryW)
        STUB(FindFirstUrlCacheGroup)
        STUB(FindNextUrlCacheContainerA)
        STUB(FindNextUrlCacheContainerW)
        STUB(FindNextUrlCacheEntryA)
        STUB(FindNextUrlCacheEntryExA)
        STUB(FindNextUrlCacheEntryExW)
        STUB(FindNextUrlCacheEntryW)
        STUB(FindNextUrlCacheGroup)
        STUB(ForceNexusLookup)
        STUB(ForceNexusLookupExW)
        STUB(FreeUrlCacheSpaceA)
        STUB(FreeUrlCacheSpaceW)
        STUB(FtpCommandA)
        STUB(FtpCommandW)
        STUB(FtpCreateDirectoryA)
        STUB(FtpCreateDirectoryW)
        STUB(FtpDeleteFileA)
        STUB(FtpDeleteFileW)
        STUB(FtpFindFirstFileA)
        STUB(FtpFindFirstFileW)
        STUB(FtpGetCurrentDirectoryA)
        STUB(FtpGetCurrentDirectoryW)
        STUB(FtpGetFileA)
        STUB(FtpGetFileEx)
        STUB(FtpGetFileSize)
        STUB(FtpGetFileW)
        STUB(FtpOpenFileA)
        STUB(FtpOpenFileW)
        STUB(FtpPutFileA)
        STUB(FtpPutFileEx)
        STUB(FtpPutFileW)
        STUB(FtpRemoveDirectoryA)
        STUB(FtpRemoveDirectoryW)
        STUB(FtpRenameFileA)
        STUB(FtpRenameFileW)
        STUB(FtpSetCurrentDirectoryA)
        STUB(FtpSetCurrentDirectoryW)
        STUB(GetProxyDllInfo)
        STUB(GetUrlCacheConfigInfoA)
        STUB(GetUrlCacheConfigInfoW)
        STUB(GetUrlCacheEntryBinaryBlob)
        STUB(GetUrlCacheEntryInfoA)
        STUB(GetUrlCacheEntryInfoExA)
        STUB(GetUrlCacheEntryInfoExW)
        STUB(GetUrlCacheEntryInfoW)
        STUB(GetUrlCacheGroupAttributeA)
        STUB(GetUrlCacheGroupAttributeW)
        STUB(GetUrlCacheHeaderData)
        STUB(GopherCreateLocatorA)
        STUB(GopherCreateLocatorW)
        STUB(GopherFindFirstFileA)
        STUB(GopherFindFirstFileW)
        STUB(GopherGetAttributeA)
        STUB(GopherGetAttributeW)
        STUB(GopherGetLocatorTypeA)
        STUB(GopherGetLocatorTypeW)
        STUB(GopherOpenFileA)
        STUB(GopherOpenFileW)
        STUB(HttpAddRequestHeadersA)
        STUB(HttpAddRequestHeadersW)
        STUB(HttpCheckDavCompliance)
        STUB(HttpCloseDependencyHandle)
        STUB(HttpDuplicateDependencyHandle)
        STUB(HttpEndRequestA)
        STUB(HttpEndRequestW)
        STUB(HttpGetServerCredentials)
        STUB(HttpGetTunnelSocket)
        STUB(HttpIndicatePageLoadComplete)
        STUB(HttpIsHostHstsEnabled)
        STUB(HttpOpenDependencyHandle)
        STUB(HttpOpenRequestA)   // MinHook patches the real one, stub just gets us there
        STUB(HttpOpenRequestW)
        STUB(HttpPushClose)
        STUB(HttpPushEnable)
        STUB(HttpPushWait)
        STUB(HttpQueryInfoA)
        STUB(HttpQueryInfoW)
        STUB(HttpSendRequestA)
        STUB(HttpSendRequestExA)
        STUB(HttpSendRequestExW)
        STUB(HttpSendRequestW)
        STUB(HttpWebSocketClose)
        STUB(HttpWebSocketCompleteUpgrade)
        STUB(HttpWebSocketQueryCloseStatus)
        STUB(HttpWebSocketReceive)
        STUB(HttpWebSocketSend)
        STUB(HttpWebSocketShutdown)
        STUB(IncrementUrlCacheHeaderData)
        STUB(InternetAlgIdToStringA)
        STUB(InternetAlgIdToStringW)
        STUB(InternetAttemptConnect)
        STUB(InternetAutodial)
        STUB(InternetAutodialCallback)
        STUB(InternetAutodialHangup)
        STUB(InternetCanonicalizeUrlA)
        STUB(InternetCanonicalizeUrlW)
        STUB(InternetCheckConnectionA)
        STUB(InternetCheckConnectionW)
        STUB(InternetClearAllPerSiteCookieDecisions)
        STUB(InternetCloseHandle)
        STUB(InternetCombineUrlA)
        STUB(InternetCombineUrlW)
        STUB(InternetConfirmZoneCrossing)
        STUB(InternetConfirmZoneCrossingA)
        STUB(InternetConfirmZoneCrossingW)
        STUB(InternetConnectA)   // MinHook patches the real one
        STUB(InternetConnectW)
        STUB(InternetConvertUrlFromWireToWideChar)
        STUB(InternetCrackUrlA)
        STUB(InternetCrackUrlW)
        STUB(InternetCreateUrlA)
        STUB(InternetCreateUrlW)
        STUB(InternetDial)
        STUB(InternetDialA)
        STUB(InternetDialW)
        STUB(InternetEnumPerSiteCookieDecisionA)
        STUB(InternetEnumPerSiteCookieDecisionW)
        STUB(InternetErrorDlg)
        STUB(InternetFindNextFileA)
        STUB(InternetFindNextFileW)
        STUB(InternetFortezzaCommand)
        STUB(InternetFreeCookies)
        STUB(InternetFreeProxyInfoList)
        STUB(InternetGetCertByURL)
        STUB(InternetGetCertByURLA)
        STUB(InternetGetConnectedState)
        STUB(InternetGetConnectedStateEx)
        STUB(InternetGetConnectedStateExA)
        STUB(InternetGetConnectedStateExW)
        STUB(InternetGetCookieA)
        STUB(InternetGetCookieEx2)
        STUB(InternetGetCookieExA)
        STUB(InternetGetCookieExW)
        STUB(InternetGetCookieW)
        STUB(InternetGetLastResponseInfoA)
        STUB(InternetGetLastResponseInfoW)
        STUB(InternetGetPerSiteCookieDecisionA)
        STUB(InternetGetPerSiteCookieDecisionW)
        STUB(InternetGetProxyForUrl)
        STUB(InternetGetSecurityInfoByURL)
        STUB(InternetGetSecurityInfoByURLA)
        STUB(InternetGetSecurityInfoByURLW)
        STUB(InternetGoOnline)
        STUB(InternetGoOnlineA)
        STUB(InternetGoOnlineW)
        STUB(InternetHangUp)
        STUB(InternetInitializeAutoProxyDll)
        STUB(InternetLockRequestFile)
        STUB(InternetOpenA)
        STUB(InternetOpenUrlA)
        STUB(InternetOpenUrlW)
        STUB(InternetOpenW)
        STUB(InternetQueryDataAvailable)
        STUB(InternetQueryFortezzaStatus)
        STUB(InternetQueryOptionA)
        STUB(InternetQueryOptionW)
        STUB(InternetReadFile)
        STUB(InternetReadFileExA)
        STUB(InternetReadFileExW)
        STUB(InternetSecurityProtocolToStringA)
        STUB(InternetSecurityProtocolToStringW)
        STUB(InternetSetCookieA)
        STUB(InternetSetCookieEx2)
        STUB(InternetSetCookieExA)
        STUB(InternetSetCookieExW)
        STUB(InternetSetCookieW)
        STUB(InternetSetDialState)
        STUB(InternetSetDialStateA)
        STUB(InternetSetDialStateW)
        STUB(InternetSetFilePointer)
        STUB(InternetSetOptionA)
        STUB(InternetSetOptionExA)
        STUB(InternetSetOptionExW)
        STUB(InternetSetOptionW)
        STUB(InternetSetPerSiteCookieDecisionA)
        STUB(InternetSetPerSiteCookieDecisionW)
        STUB(InternetSetSecureLegacyServersAppCompat)
        STUB(InternetSetStatusCallback)
        STUB(InternetSetStatusCallbackA)
        STUB(InternetSetStatusCallbackW)
        STUB(InternetShowSecurityInfoByURL)
        STUB(InternetShowSecurityInfoByURLA)
        STUB(InternetShowSecurityInfoByURLW)
        STUB(InternetTimeFromSystemTime)
        STUB(InternetTimeFromSystemTimeA)
        STUB(InternetTimeFromSystemTimeW)
        STUB(InternetTimeToSystemTime)
        STUB(InternetTimeToSystemTimeA)
        STUB(InternetTimeToSystemTimeW)
        STUB(InternetUnlockRequestFile)
        STUB(InternetWriteFile)
        STUB(InternetWriteFileExA)
        STUB(InternetWriteFileExW)
        STUB(IsHostInProxyBypassList)
        STUB(IsUrlCacheEntryExpiredA)
        STUB(IsUrlCacheEntryExpiredW)
        STUB(LoadUrlCacheContent)
        STUB(ParseX509EncodedCertificateForListBoxEntry)
        STUB(PrivacyGetZonePreferenceW)
        STUB(PrivacySetZonePreferenceW)
        STUB(ReadUrlCacheEntryStream)
        STUB(ReadUrlCacheEntryStreamEx)
        STUB(RegisterUrlCacheNotification)
        STUB(ResumeSuspendedDownload)
        STUB(RetrieveUrlCacheEntryFileA)
        STUB(RetrieveUrlCacheEntryFileW)
        STUB(RetrieveUrlCacheEntryStreamA)
        STUB(RetrieveUrlCacheEntryStreamW)
        STUB(RunOnceUrlCache)
        STUB(SetUrlCacheConfigInfoA)
        STUB(SetUrlCacheConfigInfoW)
        STUB(SetUrlCacheEntryGroup)
        STUB(SetUrlCacheEntryGroupA)
        STUB(SetUrlCacheEntryGroupW)
        STUB(SetUrlCacheEntryInfoA)
        STUB(SetUrlCacheEntryInfoW)
        STUB(SetUrlCacheGroupAttributeA)
        STUB(SetUrlCacheGroupAttributeW)
        STUB(SetUrlCacheHeaderData)
        STUB(ShowCertificate)
        STUB(ShowClientAuthCerts)
        STUB(ShowSecurityInfo)
        STUB(ShowX509EncodedCertificate)
        STUB(UnlockUrlCacheEntryFile)
        STUB(UnlockUrlCacheEntryFileA)
        STUB(UnlockUrlCacheEntryFileW)
        STUB(UnlockUrlCacheEntryStream)
        STUB(UpdateUrlCacheContentPath)
        STUB(UrlCacheCheckEntriesExist)
        STUB(UrlCacheCloseEntryHandle)
        STUB(UrlCacheContainerSetEntryMaximumAge)
        STUB(UrlCacheCreateContainer)
        STUB(UrlCacheFindFirstEntry)
        STUB(UrlCacheFindNextEntry)
        STUB(UrlCacheFreeEntryInfo)
        STUB(UrlCacheFreeGlobalSpace)
        STUB(UrlCacheGetContentPaths)
        STUB(UrlCacheGetEntryInfo)
        STUB(UrlCacheGetGlobalCacheSize)
        STUB(UrlCacheGetGlobalLimit)
        STUB(UrlCacheReadEntryStream)
        STUB(UrlCacheReloadSettings)
        STUB(UrlCacheRetrieveEntryFile)
        STUB(UrlCacheRetrieveEntryStream)
        STUB(UrlCacheServer)
        STUB(UrlCacheSetGlobalLimit)
        STUB(UrlCacheUpdateEntryExtraData)
        STUB(UrlZonesDetach)

        // Leading underscore name needs a manual export alias
        __declspec(dllexport) __declspec(naked) void _GetFileExtensionFromUrl()
    {
        __asm { jmp dword ptr[fp_GetFileExtensionFromUrl] }
    }
}