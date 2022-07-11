#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "botao.h"
#include "jogador.h"
#include "inimigo.h"
#include "objeto.h"
#include "teclado.h"
#include "jogo.h"

// iniciar elementos allegro
void must_init(bool test, const char *description){
    if(test) return;

    printf("Nao foi possivel carregar: %s\n", description);
    exit(1);
}

int main(){
    // Iniciando allegro, teclado e mouse
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");

    /**MONITOR E TELA DO JOGO*/
    // TELA CHEIA
    ALLEGRO_MONITOR_INFO info; // informacoes do monitor
    int largura_tela, altura_tela; // resolucao X e Y do computador
    al_get_monitor_info(0, &info); // recolhendo informacoes do monitor para o struct info
    largura_tela = info.x2 - info.x1; // x1-> largura inicial da tela (0) || x2 -> largura final da tela
    altura_tela = info.y2 - info.y1; // mesma logica de cima

    // Flags do display
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR); // menos essa, essa eh dos bitmaps

    ALLEGRO_DISPLAY* disp = al_create_display(largura_tela, altura_tela); // criando display do tamanho do monitor;
    must_init(disp, "display"); // iniciando display

    float red_x = largura_tela / (float) SCREEN_WIDTH; // largura redimensionada
    float red_y = altura_tela / (float) SCREEN_HEIGTH; // altura redimensionada

    // Transformacao para manter a proprocao com o monitor
    ALLEGRO_TRANSFORM transformar;
    al_identity_transform(&transformar);
    al_scale_transform(&transformar, red_x, red_y);
    al_use_transform(&transformar);

    /**COISAS DO JOGO**/
    // Iniciando timer (limitador de FPS)
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    must_init(timer, "timer");

    // Iniciando fonte
    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");

    // Criando fila de eventos
    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue();
    must_init(fila_eventos, "fila de eventos");

    // Iniciando formas primitivas (linha, retangulo e os carai)
    must_init(al_init_primitives_addon(), "primitives");

    // registrando a fonte dos eventos na fila de eventos
    al_register_event_source(fila_eventos, al_get_keyboard_event_source()); // teclado
    al_register_event_source(fila_eventos, al_get_mouse_event_source()); // mouse
    al_register_event_source(fila_eventos, al_get_display_event_source(disp)); // display
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer)); // timer

    //al_hide_mouse_cursor(disp); // esconde o mouse

    // Imagem
    must_init(al_init_image_addon(), "imagens");

    bool fim = false; // booleano para o fim do jogo
    bool re_desenhar = true; // booleano para renderizar

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    // Iniciando timer
    al_start_timer(timer);

    /** VARIAVEIS DO JOGO **/
    int x = 0, y = 0;
    prop = red_x;
    srand(time(NULL));

    ALLEGRO_BITMAP* spritesheet = al_load_bitmap("src/spritesheet.png");
    must_init(spritesheet, "sprites");

    ALLEGRO_BITMAP* bruxo = al_load_bitmap("src/bruxo.png");
    must_init(bruxo, "bruxo");

    ALLEGRO_BITMAP* coracao = al_load_bitmap("src/coracao.png");
    must_init(coracao, "coracao");

    Inimigos *mobs = criar_lInimigos();

    inserir_inimigo(mobs, criar_inimigo(spritesheet, 500, 300, 1.5));
    inserir_inimigo(mobs, criar_inimigo(spritesheet, 700, 500, 2));

    Jogador *jogador = criar_jogador(bruxo, coracao, 200, 200, 3);

    mapa_x = arredondar((float) SCREEN_WIDTH / (float) SPRITE_TAM);
    mapa_y = arredondar((float) SCREEN_HEIGTH / (float) SPRITE_TAM);

    Objeto *mapa[mapa_x][mapa_y];

    for(int i = 0; i < mapa_x; i++){
        for(int j = 0; j < mapa_y; j++){
            mapa[i][j] = criar_obj("src/folha.png", (i*SPRITE_TAM)*prop, (j*SPRITE_TAM)*prop, SPRITE_TAM, SPRITE_TAM, CHAO);
        }
    }

    int i;
    for(i = 0; i < 4; i++){
        int num_x = rand() % mapa_x;
        int num_y = rand() % mapa_y;
        destruir_obj(mapa[num_x][num_y]);
        mapa[num_x][num_y] = criar_obj("src/parede.png", (num_x*SPRITE_TAM)*prop, (num_y*SPRITE_TAM)*prop, SPRITE_TAM, SPRITE_TAM, PAREDE);
    }

    while(!fim){
        ALLEGRO_EVENT evento;
        al_wait_for_event(fila_eventos, &evento);

        /** TICK **/
        if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
            if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) fim = true;
            mover_jogador(jogador, evento.keyboard.keycode, KEY_DOWN);
        }

        else if(evento.type == ALLEGRO_EVENT_KEY_UP){
            mover_jogador(jogador, evento.keyboard.keycode, KEY_UP);
        }

        else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
            x = evento.mouse.x;
            y = evento.mouse.y;
        }

        else if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        }

        else if(evento.type == ALLEGRO_EVENT_TIMER){
            if(key[ALLEGRO_KEY_ESCAPE]) fim = true;
            re_desenhar = true;
            // logica do jogo
            if(jogador->vida_atual <= 0) fim = true;
            tick_inimigo(mobs, jogador, mapa);
            tick_jogador(jogador, mapa);
        }

        else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) fim = true;

        /** RENDER **/
        if(re_desenhar && al_is_event_queue_empty(fila_eventos)){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_filled_rectangle(0, 0, largura_tela, altura_tela, al_map_rgb(30, 30, 30));

            for(int i = 0; i < mapa_x; i++){
                for(int j = 0; j < mapa_y; j++){
                    if(mapa[i][j] != NULL) desenhar_obj(mapa[i][j]);
                }
            }

            desenhar_jogador(jogador);

            al_draw_rectangle(jogador->x + jogador->col->x, jogador->y + jogador->col->y, jogador->x + jogador->col->x + (jogador->col->lar), jogador->y + jogador->col->y + (jogador->col->alt), al_map_rgb(255, 255, 255), 1);

            desenhar_inimigos(mobs);

            al_draw_textf(font, al_map_rgb(0, 0, 0), 10, 10, 0, "<%.2f , %.2f>", jogador->x, jogador->y);
            al_flip_display();

            re_desenhar = false;
        }
    }

    // Destroi os bitmaps, fontes, tela, timer e tudo mais ao final do loop
    destruir_jogador(jogador);

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(fila_eventos);

    return 0;
}
