#include "jogador.h"

Jogador *criar_jogador(ALLEGRO_BITMAP* spritesheet, float x, float y, float vel, float prop){
    Jogador *j = (Jogador*) malloc(sizeof(Jogador));;

    int i;
    for(i = 0; i < 4; i++){
        j->up[i] = al_create_sub_bitmap(spritesheet, i*64, 0, 64, 64);
        j->left[i] = al_create_sub_bitmap(spritesheet, i*64, 64, 64, 64);
        j->right[i] = al_create_sub_bitmap(spritesheet, i*64, 128, 64, 64);
        j->down[i] = al_create_sub_bitmap(spritesheet, i*64, 192, 64, 64);
        j->dir[i] = 0;
    }
    j->x = x/prop;
    j->y = y/prop;
    j->vel = vel;
    j->Satual = 0;
    j->moving = 0;
    j->orient = 1;

    j->alt = 64*prop;
    j->lar = 64*prop;

    return j;
}

void mover_jogador(Jogador *jogador, int key, int event){
    if(event == 0){
        switch(key){
        case ALLEGRO_KEY_W:
            jogador->moving = 1;
            jogador->dir[CIMA] = 1;
            jogador->orient = 0;
            break;
        case ALLEGRO_KEY_S:
            jogador->moving = 1;
            jogador->dir[BAIXO] = 1;
            jogador->orient = 2;
            break;
        case ALLEGRO_KEY_D:
            jogador->moving = 1;
            jogador->dir[ESQ] = 1;
            jogador->orient = 1;
            break;
        case ALLEGRO_KEY_A:
            jogador->moving = 1;
            jogador->dir[DIR] = 1;
            jogador->orient = 3;
            break;
        }
    }

    else if(event == 1){
        switch(key){
        case ALLEGRO_KEY_W:
            jogador->dir[CIMA] = 0;
            if(!andando(jogador)) jogador->moving = 0;
            break;
        case ALLEGRO_KEY_S:
            jogador->dir[BAIXO] = 0;
            if(!andando(jogador)) jogador->moving = 0;
            break;
        case ALLEGRO_KEY_D:
            jogador->dir[ESQ] = 0;
            if(!andando(jogador)) jogador->moving = 0;
            break;
        case ALLEGRO_KEY_A:
            jogador->dir[DIR] = 0;
            if(!andando(jogador)) jogador->moving = 0;
            break;
        }
    }
}

void tick_jogador(Jogador *jogador, Objeto *mapa[20][12], float prop){
    //printf("ID: %d\n", aux->ID);
    if(jogador->moving){
        if(jogador->dir[CIMA]) {
            if(colidiu(jogador, mapa, prop)) {
                jogador->moving = 0;
                jogador->y += jogador->vel;
            }
            else jogador->y -= jogador->vel;
        }
        if(jogador->dir[BAIXO]) {
            if(colidiu(jogador, mapa, prop)) {
                jogador->moving = 0;
                jogador->y -= jogador->vel;
            }
            else jogador->y += jogador->vel;
        }
        if(jogador->dir[ESQ]) {
            if(colidiu(jogador, mapa, prop)) {
                jogador->moving = 0;
                jogador->x -= jogador->vel;
            }
            else jogador->x += jogador->vel;
        }
        if(jogador->dir[DIR]) {
            if(colidiu(jogador, mapa, prop)) {
                jogador->moving = 0;
                jogador->x += jogador->vel;
            }
            else jogador->x -= jogador->vel;
        }

        if(jogador->Satual < 3.9) jogador->Satual += 0.1;
        else jogador->Satual = 0;
    } else  jogador->Satual = 0;
}

void desenhar_jogador(Jogador *j){
    switch(j->orient){
        case 0: al_draw_bitmap(j->down[(int) j->Satual], j->x, j->y, 0); break;
        case 1: al_draw_bitmap(j->right[(int) j->Satual], j->x, j->y, 0); break;
        case 2: al_draw_bitmap(j->up[(int) j->Satual], j->x, j->y, 0); break;
        case 3: al_draw_bitmap(j->left[(int) j->Satual], j->x, j->y, 0); break;
    }
}

void destruir_jogador(Jogador *jogador){
    free(jogador);
}

int andando(Jogador *j){
    for(int i = 0; i < 4; i++){
        if(j->dir[i]) {
            if(i == 1) j->orient = 3;
            else if(i == 3) j->orient = 1;
            else j->orient = i;
            return 1;
        }
    }
    return 0;
}

int colidiu(Jogador *j, Objeto *obj[20][12], float prop){
    // (x,y)
    if(obj[coordMatriz(j->x)][coordMatriz(j->y)]->ID == 5 ||
       obj[coordMatriz(j->x+(j->lar/prop))][coordMatriz(j->y)]->ID == 5 ||
       obj[coordMatriz(j->x)][coordMatriz(j->y+(j->alt/prop))]->ID == 5 ||
       obj[coordMatriz(j->x+(j->lar/prop))][coordMatriz(j->y+(j->alt/prop))]->ID == 5) return 1;
    return 0;
}

int coordMatriz(float coord){
    return ((int)(coord / 64));
}
