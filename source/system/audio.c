#define MINIAUDIO_IMPLEMENTATION
#include "../headers/miniaudio.h"
#include <stdio.h>
#include "../headers/audio.h"
#include "../headers/estados.h"

#define TOTAL_MUSICAS 5

static ma_engine engine;
static ma_sound backgroundSound;

typedef struct{
    const char *titulo;
    const char *arquivo;
} Musica;

static ma_engine engine;

//Catálogo fixo de músicas
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

void playBackground(const char *arquivo){
    ma_sound_init_from_file(
        &engine,
        arquivo,
        0,
        NULL,
        NULL,
        &backgroundSound);

    ma_sound_set_looping(&backgroundSound, MA_TRUE);

    ma_sound_start(&backgroundSound);
}

void audioClose(){
    ma_engine_uninit(&engine);
}

void playAudio(const char *arquivo){
    ma_engine_play_sound(&engine, arquivo, NULL);
}

void listar_radio(){
        
    printf(" ==========================\n ");
    printf(" - PIPBOY OS - 1000A \n");
    printf(" ========================== \n");
    printf(" STATS  ");
    printf(" INV  ");
    printf(" DADOS  ");
    printf(" MAPA  ");
    printf(" *RADIO*\n");

    for(int i = 0; i < TOTAL_MUSICAS; i++){
        printf("%d - %s\n", i + 1, radioPlaylist[i].titulo);
    }

    printf("0 - Voltar\n");
}

Estado radio(){

    int escolha;

    while(1){

        listar_radio();

        escolha = opcao();

        if(escolha == 0){
            return MENU;      // Altere para o estado correto
        }

        if(escolha >= 1 && escolha <= TOTAL_MUSICAS){

            printf("Reproduzindo: %s\n",
                   radioPlaylist[escolha - 1].titulo);

            playAudio(radioPlaylist[escolha - 1].arquivo);
        }
        else{
            printf("Opcao invalida.\n");
        }
    }
}