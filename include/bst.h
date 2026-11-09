#ifndef BST_H
#define BST_H

#include "livro.h"

struct no_bst {
    Livro dados;
    struct no_bst *esq;
    struct no_bst *dir;
};

typedef struct {
    struct no_bst *raiz;
    int qtd;
} BST;

BST* criar_bst();
int inserir_bst(BST *arv, Livro l);
struct no_bst* buscar_bst(BST *arv, int id);
int remover_bst(BST *arv, int id);
void listar_em_ordem(BST *arv);
int menor_id(BST *arv, int *id);
int maior_id(BST *arv, int *id);
void copiar_para_array(struct no_bst *raiz, Livro *vet, int *pos);
void liberar_bst(BST *arv);

#endif