#include <stdlib.h>
#include <stdio.h>
#include "teclado.h"

struct tecla{
    int ID;
    struct tecla *prox;
};

typedef struct tecla Tecla;

Lista_teclas *criar_lteclas(){
    Lista_teclas *l = (Lista_teclas*)malloc(sizeof(Lista_teclas));
    if(l != NULL) *l = NULL;
    return l;
}

int inserirTecla(Lista_teclas *l, int id){
    if(l == NULL) return 0;
    Tecla *novo = (Tecla *)malloc(sizeof(Tecla));
    novo->ID = id;
    novo->prox = *l;
    *l = novo;
    return 1;
}

int removerTecla(Lista_teclas *l, int id){
    if(l == NULL) return 0;
    if(*l == NULL) return 0;
    Tecla *aux = *l, *ant = NULL;
    if(aux->ID == id){
        *l = aux->prox;
        free(aux);
        return 1;
    }
    while(aux != NULL && aux->ID != id){
        ant = aux;
        aux = aux->prox;
    }
    if(aux == NULL) return 0;
    ant->prox = aux->prox;
    free(aux);
    return 1;
}

int pressionado(Lista_teclas *l, int id){
    if(l == NULL) return 0;
    if(*l == NULL) return 0;
    Tecla *aux = *l;
    while(aux != NULL){
        if(aux->ID == id) return 1;
        else aux = aux->prox;
    }
    return 0;
}
