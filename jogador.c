#include "jogador.h"

Jogador *criar_jogador(ALLEGRO_BITMAP* spritesheet, float x, float y, float vel){
    Jogador *j = (Jogador*) malloc(sizeof(Jogador));

    int i;
    for(i = 0; i < 4; i++){
        j->up[i] = al_create_sub_bitmap(spritesheet, i*SPRITE_TAM, 0, SPRITE_TAM, SPRITE_TAM);
        j->left[i] = al_create_sub_bitmap(spritesheet, i*SPRITE_TAM, 64, SPRITE_TAM, SPRITE_TAM);
        j->right[i] = al_create_sub_bitmap(spritesheet, i*SPRITE_TAM, 128, SPRITE_TAM, SPRITE_TAM);
        j->down[i] = al_create_sub_bitmap(spritesheet, i*SPRITE_TAM, 192, SPRITE_TAM, SPRITE_TAM);
        j->dir[i] = 0;
    }
    j->vida_atual = 100;
    j->vida_max = 100;
    j->x = x/prop;
    j->y = y/prop;
    j->vel = vel;
    j->Satual = 0;
    j->moving = 0;
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
                if(colidiu(jogador, mapa)) {
                    jogador->dir[CIMA] = FALSE;
                    jogador->y += jogador->vel;
                }
                else jogador->y -= jogador->vel;
            }
        }
        if(jogador->dir[BAIXO]) {
            if((jogador->y + jogador->col->y + jogador->col->alt) + jogador->vel < SCREEN_HEIGTH) {
                if(colidiu(jogador, mapa)) {
                    jogador->dir[BAIXO] = FALSE;
                    jogador->y -= jogador->vel;
                }
                else jogador->y += jogador->vel;
            }
        }
        if(jogador->dir[DIR]) {
            if((jogador->x + jogador->col->x + jogador->col->lar) + jogador->vel < SCREEN_WIDTH) {
                if(colidiu(jogador, mapa)) {
                    jogador->dir[DIR] = FALSE;
                    jogador->x -= jogador->vel;
                }
                else jogador->x += jogador->vel;
            }
        }
        if(jogador->dir[ESQ]) {
            if((jogador->x + jogador->col->x) - jogador->vel > 0) {
                if(colidiu(jogador, mapa)) {
                    jogador->dir[ESQ] = FALSE;
                    jogador->x += jogador->vel;
                }
                else jogador->x -= jogador->vel;
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

int colidiu(Jogador *j, Objeto *obj[mapa_x][mapa_y]){
    // (x,y)
    return ((obj[coordMatriz(j->x + j->col->x)][coordMatriz(j->y + j->col->y)]->ID == PAREDE ||
       obj[coordMatriz(j->x + j->col->x + j->col->lar)][coordMatriz(j->y + j->col->y)]->ID == PAREDE ||
       obj[coordMatriz(j->x + j->col->x)][coordMatriz(j->y + j->col->y + j->col->alt)]->ID == PAREDE ||
       obj[coordMatriz(j->x + j->col->x + j->col->lar)][coordMatriz(j->y + j->col->y + j->col->alt)]->ID == PAREDE));
}

int coordMatriz(float coord){
    return ((int)(coord / SPRITE_TAM));
}

void desenhar_jogador(Jogador *j){
    al_draw_filled_rectangle(10, 30, 2*j->vida_max, 40, al_map_rgb(20, 20, 20));
    al_draw_filled_rectangle(10, 30, 2*j->vida_atual, 40, al_map_rgb(255, 100, 100));
    switch(j->orient){
        case 0: al_draw_bitmap(j->down[(int) j->Satual], j->x, j->y, 0); break;
        case 1: al_draw_bitmap(j->right[(int) j->Satual], j->x, j->y, 0); break;
        case 2: al_draw_bitmap(j->up[(int) j->Satual], j->x, j->y, 0); break;
        case 3: al_draw_bitmap(j->left[(int) j->Satual], j->x, j->y, 0); break;
    }
}

void destruir_jogador(Jogador *jogador){
    destruir_col(jogador->col);
    free(jogador);
}

