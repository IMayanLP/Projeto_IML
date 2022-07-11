#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "inimigo.h"

struct elemento{
    Inimigo dados;
    struct elemento *prox;
};

typedef struct elemento Elemento;

struct lista_inimigos{
    int qtd;
    struct elemento *ini;
};

Inimigos *criar_lInimigos(){
    Inimigos *l = (Inimigos*)malloc(sizeof(Inimigos));
    if(l != NULL) {
        l->qtd = 0;
        l->ini = NULL;
    }
    return l;
}

int inserir_inimigo(Inimigos *l, Inimigo novoIni){
    if(l == NULL) return 0;
    Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
    novo->dados = novoIni;
    novo->prox = l->ini;
    l->ini = novo;
    l->qtd++;
    return 1;
}

Inimigo criar_inimigo(ALLEGRO_BITMAP *spritesheet, float x, float y, float vel){
    Inimigo ini;
    int i;
    for(i = 0; i < 4; i++){
        ini.up[i] = al_create_sub_bitmap(spritesheet, i*SPRITE_TAM, 0, SPRITE_TAM, SPRITE_TAM);
        ini.left[i] = al_create_sub_bitmap(spritesheet, i*SPRITE_TAM, 64, SPRITE_TAM, SPRITE_TAM);
        ini.right[i] = al_create_sub_bitmap(spritesheet, i*SPRITE_TAM, 128, SPRITE_TAM, SPRITE_TAM);
        ini.down[i] = al_create_sub_bitmap(spritesheet, i*SPRITE_TAM, 192, SPRITE_TAM, SPRITE_TAM);
    }

    ini.dir = 0;
    ini.x = x/prop;
    ini.y = y/prop;
    ini.vel = vel;
    ini.ID = 0;
    ini.range = 200;
    ini.orient = 1;
    ini.Satual = 0;
    ini.moving = FALSE;
    ini.col = criar_colisao(14, 20, 34, 40);

    return ini;
}

void desenhar_inimigos(Inimigos *l){
    if(l == NULL) return;
    if(l->ini == NULL) return;
    Elemento *aux = l->ini;
    while(aux != NULL){
        switch(aux->dados.orient){
            case BAIXO: al_draw_bitmap(aux->dados.down[(int) aux->dados.Satual], aux->dados.x, aux->dados.y, 0); break;
            case DIR: al_draw_bitmap(aux->dados.right[(int) aux->dados.Satual], aux->dados.x, aux->dados.y, 0); break;
            case CIMA: al_draw_bitmap(aux->dados.up[(int) aux->dados.Satual], aux->dados.x, aux->dados.y, 0); break;
            case ESQ: al_draw_bitmap(aux->dados.left[(int) aux->dados.Satual], aux->dados.x, aux->dados.y, 0); break;
        }
        al_draw_rectangle(aux->dados.x + aux->dados.col->x, aux->dados.y + aux->dados.col->y, aux->dados.x + aux->dados.col->x + aux->dados.col->lar, aux->dados.y + aux->dados.col->y + aux->dados.col->alt, al_map_rgb(255, 255, 255), 1);
        aux = aux->prox;
    }
}

void tick_inimigo(Inimigos *l, Jogador *j, Objeto *mapa[mapa_x][mapa_y]){
    if(l == NULL) return;
    if(l->ini == NULL) return;
    Elemento *aux = l->ini;
    while(aux != NULL){
        if(!paz(aux, j)){
            aux->dados.moving = TRUE;
        } else {
            aux->dados.moving = FALSE;
            aux->dados.Satual = 0;
        }

        if(colidiu_inimigo(aux, j)){
            j->vida_atual -= 0.1;
            aux->dados.moving = FALSE;
            aux->dados.Satual = 0;
        }

        if(aux->dados.moving){
            if(aux->dados.y < j->y) {
                if(!colidiu_inimigo_M(aux, mapa, 2)){
                    aux->dados.orient = CIMA;
                    aux->dados.y += aux->dados.vel;
                }
            }
            if(aux->dados.y > j->y) {
                if(!colidiu_inimigo_M(aux, mapa, 0)){
                    aux->dados.orient = BAIXO;
                    aux->dados.y -= aux->dados.vel;
                }
            }
            if(aux->dados.x < j->x && aux->dados.x < j->x + j->col->x) {
                if(!colidiu_inimigo_M(aux, mapa, 1)){
                    aux->dados.orient = DIR;
                    aux->dados.x += aux->dados.vel;
                }
            }
            if(aux->dados.x > j->x && aux->dados.x > j->x + j->col->x) {
                if(!colidiu_inimigo_M(aux, mapa, 3)){
                    aux->dados.orient = ESQ;
                    aux->dados.x -= aux->dados.vel;
                }
            }
            if(aux->dados.Satual < 3.9) aux->dados.Satual += 0.1;
            else aux->dados.Satual = 0;
        }
        aux = aux->prox;
    }
}

