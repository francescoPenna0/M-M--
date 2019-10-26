//Simulatore ad eventi di Sistemi a Coda di tipo MMInfinito - Ver. 1.0
//Copyright (C) 2019 Alfonso Esposito, Francesco Penna

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "mminfinito.h"

int main(int argc, char const *argv[])
{

    int input_utenti;         // numero utenti inseriti da terminale
    int k = 0;                // stato iniziale
    float nascita;            // variabile di appoggio poisson
    double tempoTot;          // variabile di appoggio
    double avarage;           // tempo medio di tra arrivi
    double tempo_simulazione; // tempo di tutta la simulazione

    clock_t start_ciclo, start_simluzione;
    clock_t end_ciclo, end_simulazione;

    Utente utente;            // struttura dati utente
    Lista l;                  // lista che vuole simulare il sistema
    FILE *ft;                 // file dove salvare i dati del processo

    nuovaLista(&l);           // inizializzo lista
    
    printf("Inserire il numero di utenti desiderato per avviare la simulazione:\n"); //richiedo inserimento N Utenti
    scanf("%d", &input_utenti);

    printf("Inserire i valori di mu e lambda:\n");                                   // richiedo inserimento parametri lambda e mu
    printf("Mu-->");
    scanf("%f", &utente.mu);
    printf("Lambda-->");
    scanf("%f", &utente.lambda);

    ft = fopen("m_m_infinito.txt", "wt");                                            // apro file in modalità di scrittura
    if (ft == NULL)
    {
        printf("Errore nell'apertura del file\n");
        exit(-1);
    }

    start_simluzione = clock(); // PARTE LA SIMULAZIONE

    for (utente.n_utenti = 1; utente.n_utenti < input_utenti + 1; utente.n_utenti++)
    {
        start_ciclo = clock();                                         // Calcolo tempo di nascita del pacchetto fino alla sua morte.
                                                 
        fprintf(ft, "Utente generato n° %d\n", utente.n_utenti); // GENERO UTENTE

        insTesta(&l, utente);                                    // Inserisco pacchetto in coda
        nascita = poisson(utente.mu, utente.lambda, k);          // Calcolo la P(k) per dato sperimentale
        k++;                                                     //con la nascita del pacchetto passo da uno stato 0 ad uno stato 1;

        fprintf(ft, "P(k) definita dalla legge di poisson è : %.3f\n", nascita);

        serviUtenti(&l, ft);                                     // servo l'utente e calcolo tempo di servizio
        elimTesta(&l);                                           // il pacchetto muore
        k--;                                                     //il pacchetto muore torno allo stato 0;

        fprintf(ft, "Il numero medio di pacchetti presenti nel sistema allo stato k è : %.3f\n", utente.lambda / utente.mu); 
        fprintf(ft, "************************************************************************\n");

        end_ciclo = clock();                                           // TERMINA VITA DEL PACCHETTO

        double tempo = ((double)(end_ciclo - start_ciclo)) / CLOCKS_PER_SEC; // calcolo la durata totale della vita del pacchetto
        tempoTot = tempo + tempoTot;
        avarage = tempoTot / input_utenti;

    }

    end_simulazione = clock();                                                 //TERMINA LA SIMULAZIONE

    fclose(ft);                                                     // CHIUDO IL FILE

    tempo_simulazione = ((double)(end_simulazione - start_simluzione)) / CLOCKS_PER_SEC; // CALCOLO DURATA DELLA SIMULAZIONE

    printf("**************************************RISULTATI*********************************************\n");
    printf("*                        Risultati per una simulazione m/m/inf                             *\n");
    printf("********************************************************************************************\n");
    printf("*                                        INPUT:                                            *\n");
    printf("*                        Numero di pacchetti serviti = %d cust                            *\n", input_utenti);
    printf("*                        Lambda scelto               = %.2f                               *\n", utente.lambda);
    printf("*                        Mu scelto                   = %.2f                               *\n", utente.mu);                           
    printf("*       Stato inziale: Coda vuota, stato K = 0, Sistema vuoto, Servitore disponibile       *\n");
    printf("********************************************************************************************\n");
    printf("*                                       OUTPUTS:                                           *\n");
    printf("*                        Tempo tatole simulato                = %3.4f sec                 *\n", tempo_simulazione);
    printf("*                        Tempo medio tra gli arrivi           = %lf sec               *\n", avarage);
    printf("*                        P(k) definita dalla legge di poisson = %.3f                      *\n", nascita);
    printf("*                        Tempo medio di servizio              = %lf sec               *\n", 1.0 / utente.mu);
    printf("*                        Utilizzo del server                  = %lf %%                *\n", 100.0 * (utente.lambda / utente.mu));
    printf("*                        Tempo medio di permanenza in coda    = 0.000 sec                  *\n");
    printf("*                   Numero medio di pacchetti presenti nel sistema = %lf cust         *\n", utente.lambda / utente.mu);
    printf("*                   Numero medio di pacchetti presenti in coda     = %lf cust         *\n", utente.lambda / utente.mu);
    printf("********************************************************************************************\n");

    return 0;
}