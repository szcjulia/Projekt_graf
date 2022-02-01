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

void kolorowanie(Wierzcholek* pierwszy_wierzcholek){
    Wierzcholek* obecny_wierzcholek = pierwszy_wierzcholek;
    while (obecny_wierzcholek){
        obecny_wierzcholek->kolor = -1;
        obecny_wierzcholek = obecny_wierzcholek->nastepny_wierzcholek;
    }

    obecny_wierzcholek = pierwszy_wierzcholek;
    while (obecny_wierzcholek){
        if (obecny_wierzcholek->kolor == -1){
            obecny_wierzcholek->kolor = najmniejszy_kolor(obecny_wierzcholek->pierwszy_sasiad);
            printf("> wierzcholek %u: kolor %d\n", obecny_wierzcholek->etykieta, obecny_wierzcholek->kolor);
            obecny_wierzcholek = obecny_wierzcholek->nastepny_wierzcholek;
        }
    }
}
