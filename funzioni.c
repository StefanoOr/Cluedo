#include "funzioni.h"
#include "giocatori.h"
#include "carte.h"
#include "gioco.h"

//Created by Stefano on 08/02/2018.
/**
     * funzione dedicata al salvataggio della partita  tramite file binario
     *
     * @param int,int,int,Giocatore* ,int,Mazzo*,Mazzo*
     */

void salvaPartita(int tGiocatoreAttuale, int nTurno, int nGiocatori, Giocatore giocatori[nGiocatori], int nScoperto,
                  Mazzo *mazzoScoperto, Mazzo *mazzoTripla) {
    char nameFile[MAX_S + 1];
    char nameFileTac[MAX_S + 5] = {"Tac_"};
    int i, nIpotesi;
    FILE *fp = NULL;

    printf("Insersci il nome del tuo salvataggio:\n Salvataggi presenti:\n");////concas

/*TODO #ifdef _WIN32
    system("dir saves");
#endif
#ifdef linux
    system("ls " DIRSAVES);
#endif
#ifdef __APPLE__
    system("ls " DIRSAVES);
#endif
*/

    getchar();
    scanf("%23[^\n]s", nameFile);

    fp = fopen(nameFile, "wb");
    if (fp == NULL) {
        exit(-1);
    }
    //scrittura dati partita
    fwrite(&tGiocatoreAttuale, sizeof(int), 1, fp);
    fwrite(&nTurno, sizeof(int), 1, fp);
    fwrite(&nGiocatori, sizeof(int), 1, fp);
    //scrittura dati giocatore
    for (i = 0; i < nGiocatori; i++) {
        printf("%s\n", giocatori[i].nome);
        fwrite(giocatori[i].nome, sizeof(char), MAX_S + 1, fp);
        fwrite(&giocatori[i].idStanza, sizeof(int), 1, fp);
        fwrite(&giocatori[i].isIpotesi, sizeof(int), 1, fp);
        fwrite(&giocatori[i].nCarte, sizeof(int), 1, fp);
        //scrittura dati carte giocatore
        while (giocatori[i].carteInMano != NULL) {
            fwrite(&giocatori[i].carteInMano->carte.tipoCarta, sizeof(tipologia), 1, fp);
            fwrite(giocatori[i].carteInMano->carte.nome, sizeof(char), MAX_S + 1, fp);
            giocatori[i].carteInMano = giocatori[i].carteInMano->next;
        }

    }
    //scrittura dati carte scoperte
    fwrite(&nScoperto, sizeof(int), 1, fp);
    while (mazzoScoperto != NULL) {
        fwrite(&mazzoScoperto->carte.tipoCarta, sizeof(tipologia), 1, fp);
        fwrite(mazzoScoperto->carte.nome, sizeof(char), MAX_S + 1, fp);
        mazzoScoperto = mazzoScoperto->next;
    }
    //scrittura dati carte tripla
    while (mazzoTripla != NULL) {
        fwrite(&mazzoTripla->carte.tipoCarta, sizeof(int), 1, fp);
        fwrite(mazzoTripla->carte.nome, sizeof(char), MAX_S + 1, fp);
        mazzoTripla = mazzoTripla->next;
    }


    fclose(fp);

    strcat(nameFileTac, nameFile);
    fp = fopen(nameFileTac, "wb");
    if (fp == NULL) {
        exit(-1);
    }

    for (i = 0; i < nGiocatori; ++i) {
        nIpotesi = contaTaccuino(giocatori[i].taccuino);
        fwrite(&nIpotesi, sizeof(int), 1, fp);
        while (giocatori[i].taccuino != NULL) {
            fwrite(giocatori[i].taccuino->arma, sizeof(char), MAX_S + 1, fp);
            fwrite(giocatori[i].taccuino->sospetto, sizeof(char), MAX_S + 1, fp);
            fwrite(&giocatori[i].taccuino->idLuogo, sizeof(int), 1, fp);
            giocatori[i].taccuino = giocatori[i].taccuino->next;

        }
    }
    fclose(fp);


}

