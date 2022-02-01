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
        nowyWierzcholek->kolor = -1; // -1 oznacza niepokolorowany
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

    Sasiad *nowy_sasiad1 = (Sasiad*)malloc(sizeof(Sasiad));
    Sasiad *nowy_sasiad2 = (Sasiad*)malloc(sizeof(Sasiad));

    if(nowy_sasiad1 != NULL){
        nowy_sasiad1-> wierzcholek = wierzcholek2;
        nowy_sasiad1-> nastepny_sasiad = NULL;

        if (wierzcholek1->pierwszy_sasiad == NULL) {
            wierzcholek1->pierwszy_sasiad = nowy_sasiad1;
        } else {
            Sasiad* ostatni_sasiad = wierzcholek1->pierwszy_sasiad;
            while (ostatni_sasiad->nastepny_sasiad != NULL) {
                ostatni_sasiad = ostatni_sasiad->nastepny_sasiad;
            }
            ostatni_sasiad->nastepny_sasiad = nowy_sasiad1;
        }
    }
    if(nowy_sasiad2 != NULL){
        nowy_sasiad2-> wierzcholek = wierzcholek1;
        nowy_sasiad2-> nastepny_sasiad = NULL;

        if (wierzcholek2->pierwszy_sasiad == NULL) {
            wierzcholek2->pierwszy_sasiad = nowy_sasiad2;
        }
        else {
            Sasiad* ostatni_sasiad = wierzcholek2->pierwszy_sasiad;
            while (ostatni_sasiad->nastepny_sasiad != NULL) {
                ostatni_sasiad = ostatni_sasiad->nastepny_sasiad;
            }
            ostatni_sasiad->nastepny_sasiad = nowy_sasiad2;
        }
    }
    return ADD_EDGE_SUCCESS;
}


int usun_sasiada(Wierzcholek *wierzcholek1, Wierzcholek *wierzcholek2)
{
    if(!czy_sasiad(wierzcholek1, wierzcholek2->etykieta)) return RM_NEIGH_FAIL;

    Sasiad *obecnySasiad = wierzcholek1->pierwszy_sasiad;

    while(obecnySasiad){
        if(obecnySasiad->wierzcholek->etykieta == wierzcholek2->etykieta){
            obecnySasiad = obecnySasiad->nastepny_sasiad;
            wierzcholek1->pierwszy_sasiad = obecnySasiad->nastepny_sasiad;
            free(obecnySasiad);
            return RM_NEIGH_SUCCESS;
        }
    }
    return RM_NEIGH_FAIL;
}

void usun_krawedz(Wierzcholek *pierwszy, uint32_t etWie1, uint32_t etWie2){

    Wierzcholek *wierzcholek1 = znajdz_wierzcholek(pierwszy, etWie1);
    Wierzcholek *wierzcholek2 = znajdz_wierzcholek(pierwszy, etWie2);

    if(!(wierzcholek1 && wierzcholek2)) return RM_NEIGH_FAIL;

    if(!(czy_sasiad(wierzcholek1, wierzcholek2->etykieta) && czy_sasiad(wierzcholek2, wierzcholek1->etykieta))) return RM_EDGE_FAIL;

    if(usun_sasiada(wierzcholek1, wierzcholek2) == RM_NEIGH_SUCCESS && usun_sasiada(wierzcholek2, wierzcholek1) == RM_NEIGH_SUCCESS)
        return RM_EDGE_SUCCESS;
    else return RM_EDGE_FAIL;

}

