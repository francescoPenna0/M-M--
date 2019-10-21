#include <stdlib.h>
#include <stdio.h>
#include <math.h>

unsigned int x;     // contatore del numero di utenti attualmente in servizio
unsigned int k = 0; // stato del sistema
typedef enum disponibilità
{
    disponibile,
    non_disponibile
};

enum dispobilità servitore;

double lambda;        // tasso di nascita degli utenti
double MU;            // tasso di morte degli utenti
double servitori = 1; // numero di servitori nel sistema

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
double poisson(double mu, double lambda, int k);
