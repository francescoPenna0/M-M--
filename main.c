//Simulatore ad eventi di Sistemi a Coda di tipo MMInfinito - Ver. 1.0
//Copyright (C) 2019 Alfonso Esposito, Francesco Penna

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>

#include "funzioni.h"
#include "thpool.h"

int main(int argc, char const *argv[])
{

    int NUTENTI = 1;  // numero di utenti del sistema
    int input_utenti; // numero utenti inseriti da terminale
    //double k = 0;
    double lambda; // tasso di nascita degli utenti
    double MU;     // tasso di morte degli utenti

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
    scanf("%d", &input_utenti);

    threadpool generatori = thpool_init(3);               //3 che generano
    threadpool servitori = thpool_init(input_utenti + 1); //uno per ogni utente + 1 sempre disponibile

    printf("Inserire i valori di mu e lambda:\n");
    printf("Mu-->");
    scanf("%lf", &MU);
    printf("Lambda--> ");
    scanf("%lf", &lambda);

    NUTENTI += NUTENTI;
    utente.NUTENTI = NUTENTI;
    utente.lambda = lambda;
    utente.mu = MU;
    insTesta(&l, utente);

    while (NUTENTI != (input_utenti + 1))
    {

        thpool_wait(generatori);
        thpool_add_work(servitori, (void *)serviUtenti, (void *)(&l));

        utente.NUTENTI = NUTENTI;
        utente.lambda = lambda;
        utente.mu = MU;
        insTesta(&l, utente);

        thpool_add_work(generatori, (void *)generaUtenti, (void *)(&l));
    }

    fclose(ft);

    thpool_destroy(generatori);
    thpool_destroy(servitori);

    return 0;
}
