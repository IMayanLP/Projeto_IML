#include "botao.h"

Botao* criar_botao(char *arquivo, float x, float y, float lar, float alt, float prop){
   Botao* b = (Botao*) malloc(sizeof(Botao));

   b->img = al_load_bitmap(arquivo);
   b->x = x/prop;
   b->y = y/prop;
   b->prop = prop;
   b->lar = lar*prop;
   b->alt = alt*prop;

   return b;
}

int click_botao(Botao* b, float x, float y){
    if((x > b->x*b->prop) && (x < b->x*b->prop + b->lar) && (y > b->y*b->prop) && (y < b->y*b->prop + b->alt)) return 1;
    else return 0;
}

void desenhar_botao(Botao* b){
   al_draw_bitmap(b->img, b->x,  b->y, 0);
}

void destruir_botao(Botao* b){
    free(b);
}
