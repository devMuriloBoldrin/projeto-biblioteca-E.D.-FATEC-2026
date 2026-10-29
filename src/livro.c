#include <stdio.h>
#include <string.h>
#include "../include/livro.h"

int ler_texto(char *campo, int tam) {
    if (fgets(campo, tam, stdin) != NULL) {
        // Remove a quebra de linha do final, caso tenha
        size_t len = strlen(campo);
        if (len > 0 && campo[len - 1] == '\n') {
            campo[len - 1] = '\0';
        }
        return 1;
    }
    return 0;
}

int ler_inteiro(int *num) {
    if (scanf("%d", num) == 1) {
        // Limpa o '\n' do buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 1;
    }
    
    // Se digitou algo errado, limpa o buffer para não travar o loop
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return 0;
}