int coordMatriz_ini(float coord){
    return ((int)(coord / SPRITE_TAM));
}

int colidiu_inimigo_M(Inimigo *j, Objeto *obj[mapa_x][mapa_y], int dir){
    if(dir == 0){
        return ((obj[coordMatriz_ini(j->x + j->col->x)][coordMatriz_ini(j->y + j->col->y - j->vel)]->ID == PAREDE ||
               obj[coordMatriz_ini(j->x + j->col->x + j->col->lar)][coordMatriz_ini(j->y + j->col->y - j->vel)]->ID == PAREDE));
    }
    if(dir == 1){
        return ((obj[coordMatriz_ini(j->x + j->col->x + j->col->lar + j->vel)][coordMatriz_ini(j->y + j->col->y)]->ID == PAREDE ||
               obj[coordMatriz_ini(j->x + j->col->x + j->col->lar + j->vel)][coordMatriz_ini(j->y + j->col->y + j->col->alt)]->ID == PAREDE));
    }
    if(dir == 2){
        return ((obj[coordMatriz_ini(j->x + j->col->x)][coordMatriz_ini(j->y + j->col->y + j->col->alt + j->vel)]->ID == PAREDE ||
               obj[coordMatriz_ini(j->x + j->col->x + j->col->lar)][coordMatriz_ini(j->y + j->col->y + j->col->alt + j->vel)]->ID == PAREDE));
    }
    if(dir == 3){
        return ((obj[coordMatriz_ini(j->x + j->col->x - j->vel)][coordMatriz_ini(j->y + j->col->y)]->ID == PAREDE ||
               obj[coordMatriz_ini(j->x + j->col->x - j->vel)][coordMatriz_ini(j->y + j->col->y + j->col->alt)]->ID == PAREDE));
    }
}

int colidiu_inimigo(Inimigo *l, Jogador *j){
    return ((l->x + l->col->x > j->x + j->col->x && l->x + l->col->x < j->x + j->col->x + j->col->lar) &&
            (l->y + l->col->y > j->y + j->col->y && l->y + l->col->y < j->y + j->col->y + j->col->alt) ||
            (l->x + l->col->x + l->col->lar > j->x + j->col->x && l->x + l->col->x + l->col->lar < j->x + j->col->x + j->col->lar) &&
            (l->y + l->col->y > j->y + j->col->y && l->y + l->col->y < j->y + j->col->y + j->col->alt) ||
            (l->x + l->col->x > j->x + j->col->x && l->x + l->col->x < j->x + j->col->x + j->col->lar) &&
            (l->y + l->col->y + l->col->alt > j->y + j->col->y && l->y + l->col->y + l->col->alt < j->y + j->col->y + j->col->alt) ||
            (l->x + l->col->x + l->col->lar > j->x + j->col->x && l->x + l->col->x + l->col->lar < j->x + j->col->x + j->col->lar) &&
            (l->y + l->col->y + l->col->alt > j->y + j->col->y && l->y + l->col->y + l->col->alt < j->y + j->col->y + j->col->alt));
}

int paz(Inimigo *l, Jogador *j){
    float comp = sqrt(pow(l->x - j->x, 2) + pow(l->y - j->y, 2));
    return !(comp < l->range);
}
