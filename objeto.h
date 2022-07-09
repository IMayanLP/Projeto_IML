#ifndef OBJETO_H_INCLUDED
#define OBJETO_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

typedef struct {
    ALLEGRO_BITMAP* img;
    int ID;
    float x, y, alt, lar, prop;
} Objeto;

Objeto *criar_obj(char *, float, float, float, float, float, int);
void desenhar_obj(Objeto *);
void destruir_obj(Objeto*);

#endif // OBJETO_H_INCLUDED
