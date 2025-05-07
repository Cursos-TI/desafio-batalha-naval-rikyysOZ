#include <stdio.h>
#include <ctype.h>

void MostrarTabuleiro(char *TABULEIRO[11][11]) {   
    for(int i = 0; i < 11; i++) {
        for(int j = 0; j < 11; j++) {
            printf("%s ", TABULEIRO[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int linha, coluna;
    char coluna_char;
    
    // Tabuleiro 11x11 
    char *TABULEIRO[11][11] = {
        {" -","A","B","C","D","E","F","G","H","I","J"},
        {" 1","0","0","0","0","0","0","0","0","0","0"},
        {" 2","0","0","0","0","0","0","0","0","0","0"},
        {" 3","0","0","0","0","0","0","0","0","0","0"},
        {" 4","0","0","0","0","0","0","0","0","0","0"},
        {" 5","0","0","0","0","0","0","0","0","0","0"},
        {" 6","0","0","0","0","0","0","0","0","0","0"},
        {" 7","0","0","0","0","0","0","0","0","0","0"},
        {" 8","0","0","0","0","0","0","0","0","0","0"},
        {" 9","0","0","0","0","0","0","0","0","0","0"},
        {"10","0","0","0","0","0","0","0","0","0","0"}
    };

    // Mostra tabuleiro inicial
    MostrarTabuleiro(TABULEIRO);
    
    // Posicionando o primeiro navio (horizontal)
    printf("\nPosicionando o PRIMEIRO navio (HORIZONTAL - tamanho 3):\n");
    
    printf("Digite a linha (1 a 10): ");
    scanf("%d", &linha);
    
    printf("Digite a coluna (A a J): ");
    scanf(" %c", &coluna_char);
    coluna_char = toupper(coluna_char);
    coluna = coluna_char - 'A' + 1;

    // Verificação de posição válida
    if(coluna + 2 > 10) {
        printf("Erro: Navio não cabe nessa posição!\n");
        return 1;
    }

    // Posiciona navio
    for(int i = 0; i < 3; i++) {
        TABULEIRO[linha][coluna+i] = "3";
    }

    // Mostra tabuleiro após primeiro navio
    MostrarTabuleiro(TABULEIRO);

    // Posicionando o segundo navio (vertical)
    printf("\nPosicionando o SEGUNDO navio (VERTICAL - tamanho 3):\n");
    
    printf("Digite a linha (1 a 10): ");
    scanf("%d", &linha);
    
    printf("Digite a coluna (A a J): ");
    scanf(" %c", &coluna_char);
    coluna_char = toupper(coluna_char);
    coluna = coluna_char - 'A' + 1;

    // Verificação de posição válida
    if(linha + 2 > 10) {
        printf("Erro: Navio não cabe nessa posição!\n");
        return 1;
    }

    // Verificação de sobreposição
    for(int i = 0; i < 3; i++) {
        if(TABULEIRO[linha+i][coluna] == "3") {
            printf("Erro: Navio sobrepondo outro navio!\n");
            return 1;
        }
    }

    // Posiciona segundo navio
    for(int i = 0; i < 3; i++) {
        TABULEIRO[linha+i][coluna] = "3"; 
    }

    // Mostra tabuleiro final
    MostrarTabuleiro(TABULEIRO);

    return 0;
}