#include "caixa_colisao.h"

Caixa_colisao *criar_colisao(float x, float y, float lar, float alt){
    Caixa_colisao* col = (Caixa_colisao*)malloc(sizeof(Caixa_colisao));

    col->x = x;
    col->y = y;
    col->lar = lar;
    col->alt = alt;

    return col;
}

void destruir_col(Caixa_colisao* col){
    free(col);
}
