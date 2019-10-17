//Simulatore ad eventi di Sistemi a Coda di tipo MMInfinito - Ver. 1.0 
//Copyright (C) 2019 Alfonso Esposito, Francesco Penna

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "funzioni.h"

int main(int argc, char const *argv[]) {
    
    double NUTENTI;            // numero di utenti del sistema
    double Y = NUTENTI;        // massima dimensione della coda, resa uguale al numero di utenti per renderla "infinita"
    double lambda;             // tasso di nascita degli utenti
    double MU = 1;             // tasso di morte degli utenti
    double INCR_LAMBDA = 0.01; // incremento sul tasso di nascita degli utenti
        
    Utente utente;
    Lista l;

    printf("Inserire il numero di utenti desiderato per avviare la simulazione:\n");
    scanf("%f", &NUTENTI);

    return 0;
}
