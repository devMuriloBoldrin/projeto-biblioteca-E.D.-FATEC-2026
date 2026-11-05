#ifndef FILA_H
#define FILA_H

struct no_fila {
    int id;
    struct no_fila *prox;
};

typedef struct {
    struct no_fila *inicio;
    struct no_fila *fim;
} Fila;

Fila* criar_fila();
int enfileirar(Fila *f, int id);
int desenfileirar(Fila *f, int *id);
int fila_vazia(Fila *f);
void liberar_fila(Fila *f);

#endif