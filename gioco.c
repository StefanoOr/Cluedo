#include "funzioni.h"
#include "carte.h"
#include "giocatori.h"
//Created by Stefano on 08/02/2018.


/* Menù iniziale */
void start() {
    int menu;

    int nGiocatori, turno, giocatoreIniziale, nCarteGiocatori, nScoperto;
    Mazzo *mazzoTripla = NULL, *mazzoScoperto = NULL;
    Giocatore *giocatore = NULL;


    srand(time(NULL));
    setbuf(stdout, 0);//TODO da togliere  <----
    printf(" MENU \n"
                   "Inizia nuova partita premi premi 1 \n Carica partita premi 2 \n Esci premi 3:\n ");
    menu = inputGiocatore(1, 3);
    getchar();


    switch (menu) {
        case 1:
            nuovaPartita(&nGiocatori, &turno, &giocatoreIniziale, &nCarteGiocatori, mazzoTripla, mazzoScoperto,
                         giocatore);
            break;

        case 2:
            caricaPartita(&nGiocatori, &turno, &giocatoreIniziale, &nCarteGiocatori, &mazzoTripla, &mazzoScoperto,
                          &giocatore, &nScoperto);
            partita(giocatore,mazzoTripla,turno,giocatoreIniziale,nGiocatori,mazzoScoperto,nScoperto);

            break;
        case 3:
            exit(-1);

    }

}


//crea una nuova partita
void nuovaPartita(int *nGiocatori, int *turno, int *giocatoreIniziale, int *nCarteGiocatori, Mazzo *mazzoTripla,
                  Mazzo *mazzoScoperto, Giocatore *giocatore) {
    Mazzo *mazzoArmi = NULL, *mazzoLuogo = NULL, *mazzoSospetto = NULL, *mazzoDiGioco = NULL;
    int nScoperto;
    *turno = 1;

    //creazione dei 3 mazzi
    mazzoArmi = creaMazzoArmi(mazzoArmi);
    mazzoLuogo = creaMazzoLuoghi(mazzoLuogo);
    mazzoSospetto = creaMazzoSospetti(mazzoSospetto);

    //creazione mazzo tripla
    mazzoTripla = creaMazzoTripla(mazzoArmi, mazzoLuogo, mazzoSospetto);
    mazzoArmi = eliminaCartaInTesta(mazzoArmi);
    mazzoLuogo = eliminaCartaInTesta(mazzoLuogo);
    mazzoSospetto = eliminaCartaInTesta(mazzoSospetto);

    //creazione mazzo di gioco
    mazzoDiGioco = creaMazzoDiGioco(mazzoArmi, mazzoLuogo, mazzoSospetto, mazzoDiGioco);


    printf("Inserisci il numero di giocatori da 3 a 6:\n ");
    *nGiocatori = inputGiocatore(MIN_PLAYER, MAX_PLAYER);


    *nCarteGiocatori = contaGrandezzaMazzo(mazzoDiGioco) / *nGiocatori;

        //crezione giocatori
    giocatore = creaGiocatori(*nGiocatori, *nCarteGiocatori);

    //distribuzione delle carte del mazzo ai giocatori , e creazione del mazzo scoperto
    mazzoScoperto = distribuisciCarte(mazzoDiGioco, giocatore, *nGiocatori,
                                      mazzoScoperto);
    nScoperto = contaGrandezzaMazzo(mazzoScoperto);


    *giocatoreIniziale = rand() % (0 + *nGiocatori);
    partita(giocatore, mazzoTripla, *turno, *giocatoreIniziale, *nGiocatori, mazzoScoperto, nScoperto);

//TODO ricorda di deallocare mazzoGioco
}

