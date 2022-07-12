#include "item.h"

Item criar_item(int id, float bonus, int atributo){
    Item item;
    item.sprite = al_load_bitmap("src/espada.png");
    item.ID = id;
    item.bonus = bonus;
    item.atributo = atributo;
    item.angulo = 0;

    item.col[DIR] = *criar_colisao(40, 20, 40, 40);
    item.col[ESQ] = *criar_colisao(0, 20, -40, 40);

    return item;
}
