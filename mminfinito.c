#include "mminfinito.h"

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

float poisson(float mu, float lambda, float stato)
{

    float nascita;

    nascita = ((pow(lambda / mu, stato)) / fact(stato)) * pow(2.71, -(lambda / mu));

    return nascita;
}


void serviUtenti(Lista *l,FILE *ft)
{
    
    (*l)->dato.tempo_servizio = 1.0/(*l)->dato.mu;
    fprintf(ft,"Tempo di servizio: %.3f\n",(*l)->dato.tempo_servizio);

}

void stampaLista(Lista l){
    while(l){
        printf("%d %.3f %.3f %.3f\n", l->dato.n_utenti, l->dato.mu, l->dato.lambda,l->dato.tempo_servizio);
        l = l->next;
        } 
        printf("\n");
}