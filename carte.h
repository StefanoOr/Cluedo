
#ifndef CLUEDO_CARTE_H
#define CLUEDO_CARTE_H


#include "funzioni.h"

#define MAX_S 23
#define  N_LUOGHI 9
#define N_ARMI_SOSPETTI 6
#define N_MAZZO 18
#define ALL_CARD 21
#define MESCOLA 500


#define DESCRIZIONE_S 100
typedef enum {ARMA, SOSPETTO, STANZA } tipologia;
typedef struct {
    char nome[MAX_S + 1];
    char descrizione[DESCRIZIONE_S + 1];
    tipologia tipoCarta;

} Carta;

struct nodo{
    Carta carte;
    struct nodo* next;
};

typedef struct nodo Mazzo;
Mazzo *inserisciNodoInCoda(Mazzo *list, Carta carta);
Mazzo* creaMazzoSospetti(Mazzo* mazzoSospetto);
Mazzo* creaMazzoLuoghi(Mazzo*mazzoLuogo);
Mazzo *creaMazzoArmi(Mazzo* mazzoArmi);
Mazzo *creaMazzoTripla(Mazzo* mazzoArmi,Mazzo*mazzoLuogo,Mazzo* mazzoSospetto);
void mescolaMazzo(Mazzo *mazzo,int min,int max,int nMescolate);
void stampaMazzo(Mazzo *mazzo);
void stampaCarta(Carta carta);
Mazzo *inserisciNodoinTesta(Mazzo *mazzo, Carta carta);
Mazzo *initMazzo(int nMazzo, Mazzo *mazzo, Carta carte[]);
Mazzo *initTripla(Mazzo *mazzoArmi,Mazzo* mazzoSospetti, Mazzo* mazzoLuoghi,Mazzo* mazzoTripla);
Mazzo *eliminaCartaInTesta(Mazzo *mazzo);
Mazzo *creaMazzoDiGioco(Mazzo *mazzoArmi, Mazzo *mazzoLuogo, Mazzo *mazzoSospetto, Mazzo *mazzoDiGioco);
void cancellaMazzo(Mazzo *mazzo);
int contaGrandezzaMazzo(Mazzo* mazzo);
char *ricercaElemento(Mazzo *mazzo, int val);
#endif //CLUEDO_CARTE_H
