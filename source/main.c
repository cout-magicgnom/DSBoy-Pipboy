#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "headers/inventario.h"
#include "headers/audio.h"
#include "headers/miniaudio.h"
#include "headers/estados.h"

/*
TODO geral:
1. criar REMOVER itens 
2. separar as abas em arquivos (X)
3. comecar o radio 
4. comecar dados e stats

layout: 
    ____________
    |           |
    |telaInv()  |
    |           |
    |===========|
    |while(1)   |
    |printMenu()|
    |___________|
- Para compilar: 
gcc main.c system/inventario.c system/audio.c -o main
- Compilar dentro de src/
*/

Estado stats(){
    printf("\n\n/STATS/\n\n");
    return MENU;
}

int opcao(void){
    int op;
    printf("\n\nEscolha: ");
    scanf("%d", &op);
    return op;
}

/*
=============================================================
                        DADOS
=============================================================
*/
int dados(){
    /*
    TODO Dados:
    1."catalogo" de afazeres/rotas diarios
    2.
    */
    printf(" /DADOS/ ");

    int missoes[5] = {1};
    return 1;
}

/*
=============================================================
                        MAPA
=============================================================
*/
int mapa(){
    printf(" /MAPA/ ");
    return 1;
}



/*
=============================================================
MENU INICIAL
=============================================================
*/
Estado printMenu(){
    //talvez reclame do audioInit(); antes
    
    while(1){
        
        printf(" ==========================\n ");
        printf(" - PIPBOY OS - 1000A \n");
        printf(" ========================== \n");
        printf(" *STATS*  ");
        printf(" INV  ");
        printf(" DADOS  ");
        printf(" MAPA  ");
        printf(" RADIO\n");
        
        switch (opcao()){
            
        case 1:
            playAudio("assets/sounds/pipboy/ui_pipboy_mode.wav");
            return STATUS;
            break;
            
        case 2:
            playAudio("assets/sounds/pipboy/ui_pipboy_mode.wav");
            return INVENTARIO;
            break;
            
        case 3:
            playAudio("assets/sounds/pipboy/ui_pipboy_mode.wav");
            return DADOS;
            break;
            
        case 4: 
            playAudio("assets/sounds/pipboy/ui_pipboy_mode.wav");
            return MAPA;
            break;
            
        case 5:
            playAudio("assets/sounds/pipboy/ui_pipboy_mode.wav");
            return RADIO;
            break;

        case 0:
            return DESLIGAR;
        }
    }
}


/*
=============================================================
                        MAIN
=============================================================
*/

int main() {
    audioInit();
    EstadoInventario estadoInventario = LISTAR;
    Estado estadoAtual = MENU;
    
    while (estadoAtual != DESLIGAR){
        switch (estadoAtual){
            case MENU:
                estadoAtual = printMenu();
                break;

            case STATUS:
                estadoAtual = stats();
                break;

            case INVENTARIO:
                estadoAtual = telaInventario();
                break;

            case RADIO:
                estadoAtual = radio();
                break;
        }
    }

    printf("\n\nEncerrando . . .\n\n");
    return 0;
}


