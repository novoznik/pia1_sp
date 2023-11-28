#include "Cesta.h"

using namespace std;

void insertPoint(vector<string>& Ppoint){
    string coordinate;
    int i=0;
    cout<< "Zapiště souřadnice bodů ve tvaru: X.XXXXXX,Y.YYYYYY; pro zastavení napiště 'stop'"<<endl;
    for(;;){
        cin>>coordinate;
        Ppoint.push_back(coordinate);
        if(coordinate=="stop")
        {
            Ppoint.pop_back(); //NE REBOTAET
            break;
        }
        i++;
    }
}

// Функция для обработки ответа
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *s) {
    s->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Основная функция для отправки запроса
string sendRequest(const string& url) {
    CURL *curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init(); //vytvoreni spojeni se serverem
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); //nastaveni spojeni, CURLOPT_URL - konstanta nastaveni spojeni, url.c_str - URL adresa
        //cout<<endl<<endl<<"url.c_str()"<<url.c_str()<<endl<<endl;
        //cout<<endl<<endl<<"CURLOPT_URL"<<CURLOPT_URL<<endl<<endl;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        // Отключение проверки SSL
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        // Проверка на ошибки
        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        }
    }
    return readBuffer;
}
