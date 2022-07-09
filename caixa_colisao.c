#include "caixa_colisao.h"

Caixa_colisao *criar_colisao(float x, float y, float lar, float alt, float prop){
    Caixa_colisao* col = (Caixa_colisao*)malloc(sizeof(Caixa_colisao));

    col->x = x/prop;
    col->y = y/prop;
    col->lar = lar;
    col->alt = alt;

    return col;
}
