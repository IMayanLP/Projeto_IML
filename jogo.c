#include "jogo.h"

int arredondar(float x){
    if(x != (int) x){
        return (int)x + 1;
    }
    return x;
}

int coordMatriz(float coord){
    return ((int)(coord / SPRITE_TAM));
}
