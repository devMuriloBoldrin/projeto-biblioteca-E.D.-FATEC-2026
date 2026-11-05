#ifndef LISTA_H
#define LISTA_H

struct no_lista {
    int id;
    struct no_lista *prox;
};

typedef struct {
    struct no_lista *inicio;
    struct no_lista *fim;
} Lista;

Lista* criar_lista();
int inserir_fim(Lista *l, int id);
void imprimir_lista(Lista *l);
void liberar_lista(Lista *l);

#endif