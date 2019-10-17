#include "funzioni.h"


void nuovaLista(Lista* l){

    *l=NULL;

}

void insTesta(Lista* l,Utente utente){

    Nodo* aux=(Nodo*)malloc(sizeof(Nodo));
    aux->dato=utente;
    aux->next=*l;
    *l=aux;

}

void inizializzaSimulazionePacchetto(Lista* l,Utente utente,double accumula_tx){

    (*l)->dato.tk=0; // inizializzo tempo trascorso nel sistema. Dato che è appena arrivato inizializzo a 0
    (*l)->dato.tx=0; // inizializzo tempo di servizio a 0
    (*l)->dato.tx=(*l)->dato.tx+accumula_tx; // il tempo di servizio assegnato è dato dal tempo di arrivo del pacchetto + tempo complessivo di servizio da inizio simulazione
    
}

void UtentiInIngresso(Utente utente){
    
}