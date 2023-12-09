#include "Cesta.h"

using namespace std;

void insertPoint(vector<string>& locallocations, vector<string>& localNames){
    string name, coordinates;
    while(true) {
        cout << "Napiste nazev bodu(nazev by se mel skladat pouze z jednoho slova), pro zastaveni napiste 'end': ";
        cin >> name;
        localNames.push_back(name); // zápis názvu bodu do vektoru
        if (name == "end") {
            break; // podminka pro zastávení vstupu
        }
        cout << "Zapiste souradnice (delka, sirka) bodu " << name << " (ve tvaru: X.XXXXXX,Y.YYYYYY): ";
        cin >> coordinates; // zápis souřadnic ve formatu "šířka,délka". Problém spočívá v tom, že v URL-adrese
                            //... souřadnice by měly být zapsány ve tvaru "délka,šířka".

        int n = coordinates.find(','); // číslo pozice na které se nachází čárka
        string coordinate1; // proměnná, do které se bude zapisovat šířka
        string coordinate2; // proměnná, do které se bude zapisovat délka
        for (int i = 0; i < n; i++){
            if (i == 0)
                coordinate1 = coordinates[i];
            else
                coordinate1 += coordinates[i]; // zapisujeme každý symbol do čárky
        }
        for (int i = n + 1; i < coordinates.size(); i++){
            if (i == n + 1)
                coordinate2 = coordinates[i];
            else
                coordinate2 += coordinates[i]; // zapisujeme každý symbol po čárce
        }
        coordinates = coordinate2 + "," + coordinate1; // spojujeme

        locallocations.push_back(coordinates); // zápis souřadnic do vektoru
    }
}

void insertMatrix(vector<vector<double>>& localgraphdistance,vector<string>& locallocations,const string apiKey) {
    int n = locallocations.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue; // přeskočení párů stejných bodů pro vytváření matice s nulovými hodnoty na diagonále

            // URL pro ziskání dat z Openrouteservice
            string url = "https://api.openrouteservice.org/v2/directions/driving-car?api_key=" + apiKey + "&start=" + locallocations[i] + "&end=" + locallocations[j];

            // Odeslání dotazu a přijetí odpovědi
            string response = sendRequest(url);

            // Zpracování JSON odpovědi
            nlohmann::json jsonResponse = nlohmann::json::parse(response);

            // Extrahování vzdáleností z odpovědi
            double distance = jsonResponse["features"][0]["properties"]["segments"][0]["distance"].get<double>();


            // Uložení dat do matice
            localgraphdistance[i][j] = distance;
        }
    }
}

void ShortestWay(double& minDistance, vector<int>& minPath, vector<vector<double>>& localgraphdistance,const int n){
    // Inicializace cesty (pořadí bodů)
    vector<int> path(n); // vytváření vektoru, který obsahuje pořádí bodů zkoumané cesty
    for (int i = 0; i < n; i++)
        path[i] = i;
        // Procházení všech možných cest
        do {
        // Výpočet délky aktuální trasy
        double currentDistance = calculateTotalDistance(localgraphdistance, path);
        // Kontrola, zda je aktuální trasa nejkratší
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
            minPath = path;
        }
    }
    // Další permutace trasy
     while (next_permutation(path.begin(), path.end())); // do... while(next_permutation(path.begin,path.end)) je funkce C++,
     //... která mění pořádí prvků ve vektoru path při každém puštění cyklu. Když při prvním puštění cyklu vektor path vypadal následovně {1,2,3...},
     //... při druhém puštění cyklu vektor path bude vypadat už jako {2,1,3...} atd.
}

double calculateTotalDistance(const vector<vector<double>>& graph, const vector<int>& path) {
    double totalDistance = 0.0;
    // Procházení všech po sobě jdoucích párů míst na cestě
    for (int i = 0; i < path.size() - 1; ++i) {
        // Součet vzdáleností mezi místy
        totalDistance += graph[path[i]][path[i + 1]];
    }
    // Přidání vzdálenosti od posledního místa zpět k prvnímu
    totalDistance += graph[path.back()][path[0]];
    return totalDistance;
}

void Navigation(vector<int>& minPath,const string apiKey, vector<string>& locallocations, vector<string>& localNames) {
        for (int i = 0; i < minPath.size(); i++){
            string url;
            bool last = (i == minPath.size() - 1);
            if (last) // pro případ mezi posledním a prvním bodem
            {
                // URL pro ziskání dat z Openrouteservice
                url = "https://api.openrouteservice.org/v2/directions/driving-car?api_key=" + apiKey + "&start=" + locallocations[i] + "&end=" + locallocations[0];
            }
            else {
                // URL pro ziskání dat z Openrouteservice
                url = "https://api.openrouteservice.org/v2/directions/driving-car?api_key=" + apiKey + "&start=" + locallocations[i] + "&end=" + locallocations[i + 1];
            }
            // Odeslání dotazu a přijetí odpovědi
            string response = sendRequest(url);
            // Zpracování JSON odpovědi
            nlohmann::json jsonResponse = nlohmann::json::parse(response);
            // Extraxování navigace z odpovědi do pole directions
            auto directions = jsonResponse["features"][0]["properties"]["segments"][0]["steps"];

            if (last) {
            cout << endl << "Path between " << localNames[minPath[i]] << " and " << localNames[minPath[0]] << ":" << endl;
            }
            else {
            cout << endl << "Path between " << localNames[minPath[i]] << " and " << localNames[minPath[i+1]] << ":" << endl;
            }
            // Vypis informace o cestě z pole directions do proměnné string instruction
            for (const auto& step : directions) {
                string instruction = step["instruction"].get<string>();
                cout << instruction << endl;
        }
    }
}

//////////////////////// Funkce pro práci se serverem Openrouteservice  ////////////////////////
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *s) {
    s->append((char*)contents, size * nmemb); // přidání přijatých dat do řetězce
    return size * nmemb; // vracení celkové velikosti zpracovaných dat
}

string sendRequest(const string& url) {
    CURL *curl;
    CURLcode res;
    string readBuffer; // řetězec pro uložení přijatých dat

    curl = curl_easy_init(); // inicializace cURL

    if(curl) { // kontrola inicializace

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
        // uvolnění zdrojů
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}
