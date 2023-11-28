#ifndef CESTA_H_INCLUDED
#define CESTA_H_INCLUDED

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json.hpp>
#include <vector>

using namespace std;

void insertPoint(vector<string>& Ppoint);
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *s);
string sendRequest(const string& url);

#endif // CESTA_H_INCLUDED
