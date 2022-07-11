#ifndef INIMIGO_H_INCLUDED
#define INIMIGO_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "caixa_colisao.h"
#include "objeto.h"
#include "jogador.h"
#include "jogo.h"

typedef struct{
    int ID;

    float range;

    // movimenta��o
    int dir;
    int moving;
    float x, y, vel;

    // colis�o
    Caixa_colisao *col;

    // anima��o
    float Satual;
    int orient;
    ALLEGRO_BITMAP* up[4];
    ALLEGRO_BITMAP* left[4];
    ALLEGRO_BITMAP* right[4];
    ALLEGRO_BITMAP* down[4];
} Inimigo;

typedef struct lista_inimigos Inimigos;

Inimigos *criar_lInimigos();
int inserir_inimigo(Inimigos *, Inimigo);
void desenhar_inimigos(Inimigos *);
Inimigo criar_inimigo(ALLEGRO_BITMAP *, float, float, float);

void tick_inimigo(Inimigos *, Jogador *, Objeto *[mapa_x][mapa_y]);
int colidiu_inimigo(Inimigo *, Jogador *);
int colidiu_inimigo_M(Inimigo *, Objeto *[mapa_x][mapa_y], int);
int paz(Inimigo *, Jogador *);

#endif


