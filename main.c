//Simulatore ad eventi di Sistemi a Coda di tipo MMInfinito - Ver. 1.0 
//Copyright (C) 2019 Alfonso Esposito, Francesco Penna

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "funzioni.h"

int main(int argc, char const *argv[]) {
    
    double NUTENTI      = 1000000;  // numero di utenti del sistema
    double Y            = 1000000;  // massima dimensione della coda
    double lambda;                  // tasso di nascita degli utenti
    double MU           = 1;        // tasso di morte degli utenti
    double INCR_LAMBDA  = 0.01;     // incremento sul tasso di nascita degli utenti


    unsigned int  x;  // contatore del numero di utenti attualmente in servizio
    unsigned int  q;  // contatore del numero di utenti attualmente in coda
    unsigned int  k;  // contatore del numero di utenti attualmente nel sistema

    double accumula_tx; // accumula il tempo trascorso in servizio double accumula_tq
    double accumula_tq; // accumula il tempo trascorso in coda
    double accumula_tk; // accumula il tempo trascorso nel sistema

    double accumula_x; // accumula il numero di utenti attualmente in servizio double accumula_q
    double accumula_q;  // accumula il numero di utenti attualmente in coda
    double accumula_k;  // accumula il numero di utenti attualmente nel sistema

    double  nUtEntratiServ;  // contatore del numero di utenti entrati in servizio
    double  nUtEntratiCoda;  // accumula il numero di utenti entrati in coda
    double  nUtEntratiSist;  // accumula il numero di utenti entrati nel sistema

    double  nUtUscitiServ;   // contatore del numero di utenti usciti dal servizio
    double  nUtUscitiCoda;   // accumula il numero di utenti usciti in coda
    double  nUtUscitiSist;   // accumula il numero di utenti usciti nel sistema  

    double  nUtentiGenerati; // contatore del numero di utenti generati
    double  nUtentiPersi;    // contatore del numero di utenti persi per coda piena
    double  occorrenzeCodaPiena;  // numero di volte in cui la coda è piena

    double  tInterarrivo;  // tempo trascorso fra due arrivi consecutivi di utenti
    double  tSimulazione;  // accumula il tempo di simulazione
    double  tServitoreLibero;  // accumula il tempo in cui il servitore è libero
    double  tServitoreOccupato;  // accumula il tempo in cui il servitore è occupato
        
    Utente utente;
    Lista l;

    return 0;
}
