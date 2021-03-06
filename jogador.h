#ifndef JOGADOR_H_INCLUDED
#define JOGADOR_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "objeto.h"
#include "caixa_colisao.h"
#include "jogo.h"

typedef struct {
    // atributos
    float vida_max, vida_atual;

    // movimenta??o
    int dir[4];
    int moving;
    float x, y, vel;

    // colis?o
    Caixa_colisao *col;

    // anima??o
    float Satual;
    int orient;
    ALLEGRO_BITMAP* up[4];
    ALLEGRO_BITMAP* left[4];
    ALLEGRO_BITMAP* right[4];
    ALLEGRO_BITMAP* down[4];
    ALLEGRO_BITMAP* vida[2];
} Jogador;

Jogador *criar_jogador(ALLEGRO_BITMAP *, ALLEGRO_BITMAP*, float, float, float);
void mover_jogador(Jogador *, int, int);
void tick_jogador(Jogador *, Objeto *[mapa_x][mapa_y]);
int colisao_PlayerMapa(Jogador *, Objeto *[mapa_x][mapa_y], int);
void desenhar_jogador(Jogador *);
void destruir_jogador(Jogador *);

#endif // JOGADOR_H_INCLUDED
