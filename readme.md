﻿## TSP

Tato aplikace na C++ řeší úlohu obchodního cestujícího (TSP - Travelling Salesman Problem) využitím OpenRouteService API pro výpočet vzdáleností a doby jízdy mezi zadanými geografickými body. Umožňuje uživatelům zadávat názvy a GPS koordináty míst a následně vypočítává optimální trasu pro návštěvu všech těchto míst. 
Aplikace vyžaduje aktivní připojení k internetu pro přístup k OpenRouteService API.


## Návod k instalaci

Pro kompilaci a spuštění aplikace je potřeba mít:

-   Kompilátor C++.
-   Knihovnu [libcurl](https://curl.se/download.html) pro práci s HTTP požadavky.
-   Knihovnu [nlohmann/json](https://github.com/nlohmann/json) pro zpracování JSON.

Stáhněte knihovny a přidejte do projektu. 

## Návod k použití

1.  Spusťte program.
2.  Program vás vyzve k zadání názvu a koordinát pro každé místo.
3.  Po zadání všech míst zadejte příkaz `end`.
4.  Aplikace vypočítá a zobrazí optimální trasu mezi všemi body a poskytne přibližnou dobu jízdy a vzdálenosti.
