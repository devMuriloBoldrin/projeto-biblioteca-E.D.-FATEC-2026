#ifndef GRAFO_H
#define GRAFO_H

#define MAX_VERTICES 100

typedef struct {
    int ids[MAX_VERTICES];
    int matriz[MAX_VERTICES][MAX_VERTICES];
    int qtd_vertices;
} Grafo;

Grafo* criar_grafo();
int buscar_indice(Grafo *g, int id);
int inserir_vertice(Grafo *g, int id);
int remover_vertice(Grafo *g, int id);
int ligar_aresta(Grafo *g, int id1, int id2);
int desligar_aresta(Grafo *g, int id1, int id2);
int tem_conexao(Grafo *g, int id1, int id2);
void executar_bfs(Grafo *g, int id_origem);
int tem_caminho(Grafo *g, int id_origem, int id_destino);
void liberar_grafo(Grafo *g);

#endif