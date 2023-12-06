#ifndef CESTA_H_INCLUDED
#define CESTA_H_INCLUDED

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json.hpp>
#include <vector>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void insertPoint(vector<pair<string,string>>& locallocations);
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *s); // Funkce pro zpracování odpovědi přijaté z HTTP požadavku
string sendRequest(const string& url); //Funkce pro odeslání požadavku

double calculateTotalDistance(const vector<vector<double>>& graph, const vector<int>& path);

#endif // CESTA_H_INCLUDED
