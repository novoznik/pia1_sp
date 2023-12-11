## TSP

Tato aplikace na C++ řeší úlohu obchodního cestujícího (TSP - Travelling Salesman Problem) využitím OpenRouteService API pro výpočet vzdáleností mezi zadanými geografickými body. Umožňuje uživatelům zadávat názvy a GPS souřadnice míst a následně vypočítává optimální trasu pro návštěvu všech těchto míst. 
Aplikace vyžaduje aktivní připojení k internetu pro přístup k OpenRouteService API.


## Návod k instalaci

Pro kompilaci a spuštění aplikace je potřeba mít:

-   Kompilátor C++.
-   Knihovnu [libcurl](https://curl.se/download.html) pro práci s HTTP požadavky.
-   Knihovnu [nlohmann/json](https://github.com/nlohmann/json) pro zpracování JSON.

V případě použítí Code::Blocks stačí umístit knihovny do složky projektu pod \lib\curl a \lib\json. Otevřete soubor projektu .cbp v Code::Blocks a spusťte build projektu.

## Příklad instalace pro knihovnu libcurl:

1. Z webové stránky https://curl.se/download.html stáhnout curl-8.5.0.zip (případně jinou verzi)
2. Ve složce s projektem (kde umístěn soubor Cesta.cbp) vytvořit novou složku lib, v ní vytvořit složku curl
3. Do složky lib\curl přemístit soubory z archivu curl-8.5.0.zip 
Stejný postup platí i pro knihovnu nlohmann/json.

## Návod k použití

1.  Spusťte program.
2.  Program vás vyzve k zadání názvu a souřadnic pro každé místo (ve složce projektu je textový soubor obsahující příklady souřádnic).
3.  Po zadání všech míst zadejte příkaz `end`.
4.  Aplikace vypočítá a zobrazí optimální trasu mezi všemi místy a poskytne celkovou vzdálenost.