//gamePlay del gioco
void partita(Giocatore giocatori[], Mazzo *tripla, int turno, int turnoG, int nGiocatori, Mazzo *mazzoScoperto,
             int nScoperto) {

    int finePartita = 0, true = 1, false = 0;
    int input;
    int dadi[2];
    int statisticaCarta[ALL_CARD+1]={0};


    char stringa[STRING + 1];


    const char idString[N_LUOGHI][
            MAX_S + 1] = {"Laboratorio T", "Laboratorio M", "Bagno", "Aula Costa", "Giardino", "Entrata",
                          "Parcheggio", "Simaz", "BatCaverna"};

    const char nomeSospetti[N_ARMI_SOSPETTI][MAX_S+1]={"Alan Turing" ,"G.M. Hopper","Edsger Dijkstra","G.F. Voronoj","J.V. Neumann","M. Hamilton"};
    const char nomeArmi[N_ARMI_SOSPETTI][MAX_S+1]={"Cavo di Rete","Sparacoriandoli","Calcinaccio","Tastiera USB","Fumo Caldaia","Floppy Disk 3.5"};

    //creazione della mappa di gioco
    const int mappa[R][C] = {{0,  4,  8,  4,  8,  12, 16, 12, 14},
                             {4,  0,  4,  8,  12, 8,  12, 8,  10},
                             {8,  4,  0,  12, 16, 12, 8,  4,  6},
                             {4,  8,  12, 0,  4,  8,  12, 8,  10},
                             {8,  12, 16, 4,  0,  4,  8,  12, 10},
                             {12, 8,  12, 8,  4,  0,  4,  8,  6},
                             {16, 12, 8,  12, 8,  4,  0,  4,  2},
                             {12, 8,  4,  8,  12, 8,  4,  0,  2},
                             {14, 10, 6,  10, 10, 6,  2,  2,  0}
    };

    stampaMazzo(tripla);
    salvaStatistiche(tripla,nomeArmi,idString,nomeSospetti,statisticaCarta);
    stampaStatistiche(statisticaCarta,nomeArmi,nomeSospetti,idString);

    while (finePartita != 1) {

        printf("TURNO: %d E' il turno di %s\n", turno, giocatori[turnoG].nome);
        sprintf(stringa, "TURNO: %d E' il turno di %s ", turno, giocatori[turnoG].nome);
        salvaLog(stringa);

        printf("vuoi salvare la partita premi 1 per Salvare  o 0 per non Salvare:\n");
        input = inputGiocatore(false, true);
        if (input) {
            salvaPartita(turnoG, turno, nGiocatori, giocatori, nScoperto, mazzoScoperto, tripla);
        }
        printf("\n%s LE TUE CARTE IN MANO : \n\n",giocatori[turnoG].nome);
        stampaMazzo(giocatori[turnoG].carteInMano);

        if(nScoperto!=0) {
            printf("\nLE CARTE SCOPERTE:\n");
            stampaMazzo(mazzoScoperto);
        }

        printf("\n%s ti trovi nel luogo %s ",giocatori[turnoG].nome ,idString[giocatori[turnoG].idStanza]);

        printf("se vuoi spostarti premi 1 altrimenti 0\n");
        input = inputGiocatore(false, true);
        if (input) {
            spostamento(&giocatori[turnoG], MAX_S + 1, mappa, dadi, turno);//TODO <-- altro giorno by ema
        } else {

            sprintf(stringa, "TURNO: %d  %s non ha fatto nessun spostamento  ", turno, giocatori[turnoG].nome);
            salvaLog(stringa);
            printf("nessun spostamento\n");
        }


        if (giocatori[turnoG].isIpotesi == 0) {
            printf("se vuoi fare l'ipotesi premi 1 altrimeti 0:\n");
            input = inputGiocatore(false, true);
            if (input) {
                ipotesi(&giocatori[turnoG], tripla, giocatori, nGiocatori, idString, turnoG, mazzoScoperto, turno,nomeSospetti);
            } else {
                printf("nessuna ipotesi fatta \n");
            }
        } else {

            printf("la  tua ipotesi e' corretta prova a tirare i dadi per raggiungere la cantina\n");
            finePartita = spostamentoCantina();
            sprintf(stringa, "TURNO: %d  %s ha vinto \n ", turno, giocatori[turnoG].nome);
            salvaLog(stringa);
        }


        if (finePartita == 0) {
            turnoG++;
            turno++;
            if (turnoG == nGiocatori) {
                turnoG = 0;
            }
        }


    }
    printf("Il giocatore %s ha indovinato chi,dove e con quale arma  ha ucciso DJANNI \nGame Over",
           giocatori[turnoG].nome);
}

//funzione che permette di non far si che i player non sbaglino sull'inserimento delle azioni come il movimento e l'ipotesi
int inputGiocatore(int first, int second) {
    int input;
    scanf("%d", &input);
    if (input >= first && input <= second) {
        return input;
    } else {
        printf("Opzione sbagliata ,rinserisci\n");
        inputGiocatore(first, second);
    }

}

