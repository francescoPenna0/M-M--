//Simulatore ad eventi di Sistemi a Coda di tipo MMInfinito - Ver. 1.0
//Copyright (C) 2019 Alfonso Esposito, Francesco Penna

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "funzioni.h"

int main(int argc, char const *argv[])
{

    double n;
    //int x = 0;                                                    // contatore del numero di utenti attualmente in servizio
    double k = 0;
    double lambda;        // tasso di nascita degli utenti
    double MU;            // tasso di morte degli utenti
    double servitori = 1; // numero di servitori nel sistema
    double NUTENTI = 1;   // numero di utenti del sistema
    double input;         // numero utenti inseriti da terminale
    Utente utente;
    Lista l;
    FILE *ft;

    nuovaLista(&l);

    srand(23);
    n = rand() % 1;
    printf("%f\n", n);

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

    do
    {

        utente.pacchetto_nato = poisson(lambda, MU, k); //nascita pacchetto
        printf("%f\n", utente.pacchetto_nato);
        if (n > 0 && n < utente.pacchetto_nato)
        {
            printf("Processo di nascita: %f\n", utente.pacchetto_nato);
            k++;     //con relativo passaggio allo stato 1
            MU *= k; //aggiornamento di mu dato da mu = mu * k

            insTesta(&l, utente); //un utente entra in testa alla coda per essere servito

            l->dato.tempo = 1 / MU; //tempo trascorso complessivamente nel sistema

            servitori = calcolo_servitori(NUTENTI, servitori);

            fprintf(ft, "Il numero di utenti è %.0f\nIl numero di servitori è: %.0f\nIl tempo trascorso nel sistema è: %f\n", NUTENTI, servitori, l->dato.tempo);
            fprintf(ft, "*******************************************\n");

            elimTesta(&l); //dopo essere stato servito viene eliminato
            k--;           //si ritorna allo stato k di 0 vista la morte

            NUTENTI++; //incremento il counter avendo servito un utente
        }

    } while (NUTENTI != (input + 1));

    fclose(ft);

    return 0;
}
