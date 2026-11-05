#include <stdio.h>
#include <stdlib.h>
#include "../include/pilha.h"

Pilha* criar_pilha() {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    if (p) {
        p->topo = NULL;
    }
    return p;
}

int push(Pilha *p, RegistroAcao acao) {
    if (!p) return 0;
    
    struct no_pilha *novo = (struct no_pilha*) malloc(sizeof(struct no_pilha));
    if (!novo) return 0;

    novo->acao = acao;
    novo->prox = p->topo;
    p->topo = novo;
    return 1;
}

int pop(Pilha *p, RegistroAcao *acao) {
    if (!p || !p->topo) return 0;
    
    struct no_pilha *aux = p->topo;
    *acao = aux->acao;
    p->topo = p->topo->prox;
    free(aux);
    return 1;
}

int peek(Pilha *p, RegistroAcao *acao) {
    if (!p || !p->topo) return 0;
    *acao = p->topo->acao;
    return 1;
}

void ver_ultimas_cinco(Pilha *p) {
    if (!p || !p->topo) {
        printf("Sem historico de operacoes.\n");
        return;
    }
    
    printf("\nUltimas 5 acoes:\n");
    struct no_pilha *atual = p->topo;
    int cont = 0;
    
    while (atual != NULL && cont < 5) {
        printf("%d) %s -> Livro ID: %d", cont + 1, atual->acao.operacao, atual->acao.id1);
        if (atual->acao.id2 != -1) {
            printf(" com Livro ID: %d", atual->acao.id2);
        }
        printf("\n");
        atual = atual->prox;
        cont++;
    }
}

void liberar_pilha(Pilha *p) {
    if (!p) return;
    RegistroAcao temp;
    while (pop(p, &temp));
    free(p);
}