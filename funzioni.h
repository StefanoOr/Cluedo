#ifndef CLUEDO_FUNZIONI_H
#define CLUEDO_FUNZIONI_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "carte.h"
#include "giocatori.h"
#include "gioco.h"

#define MAX_S 23
#define STRING 255



void salvaPartita(int tGiocatoreAttuale, int nTurno, int nGiocatori, Giocatore *giocatori, int nScoperto, Mazzo *mazzoScoperto, Mazzo *mazzoTripla);
void salvaLog(char *string);
void caricaPartita(int *nGiocatori, int *turno, int *giocatoreIniziale, int *nCarteGiocatori, Mazzo **mazzoTripla, Mazzo **mazzoScoperto, Giocatore **giocatore, int *nScoperto);
void caricaStatistiche(int statistiche[]);
void salvaStatistiche(Mazzo *mazzoTripla, const char mazzoArmi[][MAX_S + 1], const char mazzoLuoghi[][MAX_S + 1], const char mazzoSospetti[][MAX_S + 1], int statistiche[]);

#endif //CLUEDO_FUNZIONI_H
