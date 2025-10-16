#include <stdio.h>

// ==================
// CONSTANTES DO JOGO
// ==================
#define TAMANHO_TABULEIRO 10       // Dimensão do tabuleiro: 10x10
#define TAMANHO_NAVIO 3            // Tamanho padrão dos navios
#define AGUA 0                     // Valor que representa água
#define NAVIO 3                    // Valor que representa parte de um navio
#define TAMANHO_MATRIZ_ATAQUE 5    // Dimensão das matrizes de ataque (5x5)
#define EFEITO_ATAQUE 5            // Valor que representa área afetada pelo ataque

// ====================================
// FUNÇÃO RECURSIVA PARA APLICAR ATAQUE
// ====================================
void aplicarAtaque(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                   int origemLinha, int origemColuna, 
                   int ataqueMatriz[TAMANHO_MATRIZ_ATAQUE][TAMANHO_MATRIZ_ATAQUE], 
                   int iAtual, int jAtual) 
{
    // Caso base: terminou de percorrer toda a matriz de ataque
    if (iAtual >= TAMANHO_MATRIZ_ATAQUE) return;
    if (jAtual >= TAMANHO_MATRIZ_ATAQUE) return;

    // Calcula a posição correspondente no tabuleiro
    int linhaTabuleiro = origemLinha - TAMANHO_MATRIZ_ATAQUE / 2 + iAtual;
    int colunaTabuleiro = origemColuna - TAMANHO_MATRIZ_ATAQUE / 2 + jAtual;

    // Verifica se a posição está dentro dos limites do tabuleiro
    if (linhaTabuleiro >= 0 && linhaTabuleiro < TAMANHO_TABULEIRO &&
        colunaTabuleiro >= 0 && colunaTabuleiro < TAMANHO_TABULEIRO) 
    {
        // Só marca se a posição da matriz de ataque for 1 e houver água
        if (ataqueMatriz[iAtual][jAtual] == 1 && tabuleiro[linhaTabuleiro][colunaTabuleiro] == AGUA) {
            tabuleiro[linhaTabuleiro][colunaTabuleiro] = EFEITO_ATAQUE;
        }
    }

    // Chamada recursiva para a próxima coluna da mesma linha
    if (jAtual + 1 < TAMANHO_MATRIZ_ATAQUE) {
        aplicarAtaque(tabuleiro, origemLinha, origemColuna, ataqueMatriz, iAtual, jAtual + 1);
    } else {
        // Quando termina a linha, passa para a próxima linha e reinicia coluna
        aplicarAtaque(tabuleiro, origemLinha, origemColuna, ataqueMatriz, iAtual + 1, 0);
    }
}

// =======================================================
// FUNÇÃO RECURSIVA PARA COLOCAR NAVIOS E VALIDAR POSIÇÕES
// =======================================================
int colocarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaInicio, int colunaInicio, int deltaLinha, int deltaColuna) {
    // Valida se cabem dentro do tabuleiro e não há sobreposição
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linhaInicio + i*deltaLinha;
        int c = colunaInicio + i*deltaColuna;
        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO) return 0;
        if (tabuleiro[l][c] != AGUA) return 0;
    }
    // Coloca navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linhaInicio + i*deltaLinha;
        int c = colunaInicio + i*deltaColuna;
        tabuleiro[l][c] = NAVIO;
    }
    return 1;
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
            tabuleiro[i][j] = AGUA;

    // ==================================
    // COLOCAÇÃO DOS NAVIOS COM VALIDAÇÃO
    // ==================================
    
    if (!colocarNavio(tabuleiro, 2, 1, 0, 1)) { printf("Erro: navio horizontal inválido!\n"); return 1; }
    if (!colocarNavio(tabuleiro, 5, 6, 1, 0)) { printf("Erro: navio vertical inválido!\n"); return 1; }
    if (!colocarNavio(tabuleiro, 1, 8, 1, -1)) { printf("Erro: navio diagonal direita inválido!\n"); return 1; }
    if (!colocarNavio(tabuleiro, 5, 1, 1, 1)) { printf("Erro: navio diagonal esquerda inválido!\n"); return 1; }

    // ==================
    // MATRIZES DE ATAQUE
    // ==================
    int cone[5][5] = {
        {0,0,1,0,0},
        {0,1,1,1,0},
        {1,1,1,1,1},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };
    int cruz[5][5] = {
        {0,0,1,0,0},
        {0,0,1,0,0},
        {1,1,1,1,1},
        {0,0,1,0,0},
        {0,0,1,0,0}
    };
    int octaedro[5][5] = {
        {0,0,1,0,0},
        {0,1,1,1,0},
        {1,1,1,1,1},
        {0,1,1,1,0},
        {0,0,1,0,0}
    };

    // ====================
    // EXECUÇÃO DOS ATAQUES
    // ====================
    // Cada chamada aplica a matriz de ataque ao tabuleiro, centrando no ponto definido (os dois números após "tabuleiro")
    aplicarAtaque(tabuleiro, 2, 2, cone, 0, 0);
    aplicarAtaque(tabuleiro, 2, 7, cruz, 0, 0);
    aplicarAtaque(tabuleiro, 7, 4, octaedro, 0, 0);

    // ======================
    // IMPRESSÃO DO TABULEIRO
    // ======================
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\nLegenda: 0 = Água | 3 = Navio | 5 = Área de Ataque\n");

    return 0;
}