#include <stdlib.h>
#include <stdio.h>


typedef struct{
    double  tx; // tempo di servizio assegnato
    double  tq; //tempo trascorso in coda
    double  tk; //tempo trascorso nel sistema
} Utente;

typedef struct nodo{
    Utente dato;
    struct nodo* next;
}Nodo;

typedef Nodo* Lista;

double poisson(double RISOLUZIONE,double lambda);
void inizializzaSimulazione();
void inserisciInCoda(Utente utente);
Utente prelevaInTesta();
void gestisciUscitaUtente(Utente utente, int *x, int *k,double *nUtUscitiServ, double *nUtUscitiSist);
void gestisciServiUtenteInCoda(Utente *utente,int *x, int *q, double *nUtEntratiServ, double *nUtUscitiCoda);
void simulazione();
void stampaRisultati();
