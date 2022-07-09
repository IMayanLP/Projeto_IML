#ifndef JOGADOR_H_INCLUDED
#define JOGADOR_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "objeto.h"
#include "caixa_colisao.h"
#include "define.h"

typedef struct {
    // atributos
    float vida_max, vida_atual;

    // movimentação
    int dir[4];
    int moving;
    float x, y, vel;

    // colisão
    Caixa_colisao *col;

    // animação
    float Satual;
    int orient;
    ALLEGRO_BITMAP* up[4];
    ALLEGRO_BITMAP* left[4];
    ALLEGRO_BITMAP* right[4];
    ALLEGRO_BITMAP* down[4];
} Jogador;

Jogador *criar_jogador(ALLEGRO_BITMAP *, float, float, float);
void mover_jogador(Jogador *, int, int);
void tick_jogador(Jogador *, Objeto *[mapa_x][mapa_y]);
void desenhar_jogador(Jogador *);
void destruir_jogador(Jogador *);
int andando(Jogador *);
int colidiu(Jogador *, Objeto *[mapa_x][mapa_y]);
int coordMatriz(float);

#endif // JOGADOR_H_INCLUDED