//TODO concas
//TODO Giocatore *giocatori, Mazzo *tripla, int turno, int turnoG, int nGiocatori, Mazzo *mazzoScoperto,int nScoperto
void caricaPartita(int *nGiocatori, int *turno, int *giocatoreIniziale, int *nCarteGiocatori, Mazzo **mazzoTripla,
                   Mazzo **mazzoScoperto, Giocatore **giocatori, int *nScoperto) {

    char nomeFile[MAX_S + 1];
    char nameFileTac[MAX_S + 5] = {"Tac_"};
    int j, i, nIpotesi = 0;
    Carta carta;
    Giocatore *giocatoriArray = NULL;
    Mazzo *triplaMazzo = NULL, *scopertoMazzo = NULL;

    Taccuino taccuino;

    printf("inserisci il nome del file\n");
    scanf("%s", nomeFile);

    FILE *fp = NULL;
    fp = fopen(nomeFile, "rb");

    if (fp == NULL) {
        perror("Errore in apertura del file\n");
        exit(1);
    }
    //lettura dati partita
    fread(giocatoreIniziale, sizeof(int), 1, fp);
    fread(turno, sizeof(int), 1, fp);
    fread(nGiocatori, sizeof(int), 1, fp);

    printf("%d %d %d", *giocatoreIniziale, *turno, *nGiocatori);

    giocatoriArray = (Giocatore *) malloc(sizeof(Giocatore) * (*nGiocatori));

    //lettura dati giocatori
    for (i = 0; i < *nGiocatori; ++i) {
        fread(giocatoriArray[i].nome, sizeof(char), MAX_S + 1, fp);
        fread(&giocatoriArray[i].idStanza, sizeof(int), 1, fp);
        fread(&giocatoriArray[i].isIpotesi, sizeof(int), 1, fp);
        fread(&giocatoriArray[i].nCarte, sizeof(int), 1, fp);


        giocatoriArray[i].carteInMano = NULL;
        for (j = 0; j < giocatoriArray[i].nCarte; ++j) {
            fread(&carta.tipoCarta, sizeof(tipologia), 1, fp);
            fread(carta.nome, sizeof(char), MAX_S + 1, fp);
            giocatoriArray[i].carteInMano = inserisciNodoinTesta(giocatoriArray[i].carteInMano, carta);
        }
    }

    fread(nScoperto, sizeof(int), 1, fp);

    //lettura dati carte scoperte
    for (j = 0; j < *nScoperto; ++j) {
        fread(&carta.tipoCarta, sizeof(tipologia), 1, fp);
        fread(carta.nome, sizeof(char), MAX_S + 1, fp);
        scopertoMazzo = inserisciNodoinTesta(scopertoMazzo, carta);


    }

    *mazzoScoperto = scopertoMazzo;

    //lettura dati carte tripla
    for (j = 0; j < 3; ++j) {
        fread(&carta.tipoCarta, sizeof(tipologia), 1, fp);
        fread(carta.nome, sizeof(char), MAX_S + 1, fp);
        triplaMazzo = inserisciNodoInCoda(triplaMazzo, carta);
    }
    *mazzoTripla = triplaMazzo;
    fclose(fp);


    strcat(nameFileTac, nomeFile);
    fp = fopen(nameFileTac, "rb");
    if (fp == NULL) {
        printf("nessun taccuino trovato \n ");
    } else {
        for (i = 0; i < *nGiocatori; ++i) {
            fread(&nIpotesi, sizeof(int), 1, fp);
            giocatoriArray[i].taccuino = NULL;
            for (j = 0; j < nIpotesi; ++j) {
                fread(taccuino.arma, sizeof(char), MAX_S + 1, fp);
                fread(taccuino.sospetto, sizeof(char), MAX_S + 1, fp);
                fread(&taccuino.idLuogo, sizeof(int), 1, fp);
                printf("%s  sospetto %s  id %d ", taccuino.arma, taccuino.sospetto, taccuino.idLuogo);
                giocatoriArray[i].taccuino = inserisciTaccuinoInTesta(giocatoriArray[i].taccuino, taccuino.arma,
                                                                      taccuino.sospetto, taccuino.idLuogo);

            }

        }
    }
    *giocatori = giocatoriArray;
}


//funzione che salva il file log
void salvaLog(char *string) {

    FILE *fp = NULL;

    fp = fopen("logger.txt", "a+");
    if (fp == NULL) {
        exit(-1);
    }

    fprintf(fp, string);
    fprintf(fp, "\n");
    fclose(fp);
}

//TODO concas
char caricaLogger() {
    FILE *fp = NULL;
    char string[MAX_S + 1];
    fp = fopen("logger.txt", "r");

    if (fp == NULL) {
        salvaLog("Nuovo logger");
    } else {

        do {
            fscanf(fp, "%s", string);
        } while (string != NULL);
    }
    //return string;
}

