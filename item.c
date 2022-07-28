#include "item.h"

Item criar_item(int id, float bonus, int atributo){
    Item item;
    item.sprite = al_load_bitmap("src/espada.png");
    item.ID = id;
    item.bonus = bonus;
    item.atributo = atributo;
    item.angulo = 0;

    item.col[DIR] = *criar_colisao(40, 20, 40, 40);
    item.col[ESQ] = *criar_colisao(-20, 20, 40, 40);
    item.col[BAIXO] = *criar_colisao(11, 50, 40, 40);
    item.col[CIMA] = *criar_colisao(11, -20, 40, 40);

    return item;
}
