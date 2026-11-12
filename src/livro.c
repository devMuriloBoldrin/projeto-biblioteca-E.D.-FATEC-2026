#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>  
#include "../include/livro.h"

int ler_texto(char *campo, int tam) {
    if (fgets(campo, tam, stdin) == NULL) {
        return 0;
    }

    size_t len = strlen(campo);
    if (len > 0 && campo[len - 1] == '\n') {
        campo[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }

    int tem_letra = 0;
    for (int i = 0; campo[i] != '\0'; i++) {
        if (!isspace((unsigned char)campo[i])) {
            tem_letra = 1;
            break;
        }
    }
    return tem_letra;
}

int ler_inteiro(int *num) {
    char linha[80];
    if (fgets(linha, sizeof(linha), stdin) == NULL) {
        return 0;
    }

    size_t len = strlen(linha);
    if (len > 0 && linha[len - 1] == '\n') {
        linha[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }

    char *sobra;
    long valor = strtol(linha, &sobra, 10);
    if (sobra == linha) {
        return 0;
    }
    *num = (int)valor;
    return 1;
}