#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define LINHAS 10
#define COLUNAS 10
#define TAMANHO_NAVIO 3
#define TAM_HABILIDADE 5 // Tamanho das matrizes de habilidade

void MostrarTabuleiro(char *TABULEIRO[LINHAS][COLUNAS]) {   
    // Cabeçalho das colunas
    printf("   ");
    for(int j = 1; j < COLUNAS; j++) {
        printf("%s ", TABULEIRO[0][j]);
    }
    printf("\n");
    
    // Corpo do tabuleiro
    for(int i = 1; i < LINHAS; i++) {
        printf("%s ", TABULEIRO[i][0]); // Número da linha
        for(int j = 1; j < COLUNAS; j++) {
            printf("%s ", TABULEIRO[i][j]);
        }
        printf("\n");
    }
}

// Função para criar matriz de habilidade em cone
void CriarCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for(int i = 0; i < TAM_HABILIDADE; i++) {
        for(int j = 0; j < TAM_HABILIDADE; j++) {
            if(i == 0 && j == TAM_HABILIDADE/2) {
                matriz[i][j] = 3; // Topo do cone
            }
            else if(i == 1 && (j >= TAM_HABILIDADE/2-1 && j <= TAM_HABILIDADE/2+1)) {
                matriz[i][j] = 3; // Parte média
            }
            else if(i == 2) {
                matriz[i][j] = 3; // Base do cone
            }
            else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Função para criar matriz de habilidade em cruz
void CriarCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for(int i = 0; i < TAM_HABILIDADE; i++) {
        for(int j = 0; j < TAM_HABILIDADE; j++) {
            if(i == TAM_HABILIDADE/2 || j == TAM_HABILIDADE/2) {
                matriz[i][j] = 3; // Linha ou coluna central
            }
            else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Função para criar matriz de habilidade em octaedro
void CriarOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    
    for(int i = 0; i < TAM_HABILIDADE; i++) {
        for(int j = 0; j < TAM_HABILIDADE; j++) {
            // Verifica se a soma das distâncias ao centro é <= centro
            if((i <= centro && j >= centro - i && j <= centro + i) ||
               (i > centro && j >= i - centro && j <= 3*centro - i)) {
                matriz[i][j] = 3;
            }
            else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Função para aplicar habilidade ao tabuleiro
void AplicarHabilidade(char *TABULEIRO[LINHAS][COLUNAS], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int linha_centro, int coluna_centro) {
    int offset = TAM_HABILIDADE/2;
    
    for(int i = 0; i < TAM_HABILIDADE; i++) {
        for(int j = 0; j < TAM_HABILIDADE; j++) {
            int linha = linha_centro - offset + i;
            int coluna = coluna_centro - offset + j;
            
            // Verifica se está dentro dos limites do tabuleiro
            if(linha >= 1 && linha < LINHAS && coluna >= 1 && coluna < COLUNAS) {
                if(habilidade[i][j] == 3) {
                    TABULEIRO[linha][coluna] = "1"; // Marca área afetada
                }
            }
        }
    }
}

int main() {
    int linha, coluna;
    char coluna_char;
    
    // Tabuleiro 10x10 (linha 0 e coluna 0 para coordenadas)
    char *TABULEIRO[LINHAS][COLUNAS] = {
        {" -","B","C","D","E","F","G","H","I","J"},  // Linha 0 (cabeçalho)
        {" 1","0","0","0","0","0","0","0","0","0"},  // Linha 1
        {" 2","0","0","0","0","0","0","0","0","0"},  // Linha 2
        {" 3","0","0","0","0","0","0","0","0","0"},  // Linha 3
        {" 4","0","0","0","0","0","0","0","0","0"},  // Linha 4
        {" 5","0","0","0","0","0","0","0","0","0"},  // Linha 5
        {" 6","0","0","0","0","0","0","0","0","0"},  // Linha 6
        {" 7","0","0","0","0","0","0","0","0","0"},  // Linha 7
        {" 8","0","0","0","0","0","0","0","0","0"},  // Linha 8
        {" 9","0","0","0","0","0","0","0","0","0"}   // Linha 9
    };
    // Vetores para representar os navios
    char navioHorizontal[TAMANHO_NAVIO] = {'3', '3', '3'};
    char navioVertical[TAMANHO_NAVIO] = {'3', '3', '3'};
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];
        
    CriarCone(cone);
    CriarCruz(cruz);
    CriarOctaedro(octaedro);

    // Mostra tabuleiro inicial
    printf("Tabuleiro Inicial:\n");
    MostrarTabuleiro(TABULEIRO);
    
    // Posicionando o navio horizontal
    printf("\nPosicionando o navio HORIZONTAL (tamanho %d):\n", TAMANHO_NAVIO);
    
    printf("Digite a linha (1 a 9): ");
    scanf("%d", &linha);
    
    printf("Digite a coluna (B a H): ");
    scanf(" %c", &coluna_char);
    coluna_char = toupper(coluna_char);
    coluna = coluna_char - 'B' + 1; // Converte para índice (1-8)

    // Verificação de posição válida
    if(coluna + TAMANHO_NAVIO - 1 >= COLUNAS) {
        printf("Erro: Navio não cabe nessa posição!\n");
        return 1;
    }

    // Verificação de sobreposição
    for(int i = 0; i < TAMANHO_NAVIO; i++) {
        if(strcmp(TABULEIRO[linha][coluna+i], "0") != 0) {
            printf("Erro: Posição (%d,%c) já ocupada!\n", 
                   linha, 'B' + coluna + i - 1);
            return 1;
        }
    }

    // Posiciona navio horizontal (usando o vetor)
    for(int i = 0; i < TAMANHO_NAVIO; i++) {
        TABULEIRO[linha][coluna+i] = "3";
    }

    printf("\nTabuleiro com navio horizontal:\n");
    MostrarTabuleiro(TABULEIRO);

    // Posicionando o navio vertical
    printf("\nPosicionando o navio VERTICAL (tamanho %d):\n", TAMANHO_NAVIO);
    
    printf("Digite a linha (1 a 8): ");
    scanf("%d", &linha);
    
    printf("Digite a coluna (B a J): ");
    scanf(" %c", &coluna_char);
    coluna_char = toupper(coluna_char);
    coluna = coluna_char - 'B' + 1;

    // Verificação de posição válida
    if(linha + TAMANHO_NAVIO - 1 >= LINHAS) {
        printf("Erro: Navio não cabe nessa posição!\n");
        return 1;
    }

    // Verificação de sobreposição
    for(int i = 0; i < TAMANHO_NAVIO; i++) {
        if(strcmp(TABULEIRO[linha+i][coluna], "0") != 0) {
            printf("Erro: Posição (%d,%c) já ocupada!\n", 
                   linha+i, coluna_char);
            return 1;
        }
    }

    // Posiciona navio vertical (usando o vetor)
    for(int i = 0; i < TAMANHO_NAVIO; i++) {
        TABULEIRO[linha+i][coluna] = "3";
    }
    
    printf("\nTabuleiro com navio vertical:\n");
    MostrarTabuleiro(TABULEIRO);

    // Posicionando o terceiro navio (diagonal)
    printf("\nPosicionando o TERCEIRO navio (DIAGONAL - tamanho 3):\n");
    
    printf("Digite a linha (1 a 8): ");
    scanf("%d", &linha);
    
    printf("Digite a coluna (B a H): ");
    scanf(" %c", &coluna_char);
    coluna_char = toupper(coluna_char);
    coluna = coluna_char - 'B' + 1;

    // Verificação de posição válida    
    if(linha + 2 >= LINHAS || coluna + 2 >= COLUNAS) {
        printf("Erro: Navio não cabe nessa posição diagonal!\n");
        return 1;
    }

    // Verificação de sobreposição
    for(int i = 0; i < 3; i++) {
        if(strcmp(TABULEIRO[linha+i][coluna+i], "3") == 0) {
            printf("Erro: Navio sobrepondo outro navio em (%d,%c)!\n", 
                   linha+i, coluna_char+i);
            return 1;
        }
    }

    // Posiciona terceiro navio diagonal baixo
    for(int i = 0; i < 3; i++) {
        TABULEIRO[linha+i][coluna+i] = "3";
    }     
    
    printf("\nTabuleiro com terceiro navio (diagonal):\n");
    MostrarTabuleiro(TABULEIRO);

    // Posicionando o Quarto navio (diagonal cima)
    printf("\nPosicionando o Quarto navio (DIAGONAL - tamanho 3):\n");
    
    printf("Digite a linha (1 a 8): ");
    scanf("%d", &linha);
    
    printf("Digite a coluna (B a H): ");
    scanf(" %c", &coluna_char);
    coluna_char = toupper(coluna_char);
    coluna = coluna_char - 'B' + 1;

    // Verificação de posição válida    
    if(linha - 2 >= LINHAS || coluna + 2 >= COLUNAS) {
        printf("Erro: Navio não cabe nessa posição diagonal!\n");
        return 1;
    }

    // Verificação de sobreposição
    for(int i = 0; i < 3; i++) {
        if(strcmp(TABULEIRO[linha-i][coluna+i], "3") == 0) {
            printf("Erro: Navio sobrepondo outro navio em (%d,%c)!\n", 
                   linha-i, coluna_char-i);
            return 1;
        }
    }

    // Posiciona Quarto navio diagonal cima
    for(int i = 0; i < 3; i++) {
        TABULEIRO[linha-i][coluna+i] = "3";
    }

    printf("\nTabuleiro com Quarto navio (diagonal):\n");
    MostrarTabuleiro(TABULEIRO);

    //aplicação das habilidades
    printf("\nAplicando habilidade CONE no centro do tabuleiro (linha 5, coluna F):\n");
    AplicarHabilidade(TABULEIRO, cone, 5, 5);
    MostrarTabuleiro(TABULEIRO);

    printf("\nAplicando habilidade CRUZ em (linha 3, coluna J):\n");
    AplicarHabilidade(TABULEIRO, cruz, 3, 3);
    MostrarTabuleiro(TABULEIRO);

    printf("\nAplicando habilidade OCTAEDRO em (linha 7, coluna H):\n");
    AplicarHabilidade(TABULEIRO, octaedro, 7, 7);
    MostrarTabuleiro(TABULEIRO);


    return 0;
}