#include "item.h"

Item criar_item(int id, float bonus, int atributo, Caixa_colisao col){
    Item item;
    item.sprite = al_load_bitmap("src/espada.png");
    item.ID = id;
    item.bonus = bonus;
    item.atributo = atributo;
    item.col = col;
    item.angulo = 0;

    return item;
}