//funzione dedicata all'ipotesi che fa il giocatore ,ritorna 0 se l'ipotesi è sbagliata e 1 se l'ipotesi è giusta , inoltre fa il controllo delle carte in mano
void
ipotesi(Giocatore *giocatore, Mazzo *tripla, Giocatore giocatori[], int nGiocatori, const char idSting[][MAX_S + 1], int turnoGiocatore, Mazzo *mazzoScoperto, int turnoPartita, const char nomeCarte[][MAX_S+1]) {

    int input;
    int checkTripla = 1;
    int i, k, a, isTrovato = 0, cartaSelect, turno;//numeroDelle carte ,contatori,
    Mazzo *aux = NULL;
    char cartaSospetto[MAX_S + 1], cartaArma[MAX_S + 1], cartaMostrata[MAX_S + 1];
    char stringa[STRING+1];

    int carteTrovata[giocatore->nCarte];
    memset(carteTrovata, 0, giocatore->nCarte);
    for (a = 0; a < giocatore->nCarte; ++a) {
        carteTrovata[a] = 0;
    }

    printf("premi 1 se vuoi vedere il taccuino ,altrimenti 0 \n");
    input=inputGiocatore(0,1);
    if (input){
        stampaTaccuino(giocatore->taccuino);
    }

//inseriemento dell'ipotesi
    printf("inserisci il sospetto \n");
    getchar();
    scanf("%[^\n]s", cartaSospetto);
    getchar();
    printf("inserisci l'arma\n");
    scanf("%[^\n]s", cartaArma);
    getchar();

    for ( i = 0; i <N_ARMI_SOSPETTI*2 ; ++i) {
       if(strstr(nomeCarte[i],cartaArma)){
           strcpy(cartaArma,nomeCarte[i]);
       } else if(strstr(nomeCarte[i],cartaSospetto)){
           strcpy(cartaSospetto,nomeCarte[i]);
       }
    }

    giocatore[turnoGiocatore].taccuino=checkTaccuino(giocatore[turnoGiocatore].taccuino,cartaArma,cartaSospetto,giocatore->idStanza);

   sprintf(stringa, "TURNO: %d  %s ha detto che  %s ha ucciso Djanni in %s con la %s ", turnoPartita,giocatore->nome, cartaSospetto, idSting[giocatore[turnoGiocatore].idStanza], cartaArma);
    salvaLog(stringa);
//controllo dell'ipotesi con le carte scoperte
    while (mazzoScoperto != NULL) {
        if (checkCarteInMano(mazzoScoperto, cartaSospetto, idSting[giocatore->idStanza], cartaArma)) {
            printf("Hai scelto una delle carte gia mostrate\n");
            return;
        }
        mazzoScoperto = mazzoScoperto->next;
    }

//controlllo di tutte carte dei  giocatori in senso orario , per verificare se  l’ipotesi del giocatore attuale è errata
    for (k = turnoGiocatore + 1; k < (nGiocatori + turnoGiocatore) && isTrovato != 1; ++k) {
        turno = k % nGiocatori;
        printf("provaaaa %s ", giocatori[turno].nome);//TODO TEST
        if (strcmp(giocatore->nome, giocatori[turno].nome)) {//TODO <--- controlal sta funzione
            aux = giocatori[turno].carteInMano;


            for (i = 0; i < giocatori[turno].nCarte; ++i) {
                if (checkCarteInMano(giocatori[turno].carteInMano, cartaSospetto, idSting[giocatore->idStanza],
                                     cartaArma)) {
                    carteTrovata[i] = 1;
                    isTrovato = 1;
                }

                giocatori[turno].carteInMano = giocatori[turno].carteInMano->next;
            }
            //se ipotesi è errata vengono stampate al giocatore che possiede quelle carte quale vuole mostrare al giocatore attuale
            if (isTrovato) {
                giocatori[turno].carteInMano = aux;

                printf("ipotesi errata \n %s quale carta vuoi mostrare a %s \n", giocatori[turno].nome,
                       giocatore->nome);
                for (int j = 0; j < giocatori[turno].nCarte; ++j) {
                    if (carteTrovata[j] == 1) {
                        printf("%s  premi %d \n", giocatori[turno].carteInMano->carte.nome, j);

                    }
                    giocatori[turno].carteInMano = giocatori[turno].carteInMano->next;

                }
                giocatori[turno].carteInMano = aux;
                scanf("%d", &cartaSelect);
                strcpy(cartaMostrata, ricercaElemento(giocatori[turno].carteInMano, cartaSelect));
                printf("%s \n", cartaMostrata);
                sprintf(stringa, "TURNO: %d  %s ha smentito l'ipotesi facendo vedere a %s la carta %s ", turno,
                        giocatore[turno].nome, idSting[giocatore[turnoGiocatore].idStanza], cartaMostrata);
                salvaLog(stringa);
            }
        }
    }
    //controllo delle carte in mano del giocatore che ha fatto l'ipotesi
    if (isTrovato == 0) {


        for (k = 0; k < 3 && isTrovato == 0; ++k) {
            isTrovato = checkCarteInMano(giocatore->carteInMano, cartaSospetto, idSting[giocatore->idStanza],
                                         cartaArma);
            if (isTrovato) {
                sprintf(stringa, "TURNO: %d  %s hai indovinato l'ipotesi ", turnoPartita,
                        giocatori[turnoGiocatore].nome);
                salvaLog(stringa);
                giocatore->carteInMano = giocatore->carteInMano->next;
            }
        }
    }



   //controllo delle carte del giocatore con quelle da indovinare
    if (isTrovato == 0) {
        for (i = 0; i < 3 && checkTripla == 1; ++i) {


            checkTripla = checkCarteInMano(tripla, cartaSospetto, idSting[giocatore->idStanza], cartaArma);
            tripla = tripla->next;
        }
        if (checkTripla) {
            giocatore->isIpotesi = checkTripla;
            printf("ipotesi  corretta\n");
        }

    }
}


