#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#include "define.h"

typedef struct {
    // distancia do X e Y do player, largura e altura
    float x, y, lar, alt;
} Caixa_colisao;

Caixa_colisao *criar_colisao(float, float, float, float, float);

#endif // DEFINES_H_INCLUDED
