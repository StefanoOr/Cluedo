//
//Created by Stefano on 08/02/2018.
//
#include "funzioni.h"
#include "carte.h"
#include "giocatori.h"

//crea i gioocatori
Giocatore *creaGiocatori(const int nGiocatori, int nCarteGiocatori) {
    int i, idRandom;
    char nome[MAX_S + 1];
    Giocatore *giocatore = NULL;
    giocatore = (Giocatore *) malloc(nGiocatori * sizeof(Giocatore));
    for (i = 0; i < nGiocatori; ++i) {
        idRandom = rand() % (N_LUOGHI);

        printf("Giocatore %d inserisci il nome", i + 1);

        getchar();
        scanf("%s", nome);

        strcpy(giocatore[i].nome, nome);
        giocatore[i].isIpotesi = 0;
        giocatore[i].idStanza = idRandom;
        giocatore[i].carteInMano = NULL;
        giocatore[i].nCarte = nCarteGiocatori;
        giocatore[i].taccuino = NULL;


    }
    return giocatore;
}

//distribuisce la carte del mazzo di gioco e restituisce le carte che sono rimaste all'interno del mazzo
Mazzo *distribuisciCarte(Mazzo *gioco, Giocatore *giocatore, int nGiocatori, Mazzo *mazzoScoperto) {
    int grandezzaMazzo, i, j;

    grandezzaMazzo = contaGrandezzaMazzo(gioco);

    for (i = 0; i < grandezzaMazzo / nGiocatori; ++i) {
        for (j = 0; j < nGiocatori; ++j) {
            giocatore[j].carteInMano = inserisciNodoinTesta(giocatore[j].carteInMano, gioco->carte);
            gioco = gioco->next;
        }
    }
    while (gioco != NULL) {
        mazzoScoperto = inserisciNodoinTesta(mazzoScoperto, gioco->carte);
        gioco = gioco->next;


    }

    return mazzoScoperto;


}

//funzione che stampa il nome della stanza assocciato all'id
void stampaIdStanza(int idStanza) {
    char idString[N_LUOGHI][
            MAX_S + 1] = {"Laboratorio T", "Laboratorio M", "Bagno", "Aula Costa", "Giardino", "Entrata",
                          "Parcheggio", "Simaz", "BatCaverna"};
    printf("\n%s", idString[idStanza]);
}


Taccuino *checkTaccuino(Taccuino *taccuino, char arma[], char sospetto[], int idLuogo) {
    int isTrovato = 0;
    Taccuino *aux = taccuino;
    while (taccuino != NULL) {
        if (strstr(taccuino->arma, arma)) {
            if (strstr(taccuino->sospetto, sospetto)) {
                if (taccuino->idLuogo == idLuogo) {
                    isTrovato = 1;
                }
            }
        }
        taccuino = taccuino->next;
    }
    if (isTrovato == 0) {
        aux = inserisciTaccuinoInTesta(aux, arma, sospetto, idLuogo);
    }
    return aux;

}

int contaTaccuino(Taccuino *taccuino) {
    if (taccuino == NULL) {
        return 0;
    }

    return contaTaccuino(taccuino->next) + 1;
}

Taccuino *inserisciTaccuinoInTesta(Taccuino *taccuino, char arma[], char sospetto[], int idLuogo) {
    Taccuino *nuovoTaccuino = (Taccuino *) malloc(sizeof(Taccuino));
    if (nuovoTaccuino == NULL) {
        printf("errore di allocamento del Taccuino");
        exit(-1);
    }
    strcpy(nuovoTaccuino->arma, arma);
    strcpy(nuovoTaccuino->sospetto, sospetto);
    nuovoTaccuino->idLuogo = idLuogo;
    nuovoTaccuino->next = taccuino;

    return nuovoTaccuino;
}

void stampaTaccuino(Taccuino *taccuino) {
    int i=1;
    while(taccuino != NULL) {
        printf("Ipotesi %d , Arma: %s , Sospetto: %s , Id: %d \n",i,taccuino->arma,taccuino->sospetto,taccuino->idLuogo);
        taccuino=taccuino->next;
        i++;
    }

}