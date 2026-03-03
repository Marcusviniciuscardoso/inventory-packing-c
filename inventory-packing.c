/******************************************************************************
Online C Compiler.
Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.
*******************************************************************************/

#include <stdio.h>

#define MAX_ITEMS 10
#define MAX_LEVELS 100
#define MAX_COLUMNS_MALETA 10

typedef struct{
    int espacoUsado; // Espaço total usado na maleta
    int limiteLargura; // Largura máxima dos níveis de cada maleta
    int totalItensNivel; // Número total de itens neste nível
    int items[MAX_ITEMS]; /* Array de itens na qual o index é a sequência em que eles foram adicionados.
    O valor encontrado no index é o tamanho do item*/
} Level;

typedef struct{
    int itemCount; // Número total de itens global
    int totalNiveis; // Número total de itens presentes na maleta
    Level level[MAX_LEVELS]; // array de level(nível), na qual o index é o número do nível. O valor encontrado no index é o nível
} Maleta;

int main()
{
    char confirmaItem = 's';
    int tamanhoLargura = 0;
    int itemSize = 0;
    int itemAtual = 0;
    int itemCount = 0;
    //int items[MAX_ITEMS] = {0};
    int i;
    int nivelAtual = 0;

    Maleta maleta;

    printf("Qual a largura da maleta?\n");
    scanf("%d", &tamanhoLargura);

    maleta.totalNiveis = 1;
    maleta.level[nivelAtual].limiteLargura = tamanhoLargura;
    maleta.level[nivelAtual].totalItensNivel = 0;
    maleta.level[nivelAtual].espacoUsado = 0;
    maleta.itemCount = 0;

    while (confirmaItem == 's') {
        printf("Deseja adicionar um item ? (s/n) ");
        scanf(" %c", &confirmaItem);

        if (confirmaItem == 's') {
            printf("Qual o tamanho do item ? ");
            scanf("%d", &itemSize);

            if (itemSize > tamanhoLargura) {
                printf("Item maior que a largura da maleta. Tente outro.\n");
                continue;
            }

            int placed = 0;

            for (int l = 0; l < maleta.totalNiveis; l++){
                if (maleta.level[l].espacoUsado + itemSize <= maleta.level[l].limiteLargura){
                    if (maleta.level[l].totalItensNivel >= MAX_ITEMS) {
                        continue;
                    }

                    maleta.level[l].items[maleta.level[l].totalItensNivel] = itemSize;
                    maleta.level[l].totalItensNivel++;
                    maleta.level[l].espacoUsado += itemSize;
                    placed = 1;
                    break;
                }
            }

            if (!placed) {
                nivelAtual = maleta.totalNiveis;

                if (nivelAtual >= MAX_LEVELS) {
                    printf("Limite de niveis atingido (%d).\n", MAX_LEVELS);
                    break;
                }

                maleta.totalNiveis = nivelAtual + 1;

                maleta.level[nivelAtual].limiteLargura = tamanhoLargura;
                maleta.level[nivelAtual].totalItensNivel = 0;
                maleta.level[nivelAtual].espacoUsado = 0;

                if (maleta.level[nivelAtual].totalItensNivel >= MAX_ITEMS) {
                    printf("Limite de itens no nivel atingido (%d).\n", MAX_ITEMS);
                    break;
                }

                maleta.level[nivelAtual].items[maleta.level[nivelAtual].totalItensNivel] = itemSize;
                maleta.level[nivelAtual].totalItensNivel++;
                maleta.level[nivelAtual].espacoUsado += itemSize;
            }

            itemCount++;
            maleta.itemCount = itemCount;
            itemAtual++;
        }
    }

    printf("Itens adicionados: %d\n", itemCount);

    for (int n = 0; n < maleta.totalNiveis; n++) {
      printf("Itens no nivel %d: ", n);
      for (i = 0; i < maleta.level[n].totalItensNivel; i++) {
        printf("%d ", maleta.level[n].items[i]);
      }
      printf("(usado=%d)\n", maleta.level[n].espacoUsado);
    }

    /*
    int w = 10;

    for(i=0; i<=item.length;i++){
        bool placed = false;

        for(level=0; level <= levelsMaleta; level++){
            if(item.length <= w - level.length)
                level.storeItemSize(item.length);
            placed = true;
            break;
        }

        if (placed == false)
            newLevel = levesMaleta.newLevel();
            newLevel.storeItemSize(item.length);
    }
    */

    return 0;
}