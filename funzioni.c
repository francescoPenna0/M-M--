#include "funzioni.h"

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

double poisson(double mu, double lambda, int k)
{
    double nascita;
    nascita = ((pow(lambda / mu, k)) / fact(k)) * pow(2.71, -(lambda / mu));
    k++;
    return nascita;
}
