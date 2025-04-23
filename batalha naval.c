#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define AREA_HABILIDADE 5

// Função para imprimir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
        printf("%d ", i);  // cabeçalho de colunas
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);  // índice da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 5)
                printf("X "); // Marcando área de habilidade
            else
                printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para criar a área de efeito Cone
void criarCone(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < 5; i++) {
        for (int j = coluna - i; j <= coluna + i; j++) {
            if (linha + i < TAMANHO_TABULEIRO && j >= 0 && j < TAMANHO_TABULEIRO) {
                tabuleiro[linha + i][j] = AREA_HABILIDADE;
            }
        }
    }
}

// Função para criar a área de efeito Cruz
void criarCruz(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < 5; i++) {
        if (linha + i < TAMANHO_TABULEIRO) {
            tabuleiro[linha + i][coluna] = AREA_HABILIDADE;  // Vertical
        }
        if (coluna + i < TAMANHO_TABULEIRO) {
            tabuleiro[linha][coluna + i] = AREA_HABILIDADE;  // Horizontal
        }
    }
}

// Função para criar a área de efeito Octaedro
void criarOctaedro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < 5; i++) {
        for (int j = coluna - i; j <= coluna + i; j++) {
            if (linha + i < TAMANHO_TABULEIRO && j >= 0 && j < TAMANHO_TABULEIRO) {
                tabuleiro[linha + i][j] = AREA_HABILIDADE;
                if (i != 0 && linha - i >= 0) {
                    tabuleiro[linha - i][j] = AREA_HABILIDADE;
                }
            }
        }
    }
}

// Função para posicionar um navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int horizontal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + (horizontal ? 0 : i);
        int c = coluna + (horizontal ? i : 0);
        tabuleiro[l][c] = NAVIO;
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro com água
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
            tabuleiro[i][j] = AGUA;

    // Posiciona os navios
    posicionarNavio(tabuleiro, 2, 4, 1);  // Navio horizontal
    posicionarNavio(tabuleiro, 5, 7, 0);  // Navio vertical
    posicionarNavio(tabuleiro, 7, 1, 1);  // Navio horizontal
    posicionarNavio(tabuleiro, 0, 5, 0);  // Navio vertical

    // Define as posições de origem das habilidades e as cria no tabuleiro
    criarCone(tabuleiro, 1, 1);  // Habilidade Cone
    criarCruz(tabuleiro, 5, 5);  // Habilidade Cruz
    criarOctaedro(tabuleiro, 3, 3);  // Habilidade Octaedro

    // Exibe o tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}
