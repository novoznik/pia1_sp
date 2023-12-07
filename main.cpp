#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json.hpp>
#include "Cesta.h"

using namespace std;

int main() {

    vector<pair<string,string>> locations; //vektor obsahujicí souřadnice bodů
    vector<string> locationNames;

    insertPoint(locations); //zapis uživatelských dat (název a souřadnice) do vektoru

    // zapis názvů míst do vektoru
    for (const auto& location : locations) {
        locationNames.push_back(location.first);
    }

    int n = locations.size();
    vector<vector<double>> graphduration(n, vector<double>(n, 0.0)); //matice se vzdalenostmi mezi každými páry bodů
    vector<vector<double>> graphdistance(n, vector<double>(n, 0.0)); //matice s dobou cesty mezi každými páry bodů

    string apiKey = "5b3ce3597851110001cf624805eac538c6a2478f82f8d444f5dd44ff";

    // extrahování vzdalenosti a doby trvání cesty mezi každým párem bodů
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue; // Přeskočení páru stejných bodů

            // URL pro ziskání dat z Openrouteservice
            string url = "https://api.openrouteservice.org/v2/directions/driving-car?api_key=" + apiKey + "&start=" + locations[i].second + "&end=" + locations[j].second;

            // Odeslání dotazu a přijetí odpovědi
            string response = sendRequest(url);


            // Zpracování JSON odpovědi
            nlohmann::json jsonResponse = nlohmann::json::parse(response);
            // Extrahování doby trvání z odpovědi
            double duration = jsonResponse["features"][0]["properties"]["segments"][0]["duration"].get<double>();
            // Extrahování doby trvání z odpovědi
            double distance = jsonResponse["features"][0]["properties"]["segments"][0]["distance"].get<double>();

            // Uložení dat do matic
            graphduration[i][j] = duration;
            graphdistance[i][j] = distance;
        }
    }

    // Inicializace cesty (pořadí míst)
    vector<int> path(n);
    for (int i = 0; i < n; i++) {
        path[i] = i;
    }

    double minDistance = 10000000;
    vector<int> minPath;

    // Procházení všech možných cest
    do {
        // Výpočet délky aktuální trasy
        double currentDistance = calculateTotalDistance(graphdistance, path);
        // Kontrola, zda je aktuální trasa nejkratší
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
            minPath = path;
        }
    }
    // Další permutace trasy
     while (next_permutation(path.begin(), path.end()));

    // Výpis nejkratší trasy a její délky
    cout << "Distance: " << minDistance <<  " metru" << endl;
    cout << "Path: ";
    for (int i : minPath) {
        cout << locationNames[i] << " -> ";
    }
    cout << endl;

    return 0;
}

