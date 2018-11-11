//
// Created by erwin on 10-11-2018.
//
#include <stdio.h>
#include <stdlib.h>
#include "colapri.h"
#include "colapri-lista.h"

typedef struct nodo{
    void *data;
    struct nodo *sgte;
}Nodo;

typedef struct {
    ColaPriOps *ops;
    CompPri comp;
    int n;
    Nodo *raiz;
} ColaPriLista;

static void agregar(ColaPri colapri, void *a);
static void* extraer(ColaPri colapri);
static void* mejor(ColaPri colapri);
static int tamano(ColaPri colapri);
static void destruir(ColaPri colapri); /* debe estar vacia */
static IterColaP iterador(ColaPri colapri);

static ColaPriOps colapri_lista_ops= {
        agregar, extraer, mejor, tamano, destruir, iterador
};

ColaPri nuevaColaPriLista(CompPri comp) {
    ColaPriLista *cp= malloc(sizeof(ColaPriLista));
    cp->ops= &colapri_lista_ops;
    cp->comp= comp;
    cp->raiz= NULL;
    cp->n=0;
    return (ColaPri)cp;
}
/* Los elementos estan ordenados de mejor a peor prioridad */
static void agregar(ColaPri colapri, void *a) {
    ColaPriLista *cp= (ColaPriLista*)colapri;
    Nodo **ppnodo = &cp->raiz; /*puntero que apunta a la lista*/
    Nodo *pnodo = *ppnodo; /*aqui estoy parado en la raiz*/
    if(pnodo==NULL){
        *ppnodo=pnodo= (Nodo*) malloc(sizeof(Nodo));
        pnodo->data=a;
        pnodo->sgte=NULL;
    }else{
        int rel= (*cp->comp)(a, pnodo->data);
        if(rel<0){/* si a tiene mejor prioridad que el primer elemento*/
            Nodo *aux=malloc(sizeof(Nodo));
            aux->data=a;
            aux->sgte=pnodo;
            *ppnodo=pnodo=aux;
        } else{
            while(pnodo->sgte!=NULL && (*cp->comp)(a, pnodo->sgte->data)>0){
                ppnodo=&pnodo->sgte;
                pnodo=*ppnodo;
            }
            Nodo *aux =(Nodo*) malloc(sizeof(Nodo));
            aux->sgte=pnodo->sgte;
            aux->data=a;
            pnodo->sgte=aux;
            *ppnodo=pnodo;
        }
    }
    cp->n++;
}

static void* mejor(ColaPri colapri) {
    ColaPriLista *cp= (ColaPriLista*)colapri;
    Nodo **ppnodo = &cp->raiz;
    Nodo *pnodo=*ppnodo;
    return pnodo->data;
}

static int tamano(ColaPri colapri) {
    ColaPriLista *cp= (ColaPriLista*)colapri;
    return cp->n;
}

static void* extraer(ColaPri colapri) {
    ColaPriLista *cp= (ColaPriLista*)colapri;
    Nodo **ppnodo = &cp->raiz;
    void *res= cp->raiz->data;
    Nodo *pnodo=*ppnodo;
    *ppnodo=pnodo=pnodo->sgte;
    cp->n--;
    return res;
}

static void destruir(ColaPri colapri) {
    ColaPriLista *cp= (ColaPriLista*)colapri;
    free(cp->raiz);
    free(cp);
}

typedef struct {
    IterColaPOps *ops;
    ColaPriLista *cp;
    Nodo *actual;
} IterColaPLista;

static int continua(IterColaP iter);
static void* proximo(IterColaP iter);
static void destruirIter(IterColaP iter);

static IterColaPOps iterOps= { continua, proximo, destruirIter };

IterColaP iterador(ColaPri colapri) {
    IterColaPLista *iter= malloc(sizeof(IterColaPLista));
    iter->ops= &iterOps;
    iter->cp= (ColaPriLista*)colapri;
    iter->actual= iter->cp->raiz;
    return (IterColaP) iter;
}

static int continua(IterColaP itercp) {
    IterColaPLista *iter= (IterColaPLista*)itercp;
    return iter->actual!=NULL;
}

static void *proximo(IterColaP itercp) {
    IterColaPLista *iter= (IterColaPLista*)itercp;
    void *ret= iter->actual->data;
    Nodo **ppnodo = &iter->actual;
    Nodo *pnodo= *ppnodo;
    *ppnodo=pnodo= pnodo->sgte;
    return ret;
}

static void destruirIter(IterColaP iter) {
    free(iter);
}
