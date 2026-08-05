#define MINIAUDIO_IMPLEMENTATION
#include "../headers/miniaudio.h"
#include "../headers/estados.h"
#include "../headers/audio.h"
#include <stdio.h>

#define TOTAL_MUSICAS 5

typedef struct{
    const char *titulo;
    const char *arquivo;
} Musica;

static ma_engine engine;

/* Catálogo fixo de músicas */
static Musica radioPlaylist[TOTAL_MUSICAS] = {
    {"Mr. New Vegas", "../assets/sounds/radio/Mr-New-Vegas-Radio.mp3"},
    {"Big Iron",      "assets/sounds/radio/Big-Iron.mp3"},
    {"Blue Moon",     "assets/sounds/radio/Blue-Moon.mp3"},
    {"Johnny Guitar", "assets/sounds/radio/Johnny-Guitar.mp3"},
    {"Heartaches",    "assets/sounds/radio/Heartaches.mp3"}
};

int audioInit(){
    return ma_engine_init(NULL, &engine);
}

void audioClose(){
    ma_engine_uninit(&engine);
}

void playAudio(const char *arquivo){
    ma_engine_play_sound(&engine, arquivo, NULL);
}

void listar_radio(){

    printf("\n=========================\n");
    printf("       PIP-BOY RADIO\n");
    printf("=========================\n");

    for(int i = 0; i < TOTAL_MUSICAS; i++){
        printf("%d - %s\n", i + 1, radioPlaylist[i].titulo);
    }

    printf("0 - Voltar");
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