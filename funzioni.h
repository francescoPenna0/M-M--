#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct utente
{
    double pacchetto_nato; // nascita pacchetto
    double tempo;
} Utente;

typedef struct nodo
{
    Utente dato;
    struct nodo *next;
} Nodo;

typedef Nodo *Lista;

void nuovaLista(Lista *l);
void insTesta(Lista *l, Utente utente);
void elimTesta(Lista *l);
int fact(int n);
double poisson(double mu, double lambda, double *stato);