void spostamento(Giocatore *giocatore, int c, const int mappa[][c], int dadi[], int turno) { //da fart ritornare l'array
    int sommaDadi = 0, isSpostabile = 0;
    int i, j;
    int prova[N_LUOGHI] = {0};
    char stringa[STRING + 1];


    for (int i = 0; i < 2; ++i) {
        dadi[i] = 1 + rand() % (N_DADO);
        sommaDadi += dadi[i];
    }
    sprintf(stringa, "TURNO: %d  %s ha fatto %d+%d", turno, giocatore->nome, dadi[0], dadi[1]);
    salvaLog(stringa);

    //controllo se è possibile effettuare lo spostamento
    for (i = 0; i < N_LUOGHI; i++) {
        if (mappa[giocatore->idStanza][i] == sommaDadi) {
            prova[i] = 1;
            isSpostabile = 1;

        }
    }

    //scelta del luogo  dello spostamento
    if (isSpostabile) {
        printf("scegli dove andare\n");
        for (j = 0; j < N_LUOGHI; ++j) {
            if (prova[j] == 1) {
                stampaIdStanza(j);
                printf(" premi %d\n", j);

            }
        }

        giocatore->idStanza = inputGiocatore(0, N_LUOGHI);
        sprintf(stringa, "TURNO: %d  %s si e' spostato  in id %d", turno, giocatore->nome, giocatore->idStanza);
        salvaLog(stringa);
    } else {
        sprintf(stringa, "TURNO: %d  %s nessun spostamento consentito ", turno, giocatore->nome);
        salvaLog(stringa);
        printf("hai fatto %d nessun spostamento \n", sommaDadi);
    }


}


int checkCarteInMano(Mazzo *carteInMano, char sospetto[], const char luogo[], char arma[]) {
    if (strstr(carteInMano->carte.nome, sospetto) ||
        strstr(carteInMano->carte.nome, luogo) ||
        strstr(carteInMano->carte.nome, arma)) {
        return 1;
    }
    return 0;
}

int spostamentoCantina() {
    int dado1, dado2;
    int isTrue;

    dado1 = 1 + rand() % (N_DADO);
    dado2 = 1 + rand() % (N_DADO);
    printf("hai lanciato i dadi hai fatto %d+%d \n", dado1, dado2);
    isTrue = dado1 / dado2;
    if (isTrue) {
        printf("hai raggiunto la CANTINA\n");
        return isTrue;

    }
    return 0;
}

void stampaStatistiche(int statistiche[], const char nomeArmi[][MAX_S+1],const char nomeSospetti[][MAX_S+1], const char idString[][MAX_S + 1]){
    int i,j,k;
    float  percentuale;
    statistiche[0]++;

    for ( j = 0; j <N_LUOGHI; ++j) {
        percentuale=statistiche[j+1]/statistiche[0]*100;
     printf("%s %2.f %% - ",idString[j],percentuale);
    }
printf("\n");
//nVolte/nPartite * 100
    for (k =j;  k< 15; k++) {
      percentuale=statistiche[k+1]/statistiche[0]*100;
        printf("%s %2.f %% - ",nomeSospetti[k%j],percentuale);

    }

    printf("\n");
    for ( i = k; i <21 ; ++i) {
        percentuale=statistiche[i+1]/statistiche[0]*100;
        printf("%s %2.f %% - ",nomeArmi[i%k],percentuale);

    }

}

