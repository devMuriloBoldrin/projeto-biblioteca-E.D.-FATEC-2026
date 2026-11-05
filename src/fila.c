#include <stdlib.h>
#include "../include/fila.h"

Fila* criar_fila() {
    Fila *f = (Fila*) malloc(sizeof(Fila));
    if (f) {
        f->inicio = NULL;
        f->fim = NULL;
    }
    return f;
}

int enfileirar(Fila *f, int id) {
    if (!f) return 0;
    
    struct no_fila *novo = (struct no_fila*) malloc(sizeof(struct no_fila));
    if (!novo) return 0;

    novo->id = id;
    novo->prox = NULL;

    if (f->fim == NULL) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
    return 1;
}

int desenfileirar(Fila *f, int *id) {
    if (!f || !f->inicio) return 0;
    
    struct no_fila *aux = f->inicio;
    *id = aux->id;
    f->inicio = f->inicio->prox;
    
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    
    free(aux);
    return 1;
}

int fila_vazia(Fila *f) {
    return (f == NULL || f->inicio == NULL);
}

void liberar_fila(Fila *f) {
    if (!f) return;
    int temp;
    while (desenfileirar(f, &temp));
    free(f);
}