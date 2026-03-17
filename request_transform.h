#pragma once
#include <windows.h>
#include <string>
#include <wininet.h>

void  TransformInit();
std::string RewriteToSingleEndpoint(const char* objectName); // always returns "/request"
void  StoreRequestData(HINTERNET hRequest, const std::string& action, const std::string& query);
bool  ConsumeJsonBody(HINTERNET hRequest, std::string& outJson);
void  ClearRequestData(HINTERNET hRequest);
// request_transform.h — add these two
bool HasStoredAction(HINTERNET hRequest);
void UpdateStoredQuery(HINTERNET hRequest, const std::string& query);