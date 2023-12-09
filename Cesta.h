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

void insertPoint(vector<string>& locallocations, vector<string>& localNames); // Funkce pro zapis uživatelem zadaných dat (název a souřadnice) do vektoru
void insertMatrix(vector<vector<double>>& localgraphdistance,vector<string>& locallocations,const string apiKey); //Funkce pro extrahování vzdáleností mezi body a jejich další zápis do matice graphdistance

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *s); // Funkce pro zpracování odpovědi přijaté z HTTP požadavku
string sendRequest(const string& url); //Funkce pro odeslání požadavku

void ShortestWay(double& minDistance, vector<int>& minPath, vector<vector<double>>& localgraphdistance,const int n); // Funkce pro hledání nejkratší cesty
double calculateTotalDistance(const vector<vector<double>>& graph, const vector<int>& path); // Funkce pro vypočet celkové délky kruhové cesty Path

void Navigation(vector<int>& minPath,const string apiKey, vector<string>& locallocations, vector<string>& localNames); // Funkce pro vypis navigace po cestě

#endif // CESTA_H_INCLUDED
