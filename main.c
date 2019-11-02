//Simulatore ad eventi di Sistemi a Coda di tipo MMInfinito - Ver. 1.0
//Copyright (C) 2019 Alfonso Esposito, Francesco Penna

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "mminfinito.h"

int main(int argc, char const *argv[])
{

    int input_utenti; // numero utenti inseriti da terminale
    int k = 0;        // stato iniziale
    int confronto;
    float nascita;                         // variabile di appoggio poisson
    double tempoTot = 0;                   // variabile di appoggio
    double tempo_interarrivo_simulato = 0; // tempo medio di tra arrivi
    double tempo_simulazione = 0;          // tempo di tutta la simulazione
    double tempo_interrarivo_teorico = 0;
    double aspetta;
    srand(time(NULL));

    clock_t start_simluzione, start1;
    clock_t end_simulazione, end1;
    double tempo = 0;

    Utente utente; // struttura dati utente
    Lista l;       // lista che vuole simulare il sistema
    FILE *ft;      // file dove salvare i dati del processo

    nuovaLista(&l); // inizializzo lista

    printf("Inserire il numero di utenti desiderato per avviare la simulazione:\n"); //richiedo inserimento N Utenti
    scanf("%d", &input_utenti);

    printf("Inserire i valori di mu e lambda:\n"); // richiedo inserimento parametri lambda e mu
    printf("Mu-->");
    scanf("%f", &utente.mu);

    printf("Lambda-->");
    scanf("%f", &utente.lambda);

    if(utente.mu < utente.lambda) {

        printf("Errore nell'inserimento dei dati\n");
        exit(-1);

    }

    ft = fopen("m_m_infinito.txt", "wt"); // apro file in modalità di scrittura
    if (ft == NULL)
    {
        printf("Errore nell'apertura del file\n");
        exit(-2);
    }

    start_simluzione = clock(); // PARTE LA SIMULAZIONE

    nascita = poisson(utente.mu, utente.lambda, k); // Calcolo la P(k) per dato sperimentale
    nascita = nascita * 100;
    nascita = (float)nascita;
    utente.n_utenti = 0;

    do
    {

        confronto = rand() % 100;

        if (nascita > confronto)
        {

            fprintf(ft, "Utente generato n° %d\n", utente.n_utenti); // GENERO UTENTE

            insTesta(&l, utente); // Inserisco pacchetto in coda

            k++; //con la nascita del pacchetto passo da uno stato 0 ad uno stato 1;

            fprintf(ft, "P(k) definita dalla legge di poisson è : %.3f\n", nascita);

            serviUtenti(&l, ft); // servo l'utente e calcolo tempo di servizio
            elimTesta(&l);       // il pacchetto muore

            start1 = clock();
            aspetta = tempo_interarrivo(utente);

            k--; //il pacchetto muore torno allo stato 0;

            fprintf(ft, "Il numero medio di pacchetti presenti nel sistema allo stato k è : %.3f\n", utente.lambda / utente.mu);
            fprintf(ft, "************************************************************************\n");

            end1 = clock(); // TERMINA VITA DEL PACCHETTO

            tempo = ((double)(end1 - start1)) / CLOCKS_PER_SEC; // calcolo tempo medio di interarrivo
            tempo += aspetta;
            tempoTot = tempo + tempoTot;

            utente.n_utenti++;
        }
        else
        {

            continue;
        }

    } while (utente.n_utenti < input_utenti);

    tempo_interarrivo_simulato = (double)tempoTot;
    tempo_interrarivo_teorico = tempo_interarrivo(utente);

    end_simulazione = clock(); //TERMINA LA SIMULAZIONE

    fclose(ft); // CHIUDO IL FILE

    tempo_simulazione = ((double)(end_simulazione - start_simluzione)) / CLOCKS_PER_SEC; // CALCOLO DURATA DELLA SIMULAZIONE
    tempo_simulazione += tempoTot; 

    printf("********************************************************************************************\n");
    printf("*                        Risultati per una simulazione m/m/inf                             *\n");
    printf("********************************************************************************************\n");
    printf("*                                        INPUT:                                            *\n");
    printf("*                        Numero di pacchetti serviti = %d cust                            *\n", input_utenti);
    printf("*                        Lambda scelto               = %.2f                               *\n", utente.lambda);
    printf("*                        Mu scelto                   = %.2f                               *\n", utente.mu);
    printf("*       Stato inziale: Coda vuota, stato K = 0, Sistema vuoto, Servitore disponibile       *\n");
    printf("********************************************************************************************\n");
    printf("*                                       OUTPUTS:                                           *\n");
    printf("*                        Tempo tatole simulato                = %.4f sec                 *\n", tempo_simulazione);
    if(utente.n_utenti>1)
    {
    printf("*                        Tempo medio tra gli arrivi           = %lf sec               *\n", tempo_interarrivo_simulato);
    }
    printf("*                        P(k) definita dalla legge di poisson = %.3f                      *\n", nascita);
    printf("*                        Tempo medio di servizio              = %lf sec               *\n", 1.0 / utente.mu);
    printf("*                        Tempo medio di permanenza in coda    = 0.000 sec                  *\n");
    printf("********************************************************************************************\n");
    printf("*                                      DATI TEORICI:                                       *\n");
    printf("*                   Tempo di interarrivo teorico                   = %lf              *\n", tempo_interrarivo_teorico);
    printf("*                   Numero medio di pacchetti presenti nel sistema = %lf cust         *\n", utente.lambda / utente.mu);
    printf("*                   Numero medio di pacchetti presenti in coda     = %lf cust         *\n", utente.lambda / utente.mu);
    printf("********************************************************************************************\n");

    return 0;
}
