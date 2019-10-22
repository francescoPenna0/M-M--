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

double poisson(double mu, double lambda, double stato)
{
    double nascita;
    nascita = ((pow(lambda / mu, stato)) / fact(stato)) * pow(2.71, -(lambda / mu));
    stato++;
    return nascita;
}

double calcolo_servitori(double NUTENTI, double servitori) {

    if (NUTENTI == 1)
        {
            servitori = 1;
            
        } else {
        
            servitori = NUTENTI * log(NUTENTI);

    }

    return servitori;

}