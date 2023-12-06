#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json.hpp>
#include "Cesta.h"

using namespace std;

int main() {

    vector<pair<string,string>> locations; //vector obsahujicí souřadnice bodů

    insertPoint(locations); //zapis souřadnic do vectoru

    int n = locations.size();
    vector<vector<double>> graphduration(n, vector<double>(n, 0.0));
    vector<vector<double>> graphdistance(n, vector<double>(n, 0.0));
    // Вычисление длительности поездки между каждой парой точек
    string apiKey = "5b3ce3597851110001cf624805eac538c6a2478f82f8d444f5dd44ff";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue; // Пропускаем одинаковые точки

            string url = "https://api.openrouteservice.org/v2/directions/driving-car?api_key=" + apiKey + "&start=" + locations[i].second + "&end=" + locations[j].second;
            string response = sendRequest(url);

            nlohmann::json jsonResponse = nlohmann::json::parse(response);
            double duration = jsonResponse["features"][0]["properties"]["segments"][0]["duration"].get<double>();
            // Извлекаем расстояние
            double distance = jsonResponse["features"][0]["properties"]["segments"][0]["distance"].get<double>();

            // Запись длительности в матрицу
            graphduration[i][j] = duration;
            graphdistance[i][j] = distance;
        }
    }

    vector<int> path(n);
    // Инициализация пути (последовательность городов)
    for (int i = 0; i < n; i++) {
        path[i] = i; //zamenit na name coordinates
    }

    double minDistance = 10000000;
    vector<int> minPath;

    // Перебор всех возможных маршрутов
    do {
        // Вычисление длины текущего маршрута
        double currentDistance = calculateTotalDistance(graphdistance, path);
        // Проверка, является ли текущий маршрут кратчайшим
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
            minPath = path;
        }
    // Переход к следующей перестановке маршрута
    } while (next_permutation(path.begin(), path.end()));

    // Вывод кратчайшего маршрута и его длины
    cout << "Distance: " << minDistance <<  " metru" << endl;
    cout << "Path: ";
    for (int i : minPath) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

