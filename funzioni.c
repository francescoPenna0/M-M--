#include "funzioni.h"
#include "thpool.h"

void nuovaLista(Lista *l)
{
    *l = NULL;
}

void insTesta(Lista *l, Utente utente)
{
    Nodo *aux = (Nodo *)malloc(sizeof(Nodo));
    aux->dato = utente;
    aux->next = *l;
    *l = aux;
}

void elimTesta(Lista *l)
{
    Nodo *aux = *l;
    *l = (*l)->next;
    free(aux);
}

int fact(int n)
{
    if (n == 0)
        return 1;
    else
        return n * fact(n - 1);
}

double poisson(double mu, double lambda, double stato)
{

    double nascita;

    nascita = ((pow(lambda / mu, stato)) / fact(stato)) * pow(2.71, -(lambda / mu));

    return nascita;
}

void generaUtenti(int NUTENTI)
{
    NUTENTI++;
}

void serviUtenti(Lista *l)
{

    useconds_t servizio = (1 / (*l)->dato.mu);

    usleep(servizio); //il pacchetto viene servito

    printf("Tempo nel sistema = tempo di servizio: %.3f\n", 1.0 / (*l)->dato.mu);

    elimTesta(l);
}
