#include <stdio.h>
#include "../headers/inventario.h"
#include "../headers/estados.h"

#define MAX_ITENS 100

/*
=============================================================
                        INVENTARIO
=============================================================
*/

Estado mostrarInventario();

typedef struct {
    int id;
    char nome[50];
    float peso;
} Item;

// Item no inventário
typedef struct {
    Item item;
    int quantidade;
} SlotInventario;

// ---------------- CATÁLOGO ----------------

Item catalogo[] = {
    {1, "Stimpak", 0.1},
    {2, "RadAway", 0.2},
    {3, "10mm Pistol", 3.5},
    {4, "10mm Ammo", 0.01},
    {5, "Laser Rifle", 4.2}
};

int totalCatalogo = sizeof(catalogo) / sizeof(catalogo[0]);

// ---------------- INVENTÁRIO ----------------

SlotInventario inventario[MAX_ITENS];
int totalInventario = 0;

// ---------------- FUNÇÕES ----------------

// Procura um item no inventário pelo ID
int buscarItemInventario(int id) {
    for (int i = 0; i < totalInventario; i++) {
        if (inventario[i].item.id == id) {
            return i;
        }
    }
    return -1;
}

// Mostra catálogo
EstadoInventario mostrarCatalogo() {

    printf("\n===== CATALOGO =====\n");

    for (int i = 0; i < totalCatalogo; i++) {
        printf("%d - %s\n",
               catalogo[i].id,
               catalogo[i].nome);
    }
}


// Adiciona item ao inventário
void addItem(Item item, int quantidade) {
    int pos = buscarItemInventario(item.id);

    // Se já existe, soma quantidade
    if (pos != -1) {
        inventario[pos].quantidade += quantidade;
        return;
    }

    // Se não existe, cria novo slot
    inventario[totalInventario].item = item;
    inventario[totalInventario].quantidade = quantidade;
    totalInventario++;
    return;
}

// Adiciona item escolhido pelo usuário


// Mostra o inventário
void imprimirInventario(void)
{
    printf("\n===== INVENTARIO =====\n");

    if(totalInventario == 0){
        printf("Inventario vazio.\n");
        return;
    }

    for(int i = 0; i < totalInventario; i++){
        printf("[%d] %s x%d\n",
               inventario[i].item.id,
               inventario[i].item.nome,
               inventario[i].quantidade);
    }
}

EstadoInventario adicionarPorID() {
    int id;
    int qtd;
    int op = 0;

    mostrarCatalogo();
    printf("\nID do item: ");
    scanf("%d", &id);

    if(op == 0){
        //mostrarInventario();
        //return;
    }

    for (int i = 0; i < totalCatalogo; i++) {
        if (catalogo[i].id == id) {

            printf("Quantidade: ");
            scanf("%d", &qtd);

            addItem(catalogo[i], qtd);
            printf("\n%s adicionado ao inventario!\n", catalogo[i].nome);
            imprimirInventario();
            return LISTAR;
        }
    }
    printf("\nItem nao encontrado.\n\n");
    return adicionarPorID();
}

void removerItem(){
    int id;
    int i, j;

    for (i = 0; i < totalInventario; i++)
    {
        if (inventario[i].item.id == id)
        {
            if (inventario[i].quantidade > 1)
            {
                inventario[i].quantidade--;
            }
            else
            {
                /* Remove o slot deslocando os demais */
                for (j = i; j < totalInventario - 1; j++)
                {
                    inventario[j] = inventario[j + 1];
                }

                totalInventario--;
            }

            return;
        }
    }

    return;
}

Estado telaInventario(void){
    EstadoInventario estado = LISTAR;

    while (1) {

        switch (estado) {

            case LISTAR:

                printf(" ==========================\n ");
                printf(" - PIPBOY OS - 1000A \n");
                printf(" ========================== \n");
                printf(" STATS  ");
                printf(" INV  ");
                printf(" DADOS  ");
                printf(" MAPA  ");
                printf(" *RADIO*\n");

                imprimirInventario();

                printf("\n1 - Adicionar");
                printf("\n2 - Remover");
                printf("\n0 - Voltar");

                switch(opcao()) {

                    case 1:
                        estado = ADICIONAR;
                        break;

                    case 2:
                        estado = REMOVER;
                        break;

                    case 0:
                        return MENU;
                }

                break;

            case ADICIONAR:

                adicionarPorID();
                estado = LISTAR;
                break;

            case REMOVER:
                
                removerItem();
                estado = LISTAR;
                break;
        }
    }
}
