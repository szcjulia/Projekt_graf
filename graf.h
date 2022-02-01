#ifndef GRAF_H
#define GRAF_H
#include <stdbool.h>
#include <stdint.h>
#define ADD_NODE_FAIL (-2)
#define ADD_NODE_SUCCESS (-3)
#define ADD_EDGE_FAIL (-2)
#define ADD_EDGE_SUCCESS (-3)


typedef struct Wierzcholek{
    uint32_t etykieta;
    int kolor;
    struct Sasiad *pierwszy_sasiad;
    struct Wierzcholek *nastepny_wierzcholek;
} Wierzcholek;

typedef struct Sasiad{
    struct Wierzcholek *wierzcholek;
    struct Sasiad *nastepny_sasiad;
} Sasiad;

Wierzcholek* znajdz_wierzcholek(Wierzcholek* pierwszy_wierzcholek, uint32_t szukana_etykieta);
int dodaj_wierzcholek(Wierzcholek** pierwszy_wierzcholek, uint32_t etykieta);
bool czy_sasiad(Wierzcholek* wierzcholek, uint32_t etykieta_sasiada);
int dodaj_krawedz(Wierzcholek* pierwszy, uint32_t etykieta_wierzcholka1, uint32_t etykieta_wierzcholka2);
//void usun_wierzcholek();
//void usun_krawedz();

#endif //GRAF_H
