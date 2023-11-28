#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json.hpp>
#include "Cesta.h"

using namespace std;

int main() {

    vector<string> point; //vector obsahujicí souřadnice bodů

    insertPoint(point); //zapis souřadnic do vectoru

    int N = point.size();
    //cout<<N<<endl;

    //for(int i=0; i<=N; i++)
      //  cout<<i<<" element "<<point[i]<<endl;

    for(int i=0; i<N-1; i++){
        for(int j=i+1; j<N; j++)
        {
            int p = i+1, f = j+1;
            cout<<endl<<"výpis dat mezi "<<p<<" a "<<f<<" body:"<<endl;
    // Ваши координаты и API-ключ  ("8.681495,49.41461", "8.687872,49.420318"; "8.684683,49.417464")
           // string point(i) = "8.681495,49.41461";
           // string point(j) = "8.687872,49.420318";
            string apiKey = "5b3ce3597851110001cf624805eac538c6a2478f82f8d444f5dd44ff";

    // Формируем URL
            string url = "https://api.openrouteservice.org/v2/directions/driving-car?api_key=" + apiKey + "&start=" + point[i] + "&end=" + point[j];

    // Отправляем запрос и получаем ответ
            string response = sendRequest(url);

    // Здесь добавьте разбор JSON-ответа и извлечение нужных данных

            cout << "Response: " << response << endl;

    // Используйте std::string response, который вы получили от сервера
            nlohmann::json jsonResponse = nlohmann::json::parse(response);

    // Извлекаем расстояние
            double distance = jsonResponse["features"][0]["properties"]["segments"][0]["distance"].get<double>();

            cout << "Distance: " << distance << " meters" << endl;
        }
    }
    return 0;
}

