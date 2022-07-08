#ifndef BOTAO_H_INCLUDED
#define BOTAO_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

typedef struct {
    ALLEGRO_BITMAP* img;
    float x, y, alt, lar, prop;
} Botao;

Botao* criar_botao(char *, float, float, float, float, float);
int click_botao(Botao* b, float, float);
void desenhar_botao(Botao* b);
void destruir_botao(Botao* b);

#endif // BUTTON_H_INCLUDED
