#include <stdio.h>
#include <stdlib.h>
#include "../include/lista.h"

Lista* criar_lista() {
    Lista *l = (Lista*) malloc(sizeof(Lista));
    if (l) {
        l->inicio = NULL;
        l->fim = NULL;
    }
    return l;
}

int inserir_fim(Lista *l, int id) {
    if (!l) return 0;
    
    struct no_lista *novo = (struct no_lista*) malloc(sizeof(struct no_lista));
    if (!novo) return 0;

    novo->id = id;
    novo->prox = NULL;

    if (l->inicio == NULL) {
        l->inicio = novo;
        l->fim = novo;
    } else {
        l->fim->prox = novo;
        l->fim = novo;
    }
    return 1;
}

void imprimir_lista(Lista *l) {
    if (!l || !l->inicio) {
        printf("Lista vazia.\n");
        return;
    }
    struct no_lista *atual = l->inicio;
    while (atual != NULL) {
        printf("%d", atual->id);
        if (atual->prox != NULL) {
            printf(" -> ");
        }
        atual = atual->prox;
    }
    printf("\n");
}

void liberar_lista(Lista *l) {
    if (!l) return;
    struct no_lista *atual = l->inicio;
    while (atual != NULL) {
        struct no_lista *aux = atual;
        atual = atual->prox;
        free(aux);
    }
    free(l);
}