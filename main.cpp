#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json.hpp>
#include "Cesta.h"

using namespace std;

int main() {

    vector<string> locations; // vektor obsahujicí souřadnice bodů
    vector<string> locationNames; // vektor obsahujicí názvy bodů

    insertPoint(locations, locationNames); // zapis uživatelských dat (název a souřadnice) do vektorů

    int n = locations.size(); // počet bodů
    vector<vector<double>> graphdistance(n, vector<double>(n, 0.0)); // vytváření prázdné matice o rozměru nxn, pak do ní budou zapsané vzdalenosti mezi body

    string apiKey = "5b3ce3597851110001cf624805eac538c6a2478f82f8d444f5dd44ff"; // apiKey pro připojení do serveru OpenRouteService

    insertMatrix(graphdistance, locations, apiKey); // extrahování vzdáleností mezi body ze serveru OpenRouteService a jejich další zápis do matice graphdistance

    double minDistance = 10000000; // proměnná do které se pak zapiše minimální vzdálenost
    vector<int> minPath; // vektor, který pak bude obsahovat pořádí bodů nejkrátší cesty

    ShortestWay (minDistance, minPath, graphdistance, n); // funkce pro hledání nejkrátší cesty


    // Výpis nejkratší trasy a její délky
    cout << "Distance: " << minDistance <<  " meters" << endl;
    cout << "Path: ";

    for (int i = 0; i < minPath.size(); i++) {
        if (i == minPath.size() - 1)
            cout << locationNames[minPath[i]] << " -> " << locationNames[minPath[0]];
        else
            cout << locationNames[minPath[i]] << " -> ";
    }
    cout << endl;

    // Výpis navigace pro dánou cestu
    Navigation (minPath, apiKey, locations, locationNames);
    return 0;
}

