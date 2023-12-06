#include "Cesta.h"

using namespace std;

void insertPoint(vector<pair<string,string>>& locallocations){
    string name, coordinates;
    while(true) {
        cout << "Napiste nazev bodu, pro zastavení napiště 'end': ";
        cin >> name;
        cout << endl;
        if (name == "end") {
            break;
        }
        cout << "Zapiště souřadnice (delka, sirka) bodu " << name << " (ve tvaru: X.XXXXXX,Y.YYYYYY): ";
        cin >> coordinates;
        locallocations.push_back({name, coordinates});
    }
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *s) {
    s->append((char*)contents, size * nmemb); //přidání přijatých dat do řetězce
    return size * nmemb; //vracení celkové velikosti zpracovaných dat
}

// Основная функция для отправки запроса
string sendRequest(const string& url) {
    CURL *curl;
    CURLcode res;
    string readBuffer; //řetězec pro uložení přijatých dat

    curl = curl_easy_init(); //inicializace cURL

    if(curl) { //kontrola inicializace

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); //nastavení URL, kam bude požadavek odeslán
        //url.c_str() převádí std::string na C-řetězec, který vyžaduje cURL
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); //nastavení funkce callback pro zápis přijatých dat
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer); //zápis dat do readBuffer

        // vypnutí ověřování SSL
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //ověřování SSL certifikátu
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); //ověřování hostname
        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        }

        curl_easy_cleanup(curl);
    }

    return readBuffer;
}

// Функция для вычисления общей длины пути
double calculateTotalDistance(const vector<vector<double>>& graph, const vector<int>& path) {
    double totalDistance = 0.0;
    // Перебираем все пары последовательных городов в пути
    for (int i = 0; i < path.size() - 1; ++i) {
        // Суммируем расстояние между городами
        totalDistance += graph[path[i]][path[i + 1]];
    }
    // Добавляем расстояние от последнего города обратно к первому
    totalDistance += graph[path.back()][path[0]];
    return totalDistance;
}
