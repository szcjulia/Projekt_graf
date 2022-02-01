#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "graf.h"
#include "kolorowanie.h"
#include "bledy.h"


Wierzcholek* znajdz_wierzcholek(Wierzcholek* pierwszy_wierzcholek, uint32_t szukana_etykieta){
    Wierzcholek *obecny_wierzcholek = pierwszy_wierzcholek;
    while(obecny_wierzcholek){
        if(obecny_wierzcholek->etykieta == szukana_etykieta){
            return obecny_wierzcholek;
        }
        obecny_wierzcholek = obecny_wierzcholek->nastepny_wierzcholek;
    }
    return NULL;
}

int dodaj_wierzcholek(Wierzcholek** pierwszy_wierzcholek, uint32_t etykieta) {
    if(znajdz_wierzcholek(*pierwszy_wierzcholek, etykieta)) {
        return ADD_NODE_FAIL; //juz jest wierzcholek z taką etykietą
    } 
    Wierzcholek* nowyWierzcholek = NULL;
    nowyWierzcholek = (Wierzcholek*)malloc(sizeof(Wierzcholek));
    if(nowyWierzcholek!= NULL){
        nowyWierzcholek->nastepny_wierzcholek = *pierwszy_wierzcholek;
        nowyWierzcholek->etykieta = etykieta;
        nowyWierzcholek->pierwszy_sasiad = NULL;
        *pierwszy_wierzcholek = nowyWierzcholek;
        return ADD_NODE_SUCCESS;

    }
    nowyWierzcholek->etykieta = etykieta;
    nowyWierzcholek->nastepny_wierzcholek = NULL;
    return ADD_NODE_FAIL;
}

bool czy_sasiad(Wierzcholek* wierzcholek, uint32_t etykieta_sasiada) {
    Sasiad* obecny_sasiad = wierzcholek-> pierwszy_sasiad;

    while(obecny_sasiad!=NULL){
        if(obecny_sasiad-> wierzcholek->etykieta == etykieta_sasiada) {
            return true;
        }
        obecny_sasiad = obecny_sasiad->nastepny_sasiad;
    }
    return false;
}

int dodaj_krawedz(Wierzcholek* pierwszy, uint32_t etykieta_wierzcholka1, uint32_t etykieta_wierzcholka2){
    Wierzcholek* wierzcholek1 = znajdz_wierzcholek(pierwszy, etykieta_wierzcholka1);
    Wierzcholek* wierzcholek2 = znajdz_wierzcholek(pierwszy, etykieta_wierzcholka2);

    if(!(wierzcholek1 && wierzcholek2)){
        return ADD_EDGE_FAIL;
    }

    if(czy_sasiad(wierzcholek1, wierzcholek2-> etykieta) || czy_sasiad(wierzcholek2, wierzcholek1-> etykieta)){
        return ADD_EDGE_FAIL;
    } 

    Wierzcholek* obecny_sasiad = wierzcholek1-> pierwszy_sasiad-> wierzcholek;

    Sasiad *nowy_sasiad1 = (Sasiad*)malloc(sizeof(Sasiad));
    Sasiad *nowy_sasiad2 = (Sasiad*)malloc(sizeof(Sasiad));

    if(nowy_sasiad1 != NULL){
        nowy_sasiad1-> wierzcholek = wierzcholek2;
        while(wierzcholek1-> pierwszy_sasiad-> wierzcholek != NULL){
            wierzcholek1->pierwszy_sasiad = wierzcholek1->pierwszy_sasiad->nastepny_sasiad;
        }
        wierzcholek1->pierwszy_sasiad->nastepny_sasiad = nowy_sasiad1;
    }
    if(nowy_sasiad2 != NULL){
        nowy_sasiad2-> wierzcholek = wierzcholek1;
        while(wierzcholek2-> pierwszy_sasiad-> wierzcholek != NULL){
            wierzcholek2->pierwszy_sasiad = wierzcholek2->pierwszy_sasiad->nastepny_sasiad;
        }
        wierzcholek2->pierwszy_sasiad->nastepny_sasiad = nowy_sasiad2;
    }
}

void usun_wierzcholek(){

}

void usun_krawedz(){

}


