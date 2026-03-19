#pragma once
#include <string>
#include <windows.h>
#include <wininet.h>

void TransformInit();
void StoreRequestData(HINTERNET hRequest, const std::string& action, const std::string& query);
bool ConsumeJsonBody(HINTERNET hRequest, char** outBuf, DWORD* outLen);
void ClearRequestData(HINTERNET hRequest);
bool HasStoredAction(HINTERNET hRequest);
void UpdateStoredQuery(HINTERNET hRequest, const std::string& query);