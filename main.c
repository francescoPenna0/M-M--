//Simulatore ad eventi di Sistemi a Coda di tipo MMInfinito - Ver. 1.0
//Copyright (C) 2019 Alfonso Esposito, Francesco Penna

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#include "funzioni.h"
#include "thpool.h"

int main(int argc, char const *argv[])
{

    double k = 0;
    double lambda;        // tasso di nascita degli utenti
    double MU;            // tasso di morte degli utenti
    double servitori = 1; // numero di servitori nel sistema
    double NUTENTI = 1;   // numero di utenti del sistema
    double input;         // numero utenti inseriti da terminale
    double tempo_iniziale, tempo_finale, tempo_medio;
    Utente utente;
    Lista l;
    FILE *ft;

    nuovaLista(&l);

    ft = fopen("m_m_infinito.txt", "wt");
    if (ft == NULL)
    {
        printf("Errore nell'apertura del file\n");
        exit(-1);
    }

    printf("Inserire il numero di utenti desiderato per avviare la simulazione:\n");
    scanf("%lf", &input);

    printf("Inserire i valori di mu e lambda:\n");
    printf("Mu-->");
    scanf("%lf", &MU);
    printf("Lambda--> ");
    scanf("%lf", &lambda);

    while (NUTENTI != (input + 1))
    {
        k++;     //con relativo passaggio allo stato 1
        MU *= k; //aggiornamento di mu dato da mu = mu * k

        utente.pacchetto_nato = poisson(lambda, MU, k); //nascita pacchetto

        insTesta(&l, utente); //un utente entra in testa alla coda per essere servito

        l->dato.tempo = 1 / MU; //tempo trascorso complessivamente nel sistema

        servitori = calcolo_servitori(NUTENTI, servitori);

        fprintf(ft, "Il numero di utenti è %.0f\nIl numero di servitori è: %.0f\nIl tempo trascorso nel sistema è: %f\nLa probabilità di rimanere nello stato è: %f\n", NUTENTI, servitori, l->dato.tempo, l->dato.pacchetto_nato);
        fprintf(ft, "***************************************************\n");

        elimTesta(&l); //dopo essere stato servito viene eliminato
        k--;           //si ritorna allo stato k di 0 vista la morte

        NUTENTI++; //incremento il counter avendo servito un utente
    }

    fclose(ft);

    return 0;
}
//USARE FUNZIONE SLEEP O USLEEP O PRENDERE TEMPO CON UN CICLO PER SIMULARE
//IL SERVIZIO DEL SERVITORE PRIMA DI SPUTARLO PER CRONOMETRARLO