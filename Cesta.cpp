#include "Cesta.h"

using namespace std;

void insertPoint(vector<pair<string,string>>& locallocations){
    string name, coordinates;
    while(true) {
        cout << "Napiste nazev bodu, pro zastaveni napiste 'end': ";
        cin >> name;
        if (name == "end") {
            break;
        }
        cout << "Zapiste souradnice (delka, sirka) bodu " << name << " (ve tvaru: X.XXXXXX,Y.YYYYYY): ";
        cin >> coordinates;
        locallocations.push_back({name, coordinates});
    }
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *s) {
    s->append((char*)contents, size * nmemb); //přidání přijatých dat do řetězce
    return size * nmemb; //vracení celkové velikosti zpracovaných dat
}

string sendRequest(const string& url) {
    CURL *curl;
    CURLcode res;
    string readBuffer; //řetězec pro uložení přijatých dat

    curl = curl_easy_init(); //inicializace cURL

    if(curl) { //kontrola inicializace

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); //nastavení URL, kam bude požadavek odeslán
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); //nastavení funkce callback pro zápis přijatých dat
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer); //zápis dat do readBuffer

        // vypnutí ověřování SSL
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //ověřování SSL certifikátu
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); //ověřování hostname
        res = curl_easy_perform(curl); //výsledek operace

        // kontrola na chyby
        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        }
        //uvolnění zdrojů
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}

double calculateTotalDistance(const vector<vector<double>>& graph, const vector<int>& path) {
    double totalDistance = 0.0;
    // procházení všech po sobě jdoucích párů míst na cestě
    for (int i = 0; i < path.size() - 1; ++i) {
        // Součet vzdáleností mezi místa
        totalDistance += graph[path[i]][path[i + 1]];
    }
    // Přidání vzdálenosti od posledního místa zpět k prvnímu
    totalDistance += graph[path.back()][path[0]];
    return totalDistance;
}
