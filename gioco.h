
#ifndef CLUEDO_GIOCO_H
#define CLUEDO_GIOCO_H

#include "funzioni.h"
#define R 9 //macro righe mappa di gioco
#define C 9//macro colonne mappa di gioco
#define N_DADO 6 //macro grandezza dado

void start();
void stampaStatistiche(int statistiche[],const char nomeSospetti[][MAX_S+1], const char nomeArmi[][MAX_S+1], const char idString[][MAX_S + 1]);
void nuovaPartita(int *nGiocatori,int *turno,int *giocatoreIniziale,int *nCarteGiocatori ,Mazzo*mazzoTripla, Mazzo*mazzoScoperto,Giocatore *giocatore);
void  partita(Giocatore giocatori[],Mazzo *tripla, int turno, int turnoG,int nGiocatori,Mazzo* mazzoScoperto,int nScoperto);
void spostamento(Giocatore *giocatore,int c,const int mappa[][c],int dadi[],int turno);
void ipotesi(Giocatore *giocatore,Mazzo *tripla,Giocatore giocatori[],int nGiocatori,const char idSting[][MAX_S+1],int turnoGiocatore,Mazzo *mazzoScoperto,int turnoPartita,const char nomeCarte[][MAX_S+1]);
int inputGiocatore(int first,int second);
int checkCarteInMano(Mazzo* carteInMano,char sospetto[],const char luogo[], char arma[]);
int spostamentoCantina();
#endif //CLUEDO_GIOCO_H
