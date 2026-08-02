#ifndef ESTADOS_H
#define ESTADOS_H

typedef enum {
    LISTAR,
    ADICIONAR,
    REMOVER
} EstadoInventario;

typedef enum {
    MENU,
    STATUS,
    INVENTARIO,
    DADOS,
    MAPA,
    RADIO,
    CONFIG,
    DESLIGAR
} Estado;


int opcao(void);

#endif