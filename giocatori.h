//
// Created by Pc on 08/02/2018.
//
#ifndef CLUEDO_GIOCATORI_H
#define CLUEDO_GIOCATORI_H
#define MAX_S 23
#define MIN_PLAYER 3
#define MAX_PLAYER 6


struct nodoTaccuino{
    char arma[MAX_S+1];
    char sospetto[MAX_S+1];
    int  idLuogo;
    struct nodoTaccuino* next;
};

typedef struct nodoTaccuino Taccuino;

typedef struct {
    char nome[MAX_S+1];
    int idStanza;
    int isIpotesi;
    int nCarte;
    Mazzo* carteInMano;
    Taccuino *taccuino;

}Giocatore;



Giocatore *creaGiocatori(int nGiocatori,int nCarteGiocatori);
Mazzo *distribuisciCarte(Mazzo *gioco,Giocatore*giocatore,int nGiocatori,Mazzo *mazzoScoperto);
void stampaIdStanza(int idStanza);
Taccuino *checkTaccuino(Taccuino *taccuino, char arma[], char sospetto[], int idLuogo);
Taccuino *inserisciTaccuinoInTesta(Taccuino *taccuino, char arma[], char sospetto[], int idLuogo);
int contaTaccuino(Taccuino *taccuino);
void stampaTaccuino(Taccuino *taccuino);
#endif //CLUEDO_GIOCATORI_H
