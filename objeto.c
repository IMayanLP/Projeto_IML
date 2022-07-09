#include "objeto.h"

Objeto *criar_obj(char *arquivo, float x, float y, float lar, float alt, int ID){
    Objeto *obj = (Objeto*) malloc(sizeof(Objeto));

    obj->ID = ID;
    obj->img = al_load_bitmap(arquivo);
    obj->x = x/prop;
    obj->y = y/prop;
    obj->prop = prop;
    obj->lar = lar*prop;
    obj->alt = alt*prop;

    return obj;
}

void desenhar_obj(Objeto *obj){
    al_draw_bitmap(obj->img, obj->x,  obj->y, 0);
}

void destruir_obj(Objeto *obj){
    free(obj);
}

