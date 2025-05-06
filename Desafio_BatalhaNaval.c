#include <stdio.h>
 
int main() {
    int index;
    
     // Tabuleiro 11x11 (incluindo bordas com letras e números)
     char *TABULEIRO[11][11] = {
        {"-","A","B","C","D","E","F","G","H","I","J"},  // Linha 0 (cabeçalho)
        {"1","0","0","0","0","0","0","0","0","0","0"},  // Linha 1
        {"2","0","0","0","0","0","0","0","0","0","0"},  // Linha 2
        {"3","0","0","0","0","0","0","0","0","0","0"},  // Linha 3
        {"4","0","0","0","0","0","0","0","0","0","0"},  // Linha 4
        {"5","0","0","0","0","0","0","0","0","0","0"},  // Linha 5
        {"6","0","0","0","0","0","0","0","0","0","0"},  // Linha 6
        {"7","0","0","0","0","0","0","0","0","0","0"},  // Linha 7
        {"8","0","0","0","0","0","0","0","0","0","0"},  // Linha 8
        {"9","0","0","0","0","0","0","0","0","0","0"},  // Linha 9
        {"10","0","0","0","0","0","0","0","0","0","0"}  // Linha 10
    };
    
    // Imprimindo o tabuleiro
    for(int i = 0; i < 11; i++) {
        for(int j = 0; j < 11; j++) {
            printf("%s ", TABULEIRO[i][j]);  // Apenas [i][j] para acessar cada elemento
        }
        printf("\n");  // Nova linha após cada linha do tabuleiro
    }
    
    return 0;
}