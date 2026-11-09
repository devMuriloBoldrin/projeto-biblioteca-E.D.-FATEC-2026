#include <stdio.h>
#include <stdlib.h>
#include "../include/bst.h"

BST* criar_bst() {
    BST *arv = (BST*) malloc(sizeof(BST));
    if (arv) {
        arv->raiz = NULL;
        arv->qtd = 0;
    }
    return arv;
}

static struct no_bst* inserir_no(struct no_bst *raiz, Livro l, int *ok) {
    if (!raiz) {
        struct no_bst *novo = (struct no_bst*) malloc(sizeof(struct no_bst));
        if (!novo) {
            *ok = 0;
            return NULL;
        }
        novo->dados = l;
        novo->esq = NULL;
        novo->dir = NULL;
        *ok = 1;
        return novo;
    }

    if (l.id < raiz->dados.id) {
        raiz->esq = inserir_no(raiz->esq, l, ok);
    } else if (l.id > raiz->dados.id) {
        raiz->dir = inserir_no(raiz->dir, l, ok);
    } else {
        *ok = 0;
    }
    return raiz;
}

int inserir_bst(BST *arv, Livro l) {
    if (!arv) return 0;
    int ok = 0;
    arv->raiz = inserir_no(arv->raiz, l, &ok);
    if (ok) {
        arv->qtd++;
    }
    return ok;
}

static struct no_bst* buscar_no(struct no_bst *raiz, int id) {
    if (!raiz || raiz->dados.id == id) return raiz;
    if (id < raiz->dados.id) return buscar_no(raiz->esq, id);
    return buscar_no(raiz->dir, id);
}

struct no_bst* buscar_bst(BST *arv, int id) {
    if (!arv) return NULL;
    return buscar_no(arv->raiz, id);
}

static struct no_bst* pegar_menor(struct no_bst *raiz) {
    struct no_bst *atual = raiz;
    while (atual && atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

static struct no_bst* remover_no(struct no_bst *raiz, int id, int *ok) {
    if (!raiz) {
        *ok = 0;
        return NULL;
    }

    if (id < raiz->dados.id) {
        raiz->esq = remover_no(raiz->esq, id, ok);
    } else if (id > raiz->dados.id) {
        raiz->dir = remover_no(raiz->dir, id, ok);
    } else {
        *ok = 1;

        if (raiz->esq == NULL) {
            struct no_bst *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            struct no_bst *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        struct no_bst *sucessor = pegar_menor(raiz->dir);
        raiz->dados = sucessor->dados;
        int status_aux = 0;
        raiz->dir = remover_no(raiz->dir, sucessor->dados.id, &status_aux);
    }
    return raiz;
}

int remover_bst(BST *arv, int id) {
    if (!arv || !arv->raiz) return 0;
    int ok = 0;
    arv->raiz = remover_no(arv->raiz, id, &ok);
    if (ok) {
        arv->qtd--;
    }
    return ok;
}

static void imprimir_em_ordem(struct no_bst *raiz) {
    if (raiz != NULL) {
        imprimir_em_ordem(raiz->esq);
        printf("[%d] \"%s\" - %s (%d)\n", raiz->dados.id, raiz->dados.titulo, raiz->dados.autor, raiz->dados.ano);
        imprimir_em_ordem(raiz->dir);
    }
}

void listar_em_ordem(BST *arv) {
    if (!arv || !arv->raiz) {
        printf("Arvore vazia.\n");
        return;
    }
    imprimir_em_ordem(arv->raiz);
}

int menor_id(BST *arv, int *id) {
    if (!arv || !arv->raiz) return 0;
    struct no_bst *atual = arv->raiz;
    while (atual->esq != NULL) atual = atual->esq;
    *id = atual->dados.id;
    return 1;
}

int maior_id(BST *arv, int *id) {
    if (!arv || !arv->raiz) return 0;
    struct no_bst *atual = arv->raiz;
    while (atual->dir != NULL) atual = atual->dir;
    *id = atual->dados.id;
    return 1;
}

void copiar_para_array(struct no_bst *raiz, Livro *vet, int *pos) {
    if (raiz != NULL) {
        copiar_para_array(raiz->esq, vet, pos);
        vet[*pos] = raiz->dados;
        (*pos)++;
        copiar_para_array(raiz->dir, vet, pos);
    }
}

static void liberar_nos(struct no_bst *raiz) {
    if (raiz != NULL) {
        liberar_nos(raiz->esq);
        liberar_nos(raiz->dir);
        free(raiz);
    }
}

void liberar_bst(BST *arv) {
    if (!arv) return;
    liberar_nos(arv->raiz);
    free(arv);
}