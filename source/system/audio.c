#define MINIAUDIO_IMPLEMENTATION
#include "../headers/miniaudio.h"
#include <stdio.h>
#include <stdbool.h>
#include <conio.h>      // getch(), kbhit()  -> Windows. Ver nota no final do arquivo para Linux.
#include <windows.h>    // Sleep()
#include "../headers/audio.h"
#include "../headers/estados.h"
#include <time.h>


#define TOTAL_MUSICAS 5

/* ============================================================
   CONFIGURACAO MODULAR DO BOTAO DE PLAY AUTOMATICO
   Para trocar qual tecla liga/desliga o autoplay, basta mudar
   este define. Nao precisa mexer em mais nada no codigo.
   ============================================================ */
#define TECLA_AUTOPLAY 'A'

/* Mesma ideia para o botao de pausar/retomar: so trocar a tecla aqui. */
#define TECLA_PAUSE 'P'

/* Teclas de navegacao (tambem podem ser remapeadas aqui) */
#define TECLA_SETA_CIMA   72   // codigo estendido da seta para cima
#define TECLA_SETA_BAIXO  80   // codigo estendido da seta para baixo
#define TECLA_ENTER       13
#define TECLA_ESC         27

typedef struct {
    const char *titulo;
    const char *arquivo;
} Musica;

static ma_engine engine;
static ma_sound  somAtual;
static bool      somCarregado  = false;
static int       indiceAtual   = -1;
static bool      autoPlayAtivo = false;
static bool      pausado       = false;

static Musica radioPlaylist[TOTAL_MUSICAS] = {
    {"Mr. New Vegas", "assets/sounds/pipboy/radiation/c/ui_pipboy_radiation_c_03.wav"},
    {"Big Iron",      "../assets/sounds/radio/Big-Iron.mp3"},
    {"Blue Moon",     "assets/sounds/radio/Blue-Moon.mp3"},
    {"Johnny Guitar", "assets/sounds/radio/Johnny-Guitar.mp3"},
    {"Heartaches",    "assets/sounds/radio/Heartaches.mp3"}
};

int audioInit(){
    return ma_engine_init(NULL, &engine);
}

/* Para o som que estiver tocando no momento, se houver algum */
static void pararSomAtual(){
    if (somCarregado){
        ma_sound_stop(&somAtual);
        ma_sound_uninit(&somAtual);
        somCarregado = false;
        pausado      = false;
    }
}

void audioClose(){
    pararSomAtual();
    ma_engine_uninit(&engine);
}

/* Toca uma musica da playlist. SEMPRE para a anterior antes de comecar
   a proxima, evitando que o audio fique sobreposto. */
static void tocarMusica(int indice){
    pararSomAtual();

    if (ma_sound_init_from_file(&engine, radioPlaylist[indice].arquivo,
                                 0, NULL, NULL, &somAtual) != MA_SUCCESS){
        printf("Erro ao carregar: %s\n", radioPlaylist[indice].arquivo);
        return;
    }

    ma_sound_start(&somAtual);
    somCarregado = true;
    indiceAtual  = indice;
    pausado      = false; // toda musica nova comeca tocando, nunca pausada
}

/* Alterna entre pausar e retomar a musica atual (mantendo a posicao,
   diferente de pararSomAtual, que descarta o som por completo). */
static void alternarPause(){
    if (!somCarregado) return;

    if (!pausado){
        ma_sound_stop(&somAtual);
        pausado = true;
    } else {
        ma_sound_start(&somAtual);
        pausado = false;
    }
}

/* Mantida por compatibilidade com o resto do projeto - agora tambem
   para qualquer som anterior antes de iniciar (evita sobreposicao). */
void playBackground(const char *arquivo){
    pararSomAtual();

    if (ma_sound_init_from_file(&engine, arquivo, 0, NULL, NULL, &somAtual) != MA_SUCCESS){
        return;
    }

    ma_sound_set_looping(&somAtual, MA_TRUE);
    ma_sound_start(&somAtual);
    somCarregado = true;
}

/* Mantida por compatibilidade - dispara um som "solto" pelo engine
   (nao e usada pelo radio, que usa tocarMusica para controlar sobreposicao) */
void playAudio(const char *arquivo){
    ma_engine_play_sound(&engine, arquivo, NULL);
}

/* ============================================================
   INTERFACE COM BOTOES (sem selecao por numero)
   ============================================================ */

