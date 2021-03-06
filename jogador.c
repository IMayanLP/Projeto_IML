#include "jogador.h"

Jogador *criar_jogador(ALLEGRO_BITMAP* spritesheet, ALLEGRO_BITMAP* coracao, float x, float y, float vel){
    Jogador *j = (Jogador*) malloc(sizeof(Jogador));

    int i;
    for(i = 0; i < 4; i++){
        j->up[i] = al_create_sub_bitmap(spritesheet, i*SPRITE_TAM, 0, SPRITE_TAM, SPRITE_TAM);
        j->left[i] = al_create_sub_bitmap(spritesheet, i*SPRITE_TAM, 64, SPRITE_TAM, SPRITE_TAM);
        j->right[i] = al_create_sub_bitmap(spritesheet, i*SPRITE_TAM, 128, SPRITE_TAM, SPRITE_TAM);
        j->down[i] = al_create_sub_bitmap(spritesheet, i*SPRITE_TAM, 192, SPRITE_TAM, SPRITE_TAM);
        j->dir[i] = 0;
    }
    j->vida[0] = al_create_sub_bitmap(coracao, 0, 0, 16, 16);
    j->vida[1] = al_create_sub_bitmap(coracao, 16, 0, 16, 16);
    j->vida_atual = 100;
    j->vida_max = 100;
    j->x = x/prop;
    j->y = y/prop;
    j->vel = vel;
    j->Satual = 0;
    j->moving = FALSE;
    j->orient = 1;

    j->col = criar_colisao(14, 20, 34, 40);

    return j;
}

void mover_jogador(Jogador *jogador, int key, int event){
    if(event == KEY_DOWN){
        switch(key){
        case ALLEGRO_KEY_W:
            jogador->moving = TRUE;
            jogador->dir[CIMA] = TRUE;
            jogador->orient = CIMA;
            break;
        case ALLEGRO_KEY_S:
            jogador->moving = TRUE;
            jogador->dir[BAIXO] = TRUE;
            jogador->orient = BAIXO;
            break;
        case ALLEGRO_KEY_D:
            jogador->moving = TRUE;
            jogador->dir[DIR] = TRUE;
            jogador->orient = DIR;
            break;
        case ALLEGRO_KEY_A:
            jogador->moving = TRUE;
            jogador->dir[ESQ] = TRUE;
            jogador->orient = ESQ;
            break;
        }
    }

    else if(event == KEY_UP){
        switch(key){
        case ALLEGRO_KEY_W:
            jogador->dir[CIMA] = FALSE;
            if(!andando(jogador)) jogador->moving = FALSE;
            break;
        case ALLEGRO_KEY_S:
            jogador->dir[BAIXO] = FALSE;
            if(!andando(jogador)) jogador->moving = FALSE;
            break;
        case ALLEGRO_KEY_D:
            jogador->dir[DIR] = FALSE;
            if(!andando(jogador)) jogador->moving = FALSE;
            break;
        case ALLEGRO_KEY_A:
            jogador->dir[ESQ] = FALSE;
            if(!andando(jogador)) jogador->moving = FALSE;
            break;
        }
    }
}

void tick_jogador(Jogador *jogador, Objeto *mapa[mapa_x][mapa_y]){
    if(jogador->moving){
        if(jogador->dir[CIMA]) {
            if((jogador->y + jogador->col->y) - jogador->vel > 0) {
                if(!colisao_PlayerMapa(jogador, mapa, CIMA)) {
                    jogador->y -= jogador->vel;
                }
            }
        }
        if(jogador->dir[BAIXO]) {
            if((jogador->y + jogador->col->y + jogador->col->alt) + jogador->vel < SCREEN_HEIGTH) {
                if(!colisao_PlayerMapa(jogador, mapa, BAIXO)) {
                    jogador->y += jogador->vel;
                }
            }
        }
        if(jogador->dir[DIR]) {
            if((jogador->x + jogador->col->x + jogador->col->lar) + jogador->vel < SCREEN_WIDTH) {
                if(!colisao_PlayerMapa(jogador, mapa, DIR)) {
                    jogador->x += jogador->vel;
                }
            }
        }
        if(jogador->dir[ESQ]) {
            if((jogador->x + jogador->col->x) - jogador->vel > 0) {
                if(!colisao_PlayerMapa(jogador, mapa, ESQ)) {
                    jogador->x -= jogador->vel;
                }
            }
        }

        if(jogador->Satual < 3.9) jogador->Satual += 0.1;
        else jogador->Satual = 0;
    } else  jogador->Satual = 0;
}

int andando(Jogador *j){
    for(int i = 0; i < 4; i++){
        if(j->dir[i]) {
            j->orient = i;
            return 1;
        }
    }
    return 0;
}

int colisao_PlayerMapa(Jogador *j, Objeto *obj[mapa_x][mapa_y], int dir){
    if(dir == CIMA){
        return ((obj[coordMatriz(j->x + j->col->x)][coordMatriz(j->y + j->col->y - j->vel)]->ID == PAREDE ||
               obj[coordMatriz(j->x + j->col->x + j->col->lar)][coordMatriz(j->y + j->col->y - j->vel)]->ID == PAREDE));
    }
    if(dir == DIR){
        return ((obj[coordMatriz(j->x + j->col->x + j->col->lar + j->vel)][coordMatriz(j->y + j->col->y)]->ID == PAREDE ||
               obj[coordMatriz(j->x + j->col->x + j->col->lar + j->vel)][coordMatriz(j->y + j->col->y + j->col->alt)]->ID == PAREDE));
    }
    if(dir == BAIXO){
        return ((obj[coordMatriz(j->x + j->col->x)][coordMatriz(j->y + j->col->y + j->col->alt + j->vel)]->ID == PAREDE ||
               obj[coordMatriz(j->x + j->col->x + j->col->lar)][coordMatriz(j->y + j->col->y + j->col->alt + j->vel)]->ID == PAREDE));
    }
    if(dir == ESQ){
        return ((obj[coordMatriz(j->x + j->col->x - j->vel)][coordMatriz(j->y + j->col->y)]->ID == PAREDE ||
               obj[coordMatriz(j->x + j->col->x - j->vel)][coordMatriz(j->y + j->col->y + j->col->alt)]->ID == PAREDE));
    }
}

void desenhar_jogador(Jogador *j){
    switch(j->orient){
        case CIMA: al_draw_bitmap(j->down[(int) j->Satual], j->x, j->y, 0); break;
        case DIR: al_draw_bitmap(j->right[(int) j->Satual], j->x, j->y, 0); break;
        case BAIXO: al_draw_bitmap(j->up[(int) j->Satual], j->x, j->y, 0); break;
        case ESQ: al_draw_bitmap(j->left[(int) j->Satual], j->x, j->y, 0); break;
    }
    int i;
    for(i = 0; i < 10; i++) al_draw_bitmap(j->vida[1], i*20+15, 30, 0);
    for(i = 0; i < j->vida_atual/10; i++) al_draw_bitmap(j->vida[0], i*20+15, 30, 0);
}

void destruir_jogador(Jogador *jogador){
    destruir_col(jogador->col);
    free(jogador);
}

