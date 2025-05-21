#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 10
#define NAVIOS 5
#define TAM_HABILIDADE 5

void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

void imprimirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("   ");
    for (int i = 1; i <= TAMANHO; i++) {
        printf("%d ", i);
    }
    printf("\n");

    char letras[] = "ABCDEFGHIJ";
    for (int i = 0; i < TAMANHO; i++) {
        printf("%c  ", letras[i]);
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == 0) {
                printf("~ ");
            } else if (tabuleiro[i][j] == 3) {
                printf("N ");
            } else if (tabuleiro[i][j] == 5) {
                printf("* ");
            } else {
                printf("? ");
            }
        }
        printf("\n");
    }
}

void posicionarNavios(int tabuleiro[TAMANHO][TAMANHO]) {
    srand(time(NULL));
    int tamanhos[NAVIOS] = {5, 4, 3, 3, 2};

    for (int i = 0; i < NAVIOS; i++) {
        int tamanho = tamanhos[i];
        int linha, coluna, direcao;

        int colocado = 0;
        while (!colocado) {
            linha = rand() % TAMANHO;
            coluna = rand() % TAMANHO;
            direcao = rand() % 2;

            int podeColocar = 1;
            for (int j = 0; j < tamanho; j++) {
                int x = linha + (direcao == 1 ? j : 0);
                int y = coluna + (direcao == 0 ? j : 0);

                if (x >= TAMANHO || y >= TAMANHO || tabuleiro[x][y] != 0) {
                    podeColocar = 0;
                    break;
                }
            }

            if (podeColocar) {
                for (int j = 0; j < tamanho; j++) {
                    int x = linha + (direcao == 1 ? j : 0);
                    int y = coluna + (direcao == 0 ? j : 0);
                    tabuleiro[x][y] = 3;
                }
                colocado = 1;
            }
        }
    }
}

void criarCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = 0;
            if (j >= TAM_HABILIDADE / 2 - i && j <= TAM_HABILIDADE / 2 + i)
                habilidade[i][j] = 1;
        }
    }
}

void criarCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = (i == TAM_HABILIDADE / 2 || j == TAM_HABILIDADE / 2) ? 1 : 0;
        }
    }
}

void criarOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = (abs(i - centro) + abs(j - centro) <= centro) ? 1 : 0;
        }
    }
}

void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemLinha, int origemColuna) {
    int offset = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int x = origemLinha + (i - offset);
                int y = origemColuna + (j - offset);
                if (x >= 0 && x < TAMANHO && y >= 0 && y < TAMANHO && tabuleiro[x][y] != 3) {
                    tabuleiro[x][y] = 5;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    int habilidade[TAM_HABILIDADE][TAM_HABILIDADE];

    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);

    criarCone(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 2, 4);

    criarCruz(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 6, 6);

    criarOctaedro(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 4, 2);

    imprimirTabuleiro(tabuleiro);

    return 0;
}
