#ifndef PILHA_H
#define PILHA_H

typedef struct {
    char operacao[20];
    int id1;
    int id2;
} RegistroAcao;

struct no_pilha {
    RegistroAcao acao;
    struct no_pilha *prox;
};

typedef struct {
    struct no_pilha *topo;
} Pilha;

Pilha* criar_pilha();
int push(Pilha *p, RegistroAcao acao);
int pop(Pilha *p, RegistroAcao *acao);
int peek(Pilha *p, RegistroAcao *acao);
void ver_ultimas_cinco(Pilha *p);
void liberar_pilha(Pilha *p);

#endif