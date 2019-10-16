#include <stdlib.h>
#include "listeCollegate.h"

void nuovaLista(Lista *pl) {
    *pl = NULL;
}

int rnd_int(int min, int max) {
  return min + rand() % (max - min + 1);
}

void generaListaRandom(Lista *pl, int n) {
    for(int i = 0; i < n; i++) {
        *pl = (Nodo*) malloc(sizeof(Nodo));
        (*pl)->dato = rnd_int(1,10);
        (*pl)->next = NULL;
        pl = &(*pl)->next;
    }
}

void azzeramentoLista(Lista l) {
    while(l) {
        l->dato = 0;
        l = l->next;
    }
}

void stampa(Lista l) {
    while(l) {
        printf("%d ", l->dato);
        l = l->next;
    }
    printf("\n");
}

int lunghezzaLista(Lista l) {
    int length = 0;
    while(l) { 
        length++;
        l = l->next;
    }
    return length;
}

Lista *ricerca(Lista *l) {
    while(*l) {
        l = &(*l) -> next;
    }
    return l;
}

void insTesta(Lista* pl, Dato d) {
    Nodo* aux = (Nodo*)malloc(sizeof(Nodo));
    aux->dato = d;
    aux->next = *pl;
    *pl = aux;
}

void reverse(Lista l, Lista *pl2) {
    *pl2 = NULL;
    while(l) {
        insTesta(pl2, l->dato);
        l = l -> next;
    }
}

Lista arrayToList(int a[], int dl) {
    Lista l = NULL;
    Lista *pl = &l;
    int i;
    for(int i = 0; i < dl; i++) {
        pl = ricerca(&l);
        insTesta(pl, a[i]);
    }
    return l;
}

int* listToArray(Lista l) {
  int n;
  int* v;
  int i;
  n = lunghezzaLista(l);
  v = (int*)malloc(n * sizeof(int));
  i = 0;
  while (l) {
    v[i] = l->dato;
    l = l->next;
    i++;
  }
  return v;
}

void elimTesta(Lista* l) {
  Nodo* aux = *l;
  *l = (*l)->next;
  free(aux);
}

Lista* ricercaOrd(Lista *l, int d) {
  while (*l) {
    if ((*l)->dato > d)
      break;
    l = &(*l)->next;
  }
  return l;   
}

void insOrd(Lista* l, int d) {
  l = ricercaOrd(l, d);
  insTesta(l, d);
}

int elim1(Lista* pl, int d) {
  pl = ricercaOrd(pl, d);
  if (*pl) {
    elimTesta(pl);
    return 1;
  } else
    return 0;
}

int massimo(Lista l) {
	int max;
	if (l == NULL) {
		exit(-1);
	}
	// inizializzo il massimo al primo elemento
	max = l->dato;
	l = l->next;
	// scorro la coda di l
	while (l) {
		if (l->dato > max)
		max = l->dato;
		l = l->next;
	}
	return max;
}