#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

typedef struct utente
{
    int n_utenti;
    float lambda;
    float mu;
    float tempo_servizio;

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
float poisson(float mu, float lambda, float stato);
void serviUtenti(Lista *l, FILE *ft);
double tempo_interarrivo(Utente u);