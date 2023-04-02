#include "funzioni.h"
//Created by Stefano on 08/02/2018.
//crea la lista mazzoTripla
Mazzo *creaMazzoTripla(Mazzo *mazzoArmi, Mazzo *mazzoLuogo, Mazzo *mazzoSospetto) {
    Mazzo *mazzoTrippla = NULL;
    mazzoTrippla = initTripla(mazzoArmi, mazzoSospetto, mazzoLuogo, mazzoTrippla);
    stampaMazzo(mazzoTrippla);
    printf("\n\n");
    return mazzoTrippla;
}

//crea la lista mazzoSospetti
Mazzo *creaMazzoSospetti(Mazzo *mazzoSospetto) {
    //creazione array dinamico sospetto
    Carta cSospetto[] = {
            {"Alan Turing",     "7 anni fuoricorso ,gli manco solo l'esame di Programmazione",                           SOSPETTO},
            {"G.M. Hopper",    "E' stata una donna di un certo peso,45kg di idee lungimiranti.C'e sempre un altro bug", SOSPETTO},
            {"Edsger Dijkstra", "Si perso cercando la strada piu veloce per andare in bagno ",                           SOSPETTO},
            {"G.F. Voronoj",   "Amante della tassellazione divenne piastrellista a solo 12 anni ",                      SOSPETTO},
            {"J.V. Neumann",   "Provo ad entrare in Archittetura dove falli miseramente",                               SOSPETTO},
            {"M. Hamilton",     "Passo alla storia per aver scritto su carta il codice della missione Apollo 11",        SOSPETTO}
    };

    mazzoSospetto = initMazzo(N_ARMI_SOSPETTI, mazzoSospetto, cSospetto);
    mescolaMazzo(mazzoSospetto, 0, N_ARMI_SOSPETTI, MESCOLA);
    //stampaMazzo(mazzoSospetto);
    printf("\n\n");
    return mazzoSospetto;
}

//crea la lista mazzoLuoghi
Mazzo *creaMazzoLuoghi(Mazzo *mazzoLuogo) {
    //creazione array dinamico luoghi

    Carta cLuogo[] = {
            {"Laboratorio T", "Luogo conosciuto a tutti gli informatici,teatro di scontri epocali tra studenti e prove pratiche ",  STANZA},
            {"Laboratorio M", "Conosciuto dagli studenti magistrali, intravisto daquelli triennali, Nuovo, e destinato a !durare.", STANZA},
            {"Bagno",         "Luogo utilizzato negli anni per distruggere prove di copiatura e scaricare ansia pre-esame",         STANZA},
            {"Aula Costa",    "Grande ,pulita, luminosa.Ricorda i grandi anfiteatri dove parlavano gli oratori.",                   STANZA},
            {"Giardino",      "Ampio spazio,mai sfruttato,un tempo casa di Survivor",                                               STANZA},
            {"Entrata",       "Dinanzi a me non fuor cose create se non etterne , e io etterno duro.",                              STANZA},
            {"Parcheggio",    "Ambito da tutti gli studenti,salva da bestemmie e imprecazioni durante il periodo delle lezioni",    STANZA},
            {"Simaz",         "Luogo angusto e senza finestre.Posseggono le  chiavi del Palazzo che custodiscono con cura",         STANZA},
            {"BatCaverna",    "Luogo nascoso e ricco di scienza,pare sia popolato da individui dediti alla ricerca scientifica",    STANZA}
    };


    mazzoLuogo = initMazzo(N_LUOGHI, mazzoLuogo, cLuogo);
    mescolaMazzo(mazzoLuogo, 0, N_LUOGHI, MESCOLA);
    return mazzoLuogo;
}

//crea la lista mazzoArmi
Mazzo *creaMazzoArmi(Mazzo *mazzoArmi) {
    //creazione array dinamico armi
    Carta cArmi[] = {
            {"Cavo di Rete",    "Permette di strangolare la vittima senza perdita di dati.",                                        ARMA},
            {"Sparacoriandoli", "Puntato alla testa della vittima non lascia alcuna speranza.Se funziona.",                         ARMA},
            {"Calcinaccio",     "Cresce in modo sporadico attorno al Palazzo delle Scienze",                                        ARMA},
            {"Tastiera USB",    "La sua efficacia è data dalla quantità di batteri presenti tra i tasti A,S e D",                   ARMA},
            {"Fumo Caldaia",    "Incolore,inodore,insapore.Tutto quello che non è il fumo della caldaia",                           ARMA},
            {"Floppy Disk 3.5", "Il suo uso richiede abilita particolari.L'apertura scorrevole metallica è affilata e silenziosa ", ARMA}
    };


    mazzoArmi = initMazzo(N_ARMI_SOSPETTI, mazzoArmi, cArmi);
    mescolaMazzo(mazzoArmi, 0, N_ARMI_SOSPETTI, MESCOLA);
    //stampaMazzo(mazzoArmi);
    printf("\n\n");
    return mazzoArmi;


}

Mazzo *inserisciNodoinTesta(Mazzo *mazzo, Carta carta) {
    Mazzo *nuovoMazzo = (Mazzo *) malloc(sizeof(Mazzo));
    if (nuovoMazzo == NULL) {
        printf("errore di allocamento ");
        exit(-1);
    }
    nuovoMazzo->carte = carta;
    nuovoMazzo->next = mazzo;
    return nuovoMazzo;
}

