#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>

#include "thpool.h"

typedef struct utente {

    double mu;
    double lambda;
    int NUTENTI;

} Utente;

typedef struct nodo
{
    Utente dato; //dato è l'utente che entra in testa
    struct nodo *next;
} Nodo;

typedef Nodo *Lista;

void nuovaLista(Lista *l);
void insTesta(Lista *l, Utente utente);
void elimTesta(Lista *l);
void generaUtenti(int NUTENTI);
void serviUtenti(Lista *l);
int fact(int n);
double poisson(double mu, double lambda, double stato);
