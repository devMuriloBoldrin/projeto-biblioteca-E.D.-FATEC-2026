#include <string.h>
#include "../include/ordenacao.h"

void ordenar_por_titulo(Livro *vet, int n) {
    for (int i = 1; i < n; i++) {
        Livro chave = vet[i];
        int j = i - 1;

        while (j >= 0 && (strcmp(vet[j].titulo, chave.titulo) > 0 || 
               (strcmp(vet[j].titulo, chave.titulo) == 0 && vet[j].id > chave.id))) {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = chave;
    }
}