#ifndef OBSLUGA_WEJSCIA_H
#define OBSLUGA_WEJSCIA_H
#include "graf.h"
#include <stdint.h>

#define ROZM_SLOWA 30
#define ROZM_LINII 50
#define ROZM_NAZWY_PLIKU 50

#define NIEPRAWIDLOWY_INPUT (-1)
#define DOD_WIE 1
#define DOD_KRA 2
#define KOLOR 3
#define US_KRA 4
#define US_WIE 5

#define EXIT 9
#define DODAJ 10
#define KOLORUJ 11
#define USUN 12

char* usuwanie_spacji(char* linijka);
char* zamiana_interpunkcji_na_spacje(char* linijka);
void bledne_wprowadzenie_funkcji();
int czytaj_opcje(char* slowo);
void wybierz_opcje(int* opcja, uint32_t* etWie1, uint32_t* etWie2, char* nazwaPliku);
int wybor(uint32_t* etWie1, uint32_t* etWie2, char* nazwaPliku);


#endif //OBSLUGA_WYJSCIA_H