void caricaStatistiche(int statistiche[]) {
    int i;
    FILE *fp = NULL;
    fp = fopen("statistiche.sav", "rb");
    if (fp == NULL) {
        printf("file inesistente \n");
        exit(1);
    }

    fread(&statistiche[0], sizeof(int), 1, fp);
    for (i = 1; i < ALL_CARD+1; ++i) {
        fread(&statistiche[i], sizeof(int), 1, fp);
    }

    fclose(fp);

}

void salvaStatistiche(Mazzo *mazzoTripla, const char mazzoArmi[][MAX_S + 1], const char mazzoLuoghi[][MAX_S + 1],
                      const char mazzoSospetti[][MAX_S + 1],int statistiche[]) {
    int i,k ,j;
    FILE *fp = NULL;
    fp = fopen("statistiche.sav", "wb");

    if (fp == NULL) {
        printf("Errore in apertura del file statistiche\n");
        exit(1);
    }

    fwrite(&statistiche[0], sizeof(int), 1, fp);

    for ( j = 0; j <9; ++j) {
        if(!strcmp(mazzoTripla->carte.nome,mazzoLuoghi[j])){
            statistiche[j+1]++;
        }
        fwrite(&statistiche[j], sizeof(int),1,fp);
    }
    mazzoTripla=mazzoTripla->next;

    for (k =j;  k< 15; k++) {
        if(!strcmp(mazzoTripla->carte.nome,mazzoSospetti[k%j])){
            statistiche[k+1]++;
        }
        fwrite(&statistiche[k], sizeof(int),1,fp);
    }
    mazzoTripla=mazzoTripla->next;

    for ( i = k; i <21 ; ++i) {
        if(!strcmp(mazzoTripla->carte.nome,mazzoArmi[i%15])){
            statistiche[i+1]++;
        }
        fwrite(&statistiche[i], sizeof(int),1,fp);
    }


fclose(fp);
}

/*
    //controllo della cart
    for (i = 0; i < N_ARMI_SOSPETTI + 1; ++i) {

        if (!strcmp(mazzoTripla->carte.nome, mazzoArmi[i]) || !strcmp(mazzoTripla->carte.nome, mazzoSospetti[i])) {
            if (indiceCarta = cartaPresenteStatistica(statistiche, mazzoTripla->carte.nome)) {
                statistiche[indiceCarta].nUscito++;
            } else {

                statistiche[p].nUscito=0;
                strcpy(statistiche[p].nome, mazzoTripla->carte.nome);
               indiceCarta=p;
                p++;
            }
            fprintf(fp,statistiche[indiceCarta].nome);
           // fwrite(statistiche[indiceCarta].nome, sizeof(char),MAX_S+1,fp);
           // fwrite(&statistiche[indiceCarta].nUscito, sizeof(int),MAX_S+1,fp);
            mazzoTripla = mazzoTripla->next;

        }
        if (mazzoTripla == NULL ) {

            break;
        }
        if(mazzoTripla->carte.tipoCarta==STANZA){
            mazzoTripla=mazzoTripla->next;
            i--;
        }
    }
    mazzoTripla=aux;
    for (j = 0; j < N_LUOGHI+1; ++j) {
        if (!strcmp(mazzoTripla->carte.nome, mazzoLuoghi[j])) {
            if (indiceCarta = cartaPresenteStatistica(statistiche, mazzoTripla->carte.nome)) {
                statistiche[indiceCarta].nUscito++;
            } else {

                statistiche[p].nUscito=0;
                strcpy(statistiche[indiceCarta].nome, mazzoTripla->carte.nome);
                indiceCarta=p;
                p++;
            }
            fprintf(fp,statistiche[indiceCarta].nome);
          //  fwrite(statistiche[indiceCarta].nome, sizeof(char),MAX_S+1,fp);
            //fwrite(&statistiche[indiceCarta].nUscito, sizeof(int),MAX_S+1,fp);
            mazzoTripla = mazzoTripla->next;

        }
        if (mazzoTripla == NULL) {
            break;
        }

    }
    fclose(fp);

}


int cartaPresenteStatistica(Statistiche *statistica, char *nome) {
    int i;
    for (i =0; i < ALL_CARD; ++i) {
        if (!strcmp(statistica[i].nome, nome)) {
            return 1;
        }
    }
    return 0;

}
*/