//inizializza il mazzo tripla
Mazzo *initTripla(Mazzo *mazzoArmi, Mazzo *mazzoSospetti, Mazzo *mazzoLuoghi, Mazzo *mazzoTripla) {

    mazzoTripla = inserisciNodoinTesta(mazzoTripla, mazzoArmi->carte);
    mazzoTripla = inserisciNodoinTesta(mazzoTripla, mazzoSospetti->carte);
    mazzoTripla = inserisciNodoinTesta(mazzoTripla, mazzoLuoghi->carte);
    return mazzoTripla;
}

//mescola il  mazzo  scambiando le informazioni tra i due  nodi
void mescolaMazzo(Mazzo *mazzo, int min, int max, int nMescolate) {
    Carta carta, cartaClone;
    Mazzo *newMazzo = mazzo;
    int i, j;
    int firstPosition, secondPosition;
    mazzo = newMazzo;
    for (j = 0; j < nMescolate; ++j) {
        firstPosition = min + rand() % (max - min);
        secondPosition = min + rand() % (max - min);

        for (i = 0; i < firstPosition; ++i) {
            mazzo = mazzo->next;
        }
        carta = mazzo->carte;
        mazzo = newMazzo;
        for (i = 0; i < secondPosition; ++i) {
            mazzo = mazzo->next;
        }
        cartaClone = mazzo->carte;
        mazzo->carte = carta;
        mazzo = newMazzo;

        for (i = 0; i < firstPosition; ++i) {
            mazzo = mazzo->next;
        }

        mazzo->carte = cartaClone;
        mazzo = newMazzo;
    }
}

//stampa tutta la lista mazzo
void stampaMazzo(Mazzo *mazzo) {
    if (mazzo != NULL) {
        stampaCarta(mazzo->carte);
        stampaMazzo(mazzo->next);
    }

}

//stampa le informazioni della carta
void stampaCarta(Carta carta) {
    printf("Nome:%s -Tipo:%d\n", carta.nome, carta.tipoCarta);
}

//inizializza il mazzo
Mazzo *initMazzo(int nMazzo, Mazzo *mazzo, Carta carte[]) {
    int i;
    for (i = 0; i < nMazzo; ++i) {
        mazzo = inserisciNodoinTesta(mazzo, carte[i]);
    }
    return mazzo;
}

//dealocca la prima carta in testa della lista mazzo
Mazzo *eliminaCartaInTesta(Mazzo *mazzo) {
    Mazzo *aux = NULL;

    if (mazzo != NULL) {
        aux = mazzo->next;
        free(mazzo);
        mazzo = aux;
    }
    return mazzo;
}

//viene creato la lista mazzo con tutte le carte luogo armi e sospetti e dopodichè il mazzo viene mescolato
Mazzo *creaMazzoDiGioco(Mazzo *mazzoArmi, Mazzo *mazzoLuogo, Mazzo *mazzoSospetto, Mazzo *mazzoDiGioco) {
    while (mazzoArmi != NULL && mazzoSospetto != NULL) {
        mazzoDiGioco = inserisciNodoinTesta(mazzoDiGioco, mazzoArmi->carte);
        mazzoDiGioco = inserisciNodoinTesta(mazzoDiGioco, mazzoSospetto->carte);
        mazzoArmi = mazzoArmi->next;
        mazzoSospetto = mazzoSospetto->next;

    }
    while (mazzoLuogo != NULL) {
        mazzoDiGioco = inserisciNodoinTesta(mazzoDiGioco, mazzoLuogo->carte);
        mazzoLuogo = mazzoLuogo->next;
    }
//mescolamento  del mazzo
    mescolaMazzo(mazzoDiGioco, 0, N_MAZZO, MESCOLA);
    //1stampaMazzo(mazzoDiGioco);

    return mazzoDiGioco;

}

//dealocca tutta la  lista mazzo in maniera ricorsiva
void cancellaMazzo(Mazzo *mazzo) {
    if (mazzo != NULL) {
        cancellaMazzo(mazzo->next);
        free(mazzo);
    }
}

//conta la grandezza della lista
int contaGrandezzaMazzo(Mazzo *mazzo) {
    int count = 0;
    while (mazzo != NULL) {
        mazzo = mazzo->next;
        count++;
    }

    return count;
}

//ricerca l'elemento all'interno della lista mazzo e restituisce il nome della carta del suo nodo
char *ricercaElemento(Mazzo *mazzo, int val) {
    int i = 0;
    while (mazzo != NULL && i != val) { // CICLA FINO A CHE LA LISTA NON FINISCE

        mazzo = mazzo->next; // ALTRIMENTI ASSEGNA A LIST IL SUO NEXT
        i++;
    }
    return mazzo->carte.nome;
}


Mazzo *inserisciNodoInCoda(Mazzo *list, Carta carta){
    Mazzo *testa = list; // PUNTATORE DI TIPO NODO A CUI VIENE ASSEGNATA LA TESTA DELLA LISTA

    if(list == NULL){ // SE LA LISTA E' VUOTA RESTITUISCE LA FUNZIONE AGGIUNGI IN TESTA
        return inserisciNodoinTesta(list, carta);
    }

    while(list->next != NULL){ // SCORRI LA LISTA FINCHE' IL NEXT NON E' NULL
        list = list->next; // ASSEGNA A LIST L'INDIRIZZO DELL'ULTIMO NEXT
    }

    list->next = inserisciNodoinTesta(NULL, carta); // RICHIAMA LA FUNZIONE AGGIUNGI IN TESTA ED ASSEGNA UN VALORE IN CODA

    return testa; // RESTITUISCE LA TESTA DELLA LISTA
}