static void desenharTela(int selecionado, int botaoAutoplay, int botaoPause, int botaoVoltar){
    system("cls"); // No Linux, troque por: system("clear");

    printf(" ==========================\n");
    printf(" - PIPBOY OS - 1000A \n");
    printf(" ==========================\n");
    printf(" STATS   INV   DADOS   MAPA   *RADIO*\n\n");

    for (int i = 0; i < TOTAL_MUSICAS; i++){
        printf("%s [ %-20s ]", (i == selecionado) ? " >" : "  ", radioPlaylist[i].titulo);

        if (i == indiceAtual && somCarregado)
            printf("  <-- tocando agora\n");
        else
            printf("\n");
    }

    printf("%s [ PLAY AUTOMATICO: %s ]  (atalho: tecla '%c')\n",
           (selecionado == botaoAutoplay) ? " >" : "  ",
           autoPlayAtivo ? "LIGADO" : "DESLIGADO",
           TECLA_AUTOPLAY);

    printf("%s [ %s ]  (atalho: tecla '%c')\n",
           (selecionado == botaoPause) ? " >" : "  ",
           pausado ? "RETOMAR" : "PAUSAR",
           TECLA_PAUSE);

    printf("%s [ VOLTAR ]\n", (selecionado == botaoVoltar) ? " >" : "  ");

    printf("\nSetas CIMA/BAIXO para navegar, ENTER para selecionar, ESC para voltar.\n");
}

Estado radio(){
    const int botaoAutoplay = TOTAL_MUSICAS;
    const int botaoPause    = TOTAL_MUSICAS + 1;
    const int botaoVoltar   = TOTAL_MUSICAS + 2;
    const int totalBotoes   = TOTAL_MUSICAS + 3;

    int selecionado = 0;

    desenharTela(selecionado, botaoAutoplay, botaoPause, botaoVoltar);

    while (1){

        /* Se o autoplay estiver ligado, a musica atual tiver terminado e
           nao estiver pausada, avanca automaticamente para a proxima. */
        if (autoPlayAtivo && somCarregado && !pausado && ma_sound_at_end(&somAtual)){
            int proximo = (indiceAtual + 1) % TOTAL_MUSICAS;
            tocarMusica(proximo);
            desenharTela(selecionado, botaoAutoplay, botaoPause, botaoVoltar);
        }

        if (kbhit()){
            int tecla = getch();

            if (tecla == 0 || tecla == 224){
                tecla = getch(); // segundo byte das teclas especiais (setas)

                if (tecla == TECLA_SETA_CIMA){
                    selecionado = (selecionado - 1 + totalBotoes) % totalBotoes;
                    desenharTela(selecionado, botaoAutoplay, botaoPause, botaoVoltar);
                }
                else if (tecla == TECLA_SETA_BAIXO){
                    selecionado = (selecionado + 1) % totalBotoes;
                    desenharTela(selecionado, botaoAutoplay, botaoPause, botaoVoltar);
                }
            }
            else if (tecla == TECLA_ENTER){
                if (selecionado < TOTAL_MUSICAS){
                    printf("Reproduzindo: %s\n", radioPlaylist[selecionado].titulo);
                    tocarMusica(selecionado);
                }
                else if (selecionado == botaoAutoplay){
                    autoPlayAtivo = !autoPlayAtivo;
                }
                else if (selecionado == botaoPause){
                    alternarPause();
                }
                else if (selecionado == botaoVoltar){
                    return MENU; // Altere para o estado correto, se necessario
                }
                desenharTela(selecionado, botaoAutoplay, botaoPause, botaoVoltar);
            }
            else if (tecla == TECLA_AUTOPLAY || tecla == (TECLA_AUTOPLAY + 32)){
                /* Atalho direto: funciona independente de onde o cursor
                   esteja. E isso que torna o botao "modular" - para mudar
                   a tecla, basta alterar o #define TECLA_AUTOPLAY no topo
                   do arquivo. */
                autoPlayAtivo = !autoPlayAtivo;
                desenharTela(selecionado, botaoAutoplay, botaoPause, botaoVoltar);
            }
            else if (tecla == TECLA_PAUSE || tecla == (TECLA_PAUSE + 32)){
                /* Mesma logica do atalho de autoplay: funciona de
                   qualquer lugar do menu e a tecla e trocavel via
                   #define TECLA_PAUSE. */
                alternarPause();
                desenharTela(selecionado, botaoAutoplay, botaoPause, botaoVoltar);
            }
            else if (tecla == TECLA_ESC){
                return MENU;
            }
        }

        struct timespec ts = {0, 50000000}; // 0.5 segundos
        nanosleep(&ts, NULL);; // evita uso excessivo de CPU
    }
}

/* ============================================================
   NOTA SOBRE PORTABILIDADE
   Este arquivo usa conio.h/windows.h (getch, kbhit, Sleep), que
   sao especificos do Windows - o padrao mais comum para esse tipo
   de projeto em C com console. Se voce compilar em Linux/Mac,
   sera preciso trocar:
     - system("cls")  -> system("clear")
     - getch()/kbhit() -> uma implementacao equivalente com termios
     - Sleep(ms)       -> usleep(ms * 1000) (de <unistd.h>)
   Se for esse o seu caso, me avise que eu adapto a versao inteira.
   ============================================================ */