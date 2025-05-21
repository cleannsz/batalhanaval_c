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

int verificarEspaco(char tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho, int direcao) {
    for (int i = 0; i < tamanho; i++) {
        int x = linha + (direcao == 0 ? 0 : (direcao == 1 ? i : (direcao == 2 ? i : -i)));
        int y = coluna + (direcao == 1 ? i : (direcao == 2 ? -i : (direcao == 3 ? i : 0)));
        
        if (x < 0 || x >= TAMANHO || y < 0 || y >= TAMANHO || tabuleiro[x][y] != '0') {
            return 0;
        }
    }
    return 1;
}

void posicionarNavios(char tabuleiro[TAMANHO][TAMANHO]) {
    srand(time(NULL));
    int tamanhos[NAVIOS] = {5, 4, 3, 3, 2}; // Tamanhos dos navios
    
    for (int i = 0; i < NAVIOS; i++) {
        int tamanho = tamanhos[i];
        int linha, coluna, direcao;
        
        do {
            linha = rand() % TAMANHO;
            coluna = rand() % TAMANHO;
            direcao = rand() % 4; // 0 = horizontal, 1 = vertical, 2 = diagonal principal, 3 = diagonal secundária
        } while (!verificarEspaco(tabuleiro, linha, coluna, tamanho, direcao));
        
        for (int j = 0; j < tamanho; j++) {
            int x = linha + (direcao == 0 ? 0 : (direcao == 1 ? j : (direcao == 2 ? j : -j)));
            int y = coluna + (direcao == 1 ? 0 : (direcao == 2 ? j : (direcao == 3 ? j : 0)));
            tabuleiro[x][y] = 'N'; // Marcando navio
        }
    }
}

int main() {
    char tabuleiro[TAMANHO][TAMANHO];
    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);
    imprimirTabuleiro(tabuleiro);
    return 0;
}