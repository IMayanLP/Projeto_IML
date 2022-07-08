#ifndef JOGADOR_H_INCLUDED
#define JOGADOR_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include "objeto.h"

#define CIMA 0
#define DIR 1
#define BAIXO 2
#define ESQ 3

typedef struct {
    // movimentação
    int dir[4];
    int moving;
    float x, y, vel;

    // colisão
    float alt, lar;

    // animação
    float Satual;
    int orient;
    ALLEGRO_BITMAP* up[4];
    ALLEGRO_BITMAP* left[4];
    ALLEGRO_BITMAP* right[4];
    ALLEGRO_BITMAP* down[4];
} Jogador;

Jogador *criar_jogador(ALLEGRO_BITMAP *, float, float, float, float);
void mover_jogador(Jogador *, int, int);
void tick_jogador(Jogador *, Objeto *[20][12], float);
void desenhar_jogador(Jogador *);
void destruir_jogador(Jogador *);
int andando(Jogador *);
int colidiu(Jogador *, Objeto *[20][12], float);
int coordMatriz(float);

#endif // JOGADOR_H_INCLUDED
