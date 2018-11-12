#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "reunion.h"

typedef struct reunion {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int entraron;
    int salir;
    int condicion;
}reunion;


Reunion *nuevaReunion(){
    Reunion *reu= (Reunion*) malloc(sizeof(Reunion));
    reu->entraron=0;
    reu->salir=0;
    reu->condicion=0;
    pthread_mutex_init(&reu->mutex, NULL);
    pthread_cond_init(&reu->cond, NULL);
    return reu;
}
void entrar(Reunion *r){
    r->entraron++;
}
void concluir(Reunion *r){
    pthread_mutex_lock(&r->mutex);
    r->salir++;
    if(r->salir==r->entraron){
        r->condicion=1;
    } else{
        while(r->condicion!=1){
            pthread_cond_wait(&r->cond, &r->mutex);
        }
    }
    pthread_cond_broadcast(&r->cond);
    pthread_mutex_unlock(&r->mutex);

}


