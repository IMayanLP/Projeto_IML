/// Tamanho da tela
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGTH 720

/// Teclado
#define KEY_SEEN     1
#define KEY_RELEASED 2

/// FPS
#define FPS 60

/// Eventos
// Jogador
#define KEY_DOWN 0
#define KEY_UP 1

/// Mundo
#define SPRITE_TAM 64

// Tipos
#define CHAO 0
#define PAREDE 1

/// Jogador
#define CIMA 0
#define DIR 1
#define BAIXO 2
#define ESQ 3

#define ANDANDO 0
#define ATACANDO 1

#define SPRITE_INICIAL 0

/// Itens
#define ANGULO_CIMA 0.5
#define ANGULO_BAIXO 1.17
#define ANGULO_ESQ -1.17
#define ANGULO_DIR -0.5


int mapa_x;
int mapa_y;
float prop;

int arredondar(float);
int coordMatriz(float);
