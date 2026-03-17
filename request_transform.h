#pragma once
#include <windows.h>
#include <wininet.h>
#include <string>

// Call once at startup before any hooks fire
void TransformInit();

// Call in Hook_HttpOpenRequestA:
// strips query string from path, rewrites path, returns clean path
// outQuery gets the raw query string to store after you have the handle
std::string RewritePath(const char* objectName, std::string& outQuery);

// Call in Hook_HttpOpenRequestA after fpHttpOpenRequestA returns:
// stores the query string keyed by the request handle
void StoreQuery(HINTERNET hRequest, const std::string& query);

// Call in Hook_HttpSendRequestA:
// builds JSON from stored params (encrypting password fields), clears stored data
// returns empty string if nothing was stored for this handle
std::string ConsumeJsonBody(HINTERNET hRequest);

// Call in Hook_InternetCloseHandle to avoid leaking map entries
void ClearRequestData(HINTERNET hRequest);