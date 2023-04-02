# Cluedo
gioco cluedo da console in c


I vari giocatori durante il gioco dovranno formulare le ipotesi del delitto del tipo: il sospettato ha ucciso
Djanni nella stanza con l’arma e gli altri giocatori confuteranno o confermeranno tale ipotesi.
Vince il giocatore che per primo indovinerà la tripla: sospetto, stanza e arma

Armi
Cavo di rete, Sparacoriandoli, Tastiera USB, Fumo della caldaia, Floppy disk 3.5, Calcinaccio


![5dca0a984dc2fd2af9980b3689c2e68e](https://user-images.githubusercontent.com/15201701/229329904-88efbdfa-e536-4f7c-b53c-7b5af1243810.png)


Sospetti
A. Turing, G. F. Voronoj, J. V. Neumann, E. Dijkstra, M. Hamilton, G. M. Hopper

![14a115425d11bc6f8534cb840932eca9](https://user-images.githubusercontent.com/15201701/229329960-1a511bbf-baf1-4c01-b3bb-e0e3cc86b5a1.png)



Stanze
Lab. T, Lab. M, Batcaverna, SimAz, Aula Costa, Entrata, Parcheggio, Bagno, Giardino

![7924959ee73119c3d1d8e474f4320cd6](https://user-images.githubusercontent.com/15201701/229329982-8b29deaa-3b6a-4dd9-8ccf-8c33afdaca6e.png)

Ogni carta è rappresentata da una struttura contenente la tipologia della carta (definita tramite
enumerazione: ARMA=0, SOSPETTO=1, STANZA=2) e il nome della stessa sotto forma di stringa.

I giocatori devono essere posizionati random in una stanza del Palazzo e per muoversi possono
lanciare due dadi da sei. Il giocatore iniziale deve essere scelto casualmente, poi si seguirà l’ordine dei
giocatori inseriti in precedenza. I dati dei giocatori devono essere memorizzati in un’apposita struttura
e memorizzati in un array allocato dinamicamente.
Una volta iniziato il gioco, ad ogni turno si stamperà il numero del turno, il nome del giocatore corrente
e dove egli si trova all’interno del tabellone. In questo momento del gioco dovrà essere permesso al
giocatore di salvare la partita all’interno di un file binario (chiamato “partita.sav”)

Una volta stampate queste informazioni dovrà essere chiesto all’utente se voglia provare a indovinare
le incognite o se voglia spostarsi in un’altra stanza. Nel primo caso verrà data la possibilità di formulare
l’ipotesi. Tale ipotesi può essere fatta su TUTTI i sospetti, TUTTE le armi ma obbligatoriamente nella
stanza in cui si trova il giocatore. Richieste queste informazioni, dovranno essere controllate tutte le
carte dei giocatori restanti, un giocatore alla volta, per verificare l’ipotesi del giocatore.
Appena si trova una carta che non soddisfa tale ipotesi, si interromperà il controllo degli altri giocatori
e si dovrà stampare un messaggio del tipo “L’ipotesi è errata.” visibile a tutti i giocatori. Dovrà poi
essere visualizzata SOLO al giocatore corrente la carta che ha confutato l’ipotesi (si faccia in modo che
se il giocatore che confuta l’ipotesi ha più carte sia esso stesso a scegliere quale mostrare).
Nel caso in cui nessun giocatore confuti l’ipotesi il giocatore che ha indovinato la tripla dovrà ottenere
al prossimo turno di lancio due dadi con lo stesso valore. Questo serve per recarsi nella cantina dove
potrà terminare il gioco. Se non viene effettuato un lancio di dadi doppi il turno passa al giocatore
successivo che cercherà quindi di recarsi nella stanza dove è avvenuto il delitto, formulare l’ipotesi e
fare un lancio doppio prima del o dei giocatori avversari.
Nel caso in cui un giocatore formuli un’ipotesi contenente una delle sue carte, il programma dopo aver
controllato tutti i giocatori seguendo l’ordine di gioco stamperà lo stesso messaggio di ipotesi errata. In
questo modo sarà chiaro che il giocatore stia bluffando. Non dovrà però essere mostrata a nessuno la
carta che ha reso l’ipotesi errata.
Nel caso in cui il giocatore voglia spostarsi in un’altra stanza dovrà essere effettuato un lancio di due
dadi e sulla base del risultato e della posizione del giocatore dovranno essere mostrate le stanze in cui
può recarsi (potrebbe non essercene neanche una raggiungibile e in quel caso il turno passa al
giocatore successivo dopo aver comunque dato la possibilità al giocatore di formulare l’ipotesi). Tra
quelle raggiungibili l’utente sceglierà quella in cui recarsi e potrà formulare o meno la sua ipotesi.
Nel caso in cui venga caricata una partita esistente da un file binario (chiamato “partita.sav”) dovranno
essere ovviamente saltati i passaggi iniziali per proseguire direttamente con il turno di gioco

![dbb4643e2d6deb9beeb484649ec25b41](https://user-images.githubusercontent.com/15201701/229330157-92e2e49d-8383-487c-b675-481fc0145c66.png)

Il tabellone rappresenta le stanze del Palazzo delle Scienze dove si svolge il gioco. Nella tabella
seguente, per ogni stanza è indicata la distanza da ogni altra stanza e deve essere utilizzata per gli
spostamenti dei giocatori all’interno del tabellone.



![877e7d0e64d7ea3de31e9b76e01257c9](https://user-images.githubusercontent.com/15201701/229330225-ea27e540-9c0e-422a-af72-d7dae75086ac.png)
