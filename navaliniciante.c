#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 10
#define NAVIOS 5

void inicializarTabuleiro(char tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = '0'; // Água
        }
    }
}

void imprimirTabuleiro(char tabuleiro[TAMANHO][TAMANHO]) {
    printf("   ");
    for (int i = 1; i <= TAMANHO; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    char letras[] = "ABCDEFGHIJ";
    for (int i = 0; i < TAMANHO; i++) {
        printf("%c  ", letras[i]);
        for (int j = 0; j < TAMANHO; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char tabuleiro[TAMANHO][TAMANHO];
    inicializarTabuleiro(tabuleiro);
    imprimirTabuleiro(tabuleiro);
    return 0;
}