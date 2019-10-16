#include <stdio.h>
#include <stdlib.h>
//metti al posto di int il formato di dato che ti serve
typedef int Dato;

typedef struct nodo {
  Dato dato;
  struct nodo* next;
} Nodo;

typedef Nodo* Lista;

void nuovaLista(Lista *pl);
int rnd_int(int min, int max);
void generaListaRandom(Lista *pl, int n);
void azzeramentoLista(Lista l);
void stampa(Lista l);
int lunghezzaLista(Lista l);
Lista *ricerca(Lista *l);
void insTesta(Lista* pl, Dato d);
void reverse(Lista l, Lista *pl2);
Lista arrayToList(int a[], int dl);
int* listToArray(Lista l);
void elimTesta(Lista* l);
Lista* ricercaOrd(Lista *l, int d);
void insOrd(Lista* l, int d);
int elim1(Lista* pl, int d);
int massimo(Lista l);