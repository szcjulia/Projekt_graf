#include "binar.h"
#include "graf.h"
#include <stdio.h>


void zapisz_bin(Wierzcholek* pierwszy_wierzcholek, char* nazwaPliku){

    FILE *plikBin = NULL;
    plikBin = fopen(nazwaPliku, "wb");
    if(plikBin == NULL || ferror(plikBin)){
        printf("Nie mozna otworzyc pliku\n");
        return;
    }

    Wierzcholek *obecny_wierzcholek = pierwszy_wierzcholek;
    while(obecny_wierzcholek)
    {
        fprintf(plikBin, "%u\n", obecny_wierzcholek->etykieta);
        obecny_wierzcholek = obecny_wierzcholek->nastepny_wierzcholek;
    }
    fclose(plikBin);

    printf("Zapisano do pliku '%s'\n", nazwaPliku);
}