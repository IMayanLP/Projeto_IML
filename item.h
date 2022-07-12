#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include "jogo.h"
#include "caixa_colisao.h"

typedef struct {
    ALLEGRO_BITMAP* sprite;
    int ID;
    float angulo;
    float bonus;
    int atributo;
    Caixa_colisao col;
} Item;

Item criar_item(int , float, int, Caixa_colisao);
desenhar_item(Item);

#endif

