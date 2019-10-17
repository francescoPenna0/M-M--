#include <stdlib.h>
#include <stdio.h>

unsigned int  x;  // contatore del numero di utenti attualmente in servizio
unsigned int  k;  // contatore del numero di utenti attualmente nel sistema

typedef enum disponibilita {disponibile, non_disponibile};

enum disponibilita servitore; //il servitore è sempre disponibile, se non lo è mandiamo errore

double  nUtEntratiServ;  // contatore del numero di utenti entrati in servizio
double  nUtEntratiSist;  // accumula il numero di utenti entrati nel sistema

double  nUtUscitiServ;   // contatore del numero di utenti usciti dal servizio
double  nUtUscitiSist;   // accumula il numero di utenti usciti nel sistema  

double  nUtentiGenerati; // contatore del numero di utenti generati

double  tInterarrivo;       // tempo trascorso fra due arrivi consecutivi di utenti
double  tSimulazione;       // accumula il tempo di simulazione
double  tServitoreLibero;   // accumula il tempo in cui il servitore è libero


typedef struct utente {
    double  tx; // tempo di servizio assegnato
    double  tk; //tempo trascorso nel sistema
} Utente;

typedef struct nodo {
    Utente dato;
    struct nodo* next;
} Nodo;

typedef Nodo* Lista;

void nuovaLista(Lista* l);
void insTesta(Lista* l,Utente utente);
void gestioneUtente(Lista *l, Utente utente, int x, int k, int servitore);
void inizializzaSimulazionePacchetto(Lista* l,Utente utente, double accumula_tx);
void UtentiInIngresso(Utente utente);
void UtentiInUscita(Utente utente, int *x, int *k,double *nUtUscitiServ, double *nUtUscitiSist);
void simulazione();
void stampaRisultati();
