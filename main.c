//Simulatore ad eventi di Sistemi a Coda di tipo MMInfinito - Ver. 1.0
// Copyright (C) 2019 Alfonso Esposito, Francesco Penna

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "funzioni.h"

int main(int argc, char const *argv[])
{

    double NUTENTI = 1; // numero di utenti del sistema
    double input;       // numero utenti inseriti da terminale
    Utente utente;
    Lista l;
    FILE *ft;

    nuovaLista(&l);

    printf("Inserire il numero di utenti desiderato per avviare la simulazione:\n");
    scanf("%lf", &input);
    printf("\n");

    ft = fopen("M/M/inf.txt", "a");
    if (ft == NULL)
    {
        printf("errore nell'apertura del file\n");
        exit(-1);
    }

    while (NUTENTI != input)
    {
        printf("nascita pacchetto numero %f", NUTENTI);
        utente.pacchetto_nato = poisson(lambda, MU, k); //nascita pacchetto e passaggio allo stato 1
        utente.tempo = 1 / MU;                          //tempo trascorso complessivamente nel sistema
        insTesta(&l, utente);
        MU *= k;
        NUTENTI++;
        x++;
        servitori = pow(servitori, 2);

        fprintf(ft,"Il numero di utenti è %f\nIl numero di servitori è: %f\nIl tempo trascorso nel sistema è: %f\n",NUTENTI, servitori, l->dato.tempo);
        fprintf(ft, "*****************************************************************************************\n");
        elimTesta(&l);
    }

    fclose(ft);
    return 0;
}
