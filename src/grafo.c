#include <stdio.h>
#include <stdlib.h>
#include "../include/grafo.h"
#include "../include/fila.h"
#include "../include/lista.h"

Grafo* criar_grafo() {
    Grafo *g = (Grafo*) malloc(sizeof(Grafo));
    if (g) {
        g->qtd_vertices = 0;
        for (int i = 0; i < MAX_VERTICES; i++) {
            g->ids[i] = -1;
            for (int j = 0; j < MAX_VERTICES; j++) {
                g->matriz[i][j] = 0;
            }
        }
    }
    return g;
}

int buscar_indice(Grafo *g, int id) {
    if (!g) return -1;
    for (int i = 0; i < g->qtd_vertices; i++) {
        if (g->ids[i] == id) return i;
    }
    return -1;
}

int inserir_vertice(Grafo *g, int id) {
    if (!g || g->qtd_vertices >= MAX_VERTICES) return 0;
    if (buscar_indice(g, id) != -1) return 0;

    int idx = g->qtd_vertices;
    g->ids[idx] = id;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->matriz[idx][i] = 0;
        g->matriz[i][idx] = 0;
    }
    g->qtd_vertices++;
    return 1;
}

int remover_vertice(Grafo *g, int id) {
    if (!g) return 0;
    int idx = buscar_indice(g, id);
    if (idx == -1) return 0;

    for (int i = idx; i < g->qtd_vertices - 1; i++) {
        g->ids[i] = g->ids[i + 1];
    }

    for (int i = idx; i < g->qtd_vertices - 1; i++) {
        for (int j = 0; j < g->qtd_vertices; j++) {
            g->matriz[i][j] = g->matriz[i + 1][j];
        }
    }

    for (int j = idx; j < g->qtd_vertices - 1; j++) {
        for (int i = 0; i < g->qtd_vertices; i++) {
            g->matriz[i][j] = g->matriz[i][j + 1];
        }
    }

    g->qtd_vertices--;
    return 1;
}

int ligar_aresta(Grafo *g, int id1, int id2) {
    if (!g || id1 == id2) return 0;
    int u = buscar_indice(g, id1);
    int v = buscar_indice(g, id2);
    if (u == -1 || v == -1) return 0;
    if (g->matriz[u][v] == 1) return 0;

    g->matriz[u][v] = 1;
    g->matriz[v][u] = 1;
    return 1;
}

int desligar_aresta(Grafo *g, int id1, int id2) {
    if (!g) return 0;
    int u = buscar_indice(g, id1);
    int v = buscar_indice(g, id2);
    if (u == -1 || v == -1 || g->matriz[u][v] == 0) return 0;

    g->matriz[u][v] = 0;
    g->matriz[v][u] = 0;
    return 1;
}

int tem_conexao(Grafo *g, int id1, int id2) {
    if (!g) return 0;
    int u = buscar_indice(g, id1);
    int v = buscar_indice(g, id2);
    if (u == -1 || v == -1) return 0;
    return g->matriz[u][v];
}

void executar_bfs(Grafo *g, int id_origem) {
    if (!g) return;
    int inicio_idx = buscar_indice(g, id_origem);
    if (inicio_idx == -1) {
        printf("ID %d nao encontrado.\n", id_origem);
        return;
    }

    int visitados[MAX_VERTICES] = {0};
    Lista *ordem = criar_lista();
    Fila *fila = criar_fila();

    visitados[inicio_idx] = 1;
    enfileirar(fila, inicio_idx);
    inserir_fim(ordem, g->ids[inicio_idx]);

    while (!fila_vazia(fila)) {
        int atual;
        desenfileirar(fila, &atual);

        int vizinhos[MAX_VERTICES];
        int tot = 0;
        for (int i = 0; i < g->qtd_vertices; i++) {
            if (g->matriz[atual][i] == 1 && !visitados[i]) {
                vizinhos[tot++] = i;
            }
        }

        // Ordena vizinhos por ID
        for (int i = 0; i < tot - 1; i++) {
            for (int j = 0; j < tot - i - 1; j++) {
                if (g->ids[vizinhos[j]] > g->ids[vizinhos[j + 1]]) {
                    int aux = vizinhos[j];
                    vizinhos[j] = vizinhos[j + 1];
                    vizinhos[j + 1] = aux;
                }
            }
        }

        for (int i = 0; i < tot; i++) {
            int v = vizinhos[i];
            visitados[v] = 1;
            enfileirar(fila, v);
            inserir_fim(ordem, g->ids[v]);
        }
    }

    printf("Busca em Largura (BFS) a partir de %d:\n", id_origem);
    imprimir_lista(ordem);

    liberar_fila(fila);
    liberar_lista(ordem);
}

int tem_caminho(Grafo *g, int id_origem, int id_destino) {
    if (!g) return 0;
    int u = buscar_indice(g, id_origem);
    int dest = buscar_indice(g, id_destino);
    if (u == -1 || dest == -1) return -1;
    if (u == dest) return 1;

    int visitados[MAX_VERTICES] = {0};
    Fila *fila = criar_fila();

    visitados[u] = 1;
    enfileirar(fila, u);

    int achou = 0;
    while (!fila_vazia(fila)) {
        int atual;
        desenfileirar(fila, &atual);
        if (atual == dest) {
            achou = 1;
            break;
        }
        for (int v = 0; v < g->qtd_vertices; v++) {
            if (g->matriz[atual][v] == 1 && !visitados[v]) {
                visitados[v] = 1;
                enfileirar(fila, v);
            }
        }
    }

    liberar_fila(fila);
    return achou;
}

void liberar_grafo(Grafo *g) {
    if (g) free(g);
}