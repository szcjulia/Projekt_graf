#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include "graf.h"
#include "obsluga_wejscia.h"
#include "kolorowanie.h"

int main(){

    int opcja = 0;
    Wierzcholek *pierwszy = NULL;
    uint32_t etWie1 = 0;
    uint32_t etWie2 = 0;
    char nazwaPliku[ROZM_NAZWY_PLIKU];

    for(;;)
    {
        opcja = wybor(&etWie1, &etWie2, nazwaPliku);
        
        switch (opcja)
        {
            case DOD_WIE:
                if(dodaj_wierzcholek(&pierwszy, etWie1) == ADD_NODE_FAIL) printf("Fail\n");
                else printf("Success\n");
                break;

            case DOD_KRA:
                if(dodaj_krawedz(pierwszy, etWie1, etWie2) == ADD_EDGE_FAIL) printf("Fail\n");
                else printf("Success\n");
                break;

            case KOLOR:
                kolorowanie(pierwszy, nazwaPliku);
                break;

            case EXIT:
                return(0);
                break;

            default:
                break;
        }
    }
}