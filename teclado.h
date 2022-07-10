#ifndef TECLADO_H_INCLUDED
#define TECLADO_H_INCLUDED

#include "jogo.h"

typedef struct tecla *Lista_teclas;

Lista_teclas *criar_lteclas();
int inserirTecla(Lista_teclas *, int);
int removerTecla(Lista_teclas *, int);
int pressionado(Lista_teclas *, int);

#endif // TECLADO_H_INCLUDED


