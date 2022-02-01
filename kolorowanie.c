#include "kolorowanie.h"
#include <stdio.h>

int sprobuj_kolor(Sasiad* pierwszy_sasiad, int kolor){
    Sasiad* obecny_sasiad = pierwszy_sasiad;
    while (obecny_sasiad){
        if (obecny_sasiad->wierzcholek->kolor == kolor){
            return 0;
        }
        obecny_sasiad = obecny_sasiad->nastepny_sasiad;
    }
    return 1;
}

int najmniejszy_kolor(Sasiad* pierwszy_sasiad){
    int kolor = 0;
    for (;;){
        if (sprobuj_kolor(pierwszy_sasiad, kolor)) return kolor;
        else kolor++;
    }
}

void kolorowanie(Wierzcholek* pierwszy_wierzcholek, char* nazwaPliku){
    if (!pierwszy_wierzcholek) return;

    int ileWierzcholkow = 0;
    Wierzcholek* obecny_wierzcholek = pierwszy_wierzcholek;
    while (obecny_wierzcholek){
        ileWierzcholkow++;

        obecny_wierzcholek->kolor = -1;
        obecny_wierzcholek = obecny_wierzcholek->nastepny_wierzcholek;
    }

    obecny_wierzcholek = pierwszy_wierzcholek;
    while (obecny_wierzcholek){
        if (obecny_wierzcholek->kolor == -1){
            obecny_wierzcholek->kolor = najmniejszy_kolor(obecny_wierzcholek->pierwszy_sasiad);
            obecny_wierzcholek = obecny_wierzcholek->nastepny_wierzcholek;
        }
    }


    FILE* f = fopen(nazwaPliku, "w");
    if (!f)
    {
        printf("Nie mozna otworzyc pliku\n");
        return;
    }

    uint32_t obecnaEtykieta = 0;
    for (int i = 0; i < ileWierzcholkow; i++){
        obecny_wierzcholek = pierwszy_wierzcholek;

        Wierzcholek* nastepny_wierzcholek = NULL;
        uint32_t nastepnaEtykieta = UINT32_MAX;

        while (obecny_wierzcholek) {
            if (obecny_wierzcholek->etykieta > obecnaEtykieta && obecny_wierzcholek->etykieta <= nastepnaEtykieta)
            {
                nastepnaEtykieta = obecny_wierzcholek->etykieta;
                nastepny_wierzcholek = obecny_wierzcholek;
            }
            obecny_wierzcholek = obecny_wierzcholek->nastepny_wierzcholek;
        }

        if (nastepny_wierzcholek) {
            fprintf(f, "%u: %d\n", nastepny_wierzcholek->etykieta, nastepny_wierzcholek->kolor);
            obecnaEtykieta = nastepnaEtykieta;
        }
    }

    fclose(f);
    printf("Zapisano do pliku '%s'\n", nazwaPliku);
}
