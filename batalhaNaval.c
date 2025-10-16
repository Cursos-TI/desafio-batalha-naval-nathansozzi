#include <stdio.h>

// ==================
// CONSTANTES DO JOGO
// ==================
#define tamanhoTabuleiro 10
#define tamanhoNavio 3
#define agua 0
#define navio 3

int main() {

    // ======================
    // DECLARANDO O TABULEIRO
    // ======================
    int tabuleiro[tamanhoTabuleiro][tamanhoTabuleiro];

    // inicializando o tabuleiro com água
    for (int linha = 0; linha < tamanhoTabuleiro; linha++) {
        for (int coluna = 0; coluna < tamanhoTabuleiro; coluna++) {
            tabuleiro[linha][coluna] = agua;
        }
    }

    // ========================
    // CONFIGURAÇÕES DOS NAVIOS
    // ========================
    int navioVertical[tamanhoNavio] = {navio, navio, navio};
    int navioHorizontal[tamanhoNavio] = {navio, navio, navio};

    // ============================
    // POSIÇÕES INICIAIS DOS NAVIOS
    // ============================
    int linhaHorizontalInicio = 2;
    int colunaHorizontalInicio = 1;

    int linhaVerticalInicio = 5;
    int colunaVerticalInicio = 6;

    // ============================================================
    // VALIDAÇÃO BÁSICA SE OS NAVIOS ESTÃO NOS LIMITES DO TABULEIRO
    // ============================================================
    if (colunaHorizontalInicio + tamanhoNavio > tamanhoTabuleiro) {
        printf("Erro: O navio horizontal não cabe no tabuleiro na posição inicial especificada.\n");
        return 1;
    }

    if (linhaVerticalInicio + tamanhoNavio > tamanhoTabuleiro) {
        printf("Erro: O navio vertical não cabe no tabuleiro na posição inicial especificada.\n");
        return 1;
    }

    // ================================
    // COLOCANDO OS NAVIOS NO TABULEIRO
    // ================================
    // Colocando o navio horizontal
    for (int i = 0; i < tamanhoNavio; i++) {
        int linha = linhaHorizontalInicio;
        int coluna = colunaHorizontalInicio + i;

        if (tabuleiro[linha][coluna] == navio) {
            printf("Erro: Sobreposição de navios na posição (%d, %d).\n", linha, coluna);
            return 1;
        }

        tabuleiro[linha][coluna] = navioHorizontal[i];
    }

    // Colocando o navio vertical
    for (int i = 0; i < tamanhoNavio; i++) {
        int linha = linhaVerticalInicio + i;
        int coluna = colunaVerticalInicio;

        if (tabuleiro[linha][coluna] == navio) {
            printf("Erro: Sobreposição de navios na posição (%d, %d).\n", linha, coluna);
            return 1;
        }

        tabuleiro[linha][coluna] = navioVertical[i];
    }

    // =====================
    // EXIBIÇÃO DO TABULEIRO
    // =====================
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");

    for (int linha = 0; linha < tamanhoTabuleiro; linha++) {
        for (int coluna = 0; coluna < tamanhoTabuleiro; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }

    printf("\nLegenda: 0 = Água | 3 = Navio\n");

    return 0;
}