#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "botao.h"
#include "jogador.h"
#include "objeto.h"
#include "define.h"

// Teclado
#define KEY_SEEN     1
#define KEY_RELEASED 2

#define FPS 60

// iniciar elementos allegro
void must_init(bool test, const char *description){
    if(test) return;

    printf("Nao foi possivel carregar: %s\n", description);
    exit(1);
}

int bateu(int Ax, int Ay, int Bx, int By, int Aw, int Ah, int Bw, int Bh){
    if(Ax + Aw > Bx && Ax < Bx + Bw && Ay + Ah > By && Ay < By + Bw) return 1;
    return 0;
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
    ALLEGRO_BITMAP* spritesheet = al_load_bitmap("src/spritesheet.png");
    must_init(spritesheet, "sprites");

    Botao *botao = criar_botao("src/botao.png", 200, 200, 100, 100, red_x);
    int x = 0, y = 0;

    Jogador *jogador = criar_jogador(spritesheet, 200, 200, 3, red_x);

    Objeto *mapa[20][12];

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 12; j++){
            mapa[i][j] = criar_obj("src/folha.png", (i*64)*red_x, (j*64)*red_x, 64, 64, red_x, false, 4);
        }
    }

     destruir_obj(mapa[5][5]);
     mapa[5][5] = criar_obj("src/parede.png", (5*64)*red_x, (5*64)*red_x, 64, 64, red_x, true, 5);
     destruir_obj(mapa[8][7]);
     mapa[8][7] = criar_obj("src/parede.png", (8*64)*red_x, (7*64)*red_x, 64, 64, red_x, true, 5);

    while(!fim){
        ALLEGRO_EVENT evento;
        al_wait_for_event(fila_eventos, &evento);

        /** TICK **/
        if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
            if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) fim = true;
            mover_jogador(jogador, evento.keyboard.keycode, 0);
        }

        else if(evento.type == ALLEGRO_EVENT_KEY_UP){
            mover_jogador(jogador, evento.keyboard.keycode, 1);
        }

        else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
            x = evento.mouse.x;
            y = evento.mouse.y;
        }

        else if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(click_botao(botao, x, y)) printf("clicou");
        }

        else if(evento.type == ALLEGRO_EVENT_TIMER){
            if(key[ALLEGRO_KEY_ESCAPE]) fim = true;
            re_desenhar = true;
            // logica do jogo
            tick_jogador(jogador, mapa, red_x);
        }

        else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) fim = true;

        /** RENDER **/
        if(re_desenhar && al_is_event_queue_empty(fila_eventos)){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_filled_rectangle(0, 0, largura_tela, altura_tela, al_map_rgb(30, 30, 30));

            for(int i = 0; i < 20; i++){
                for(int j = 0; j < 12; j++){
                    if(mapa[i][j] != NULL) desenhar_obj(mapa[i][j]);
                }
            }

            for(int i = 0; i < SCREEN_HEIGTH; i++){
                al_draw_filled_rectangle(0, i*64, largura_tela, (i*64)+1, al_map_rgb(100, 100, 200));
            }
            for(int i = 0; i < SCREEN_WIDTH; i++){
                al_draw_filled_rectangle(i*64, 0, (i*64)+1, altura_tela, al_map_rgb(255, 200, 30));
            }

            desenhar_jogador(jogador);
            al_draw_rectangle(jogador->x, jogador->y, jogador->x + (jogador->lar/red_x), jogador->y + (jogador->alt/red_x), al_map_rgb(255, 255, 255), 1);

            al_draw_textf(font, al_map_rgb(0, 0, 0), 10, 10, 0, "<%.2f , %.2f>", jogador->x, jogador->y);
            al_draw_textf(font, al_map_rgb(0, 0, 0), 500, 10, 0, "<%d , %d>", (int)(jogador->x/64), (int)(jogador->y/64));
            al_flip_display();

            re_desenhar = false;
        }
    }

    // Destroi os bitmaps, fontes, tela, timer e tudo mais ao final do loop
    destruir_botao(botao);
    destruir_jogador(jogador);

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(fila_eventos);

    return 0;
}
