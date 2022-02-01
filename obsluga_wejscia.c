#include "obsluga_wejscia.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "graf.h"
#include "bledy.h"

char* usuwanie_spacji(char* linijka) 
{
    int p = -1, q = 0;
    while (linijka[++p] != '\0') {
        if (isspace(linijka[p]) == 0) 
           linijka[q++] = linijka[p];
    }
    linijka[q] = '\0';
 
    return linijka;
}

char* zamiana_interpunkcji_na_spacje(char* linijka) 
{

    int p=-1;
    while (linijka[++p] != '\0') {
        if (linijka[p] == ',' || linijka[p] == ':') 
           linijka[p]=' ';
    }
    return linijka;
}

void wczytywanie_polecen(char* linijka) {

    int p = 0;   
    while (linijka[p] != '\0') {
        if (linijka[p] == 'D') 
            printf(" to d ");
        else
            printf("%c",linijka[p]);
        p++;
    }
}

void bledne_wprowadzenie_funkcji(){
			printf("Bląd wprowadzenie pamieci!\n");
}

int wybor(uint32_t* etWie1, uint32_t* etWie2){
    int opcja = NIEPRAWIDLOWY_INPUT;

    for(;;)
    {
        wybierz_opcje(&opcja, etWie1, etWie2);
        if(opcja != NIEPRAWIDLOWY_INPUT) return opcja;
    } 
}


void wybierz_opcje(int* opcja, uint32_t* etWie1, uint32_t* etWie2)
{
    char slowo[ROZM_SLOWA];
    char linia[ROZM_LINII];

    if (gets(linia))
    {

        if (sscanf(linia, "%s", slowo)) 
        {
            if (strcmp(slowo, "run") && strcmp(slowo, "list") && strcmp(slowo, "dump") && strcmp(slowo, "save"))
            {
                usuwanie_spacji(linia);
                zamiana_interpunkcji_na_spacje(linia);
            }
        }
        

        if (sscanf(linia, "%s", slowo))
        {
            *opcja = czytaj_opcje(slowo);
            switch (*opcja)
            {
                case EXIT: return;
                case DODAJ:
                    if (3 == sscanf(linia, "%s %lu %lu", slowo, etWie1, etWie2))
                    {
                        *opcja = DOD_KRA;
                        return;
                    }
                    if (2 == sscanf(linia, "%s %lu", slowo, etWie1, etWie2))
                    {
                        *opcja = DOD_WIE;
                        return;
                    }
                    *opcja = NIEPRAWIDLOWY_INPUT;
                    break;
                default:
                    *opcja = NIEPRAWIDLOWY_INPUT;
                    break;
            }
        }
    }  
}

int czytaj_opcje(char* slowo)
{
    if (!strcmp(slowo, "exit")) return EXIT; 
    if (!strcmp(slowo, "a")) return DODAJ; 

    else return NIEPRAWIDLOWY_INPUT;
}

