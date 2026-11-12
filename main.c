#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/livro.h"
#include "include/bst.h"
#include "include/grafo.h"
#include "include/pilha.h"
#include "include/ordenacao.h"

void menu() {
    printf("\n=== SISTEMA DA BIBLIOTECA ===\n");
    printf("1 - Cadastrar livro\n");
    printf("2 - Buscar livro (BST)\n");
    printf("3 - Remover livro\n");
    printf("4 - Listar livros por ID\n");
    printf("5 - Listar livros por titulo\n");
    printf("6 - Adicionar conexao\n");
    printf("7 - Remover conexao\n");
    printf("8 - Consultar conexao direta\n");
    printf("9 - Listar livros alcancaveis (BFS)\n");
    printf("10 - Verificar caminho entre dois livros\n");
    printf("11 - Historico de acoes\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    BST *arvore = criar_bst();
    Grafo *grafo = criar_grafo();
    Pilha *historico = criar_pilha();

    if (!arvore || !grafo || !historico) {
        printf("Erro ao alocar memoria para as estruturas.\n");
        return 1;
    }

    int op;
    do {
        menu();
        if (!ler_inteiro(&op)) {
            printf("Opcao invalida. Digite apenas numeros.\n");
            continue;
        }

        switch (op) {
            case 1: {
                if (grafo->qtd_vertices >= MAX_VERTICES) {
                    printf("Limite de livros atingido (%d).\n", MAX_VERTICES);
                    break;
                }
                Livro l;
                printf("ID do livro: ");
                if (!ler_inteiro(&l.id) || l.id <= 0) {
                    printf("ID invalido.\n");
                    break;
                }
                if (buscar_bst(arvore, l.id) != NULL) {
                    printf("ID %d ja esta cadastrado.\n", l.id);
                    break;
                }
                printf("Titulo: ");
                if (!ler_texto(l.titulo, sizeof(l.titulo))) {
                    printf("Titulo obrigatorio.\n");
                    break;
                }
                printf("Autor: ");
                if (!ler_texto(l.autor, sizeof(l.autor))) {
                    printf("Autor obrigatorio.\n");
                    break;
                }
                printf("Ano de publicacao: ");
                if (!ler_inteiro(&l.ano) || l.ano < 1 || l.ano > 2026) {
                    printf("Ano invalido.\n");
                    break;
                }

                if (!inserir_bst(arvore, l)) {
                    printf("Erro ao inserir na BST.\n");
                    break;
                }

                if (!inserir_vertice(grafo, l.id)) {
                    remover_bst(arvore, l.id);
                    printf("Erro ao criar vertice no grafo. Operacao cancelada.\n");
                    break;
                }

                RegistroAcao ac;
                strcpy(ac.operacao, "CADASTRO");
                ac.id1 = l.id;
                ac.id2 = -1;
                push(historico, ac);
                printf("Livro %d cadastrado com sucesso!\n", l.id);
                break;
            }
            case 2: {
                int id;
                printf("ID para busca: ");
                if (!ler_inteiro(&id)) break;
                struct no_bst *achado = buscar_bst(arvore, id);
                if (achado != NULL) {
                    printf("\n--- Livro Encontrado ---\n");
                    printf("ID: %d\nTitulo: %s\nAutor: %s\nAno: %d\n",
                           achado->dados.id, achado->dados.titulo, achado->dados.autor, achado->dados.ano);
                } else {
                    printf("Livro %d nao encontrado.\n", id);
                }
                break;
            }
            case 3: {
                int id;
                printf("ID a remover: ");
                if (!ler_inteiro(&id)) break;
                if (buscar_bst(arvore, id) == NULL) {
                    printf("Livro %d nao cadastrado.\n", id);
                    break;
                }
                remover_bst(arvore, id);
                remover_vertice(grafo, id);

                RegistroAcao ac;
                strcpy(ac.operacao, "REMOCAO");
                ac.id1 = id;
                ac.id2 = -1;
                push(historico, ac);
                printf("Livro %d removido do sistema.\n", id);
                break;
            }
            case 4: {
                printf("\n--- Catalogo (Ordem por ID) ---\n");
                listar_em_ordem(arvore);
                int min, max;
                if (menor_id(arvore, &min)) printf("Menor ID: %d\n", min);
                if (maior_id(arvore, &max)) printf("Maior ID: %d\n", max);
                break;
            }
            case 5: {
                if (arvore->qtd == 0) {
                    printf("Nenhum livro cadastrado.\n");
                    break;
                }
                Livro *vet = (Livro*) malloc(arvore->qtd * sizeof(Livro));
                if (!vet) break;
                int pos = 0;
                copiar_para_array(arvore->raiz, vet, &pos);
                ordenar_por_titulo(vet, arvore->qtd);

                printf("\n--- Catalogo Ordenado por Titulo ---\n");
                for (int i = 0; i < arvore->qtd; i++) {
                    printf("\"%s\" (ID: %d) - %s [%d]\n",
                           vet[i].titulo, vet[i].id, vet[i].autor, vet[i].ano);
                }
                free(vet);
                break;
            }
            case 6: {
                int a, b;
                printf("ID do livro 1: ");
                if (!ler_inteiro(&a)) break;
                printf("ID do livro 2: ");
                if (!ler_inteiro(&b)) break;

                if (ligar_aresta(grafo, a, b)) {
                    RegistroAcao ac;
                    strcpy(ac.operacao, "ADD_ARESTA");
                    ac.id1 = a;
                    ac.id2 = b;
                    push(historico, ac);
                    printf("Conexao criada entre %d e %d!\n", a, b);
                } else {
                    printf("Nao foi possivel criar a conexao.\n");
                }
                break;
            }
            case 7: {
                int a, b;
                printf("ID do livro 1: ");
                if (!ler_inteiro(&a)) break;
                printf("ID do livro 2: ");
                if (!ler_inteiro(&b)) break;

                if (desligar_aresta(grafo, a, b)) {
                    RegistroAcao ac;
                    strcpy(ac.operacao, "REM_ARESTA");
                    ac.id1 = a;
                    ac.id2 = b;
                    push(historico, ac);
                    printf("Conexao removida entre %d e %d.\n", a, b);
                } else {
                    printf("Conexao inexistente.\n");
                }
                break;
            }
            case 8: {
                int a, b;
                printf("ID 1: ");
                if (!ler_inteiro(&a)) break;
                printf("ID 2: ");
                if (!ler_inteiro(&b)) break;

                if (buscar_indice(grafo, a) == -1 || buscar_indice(grafo, b) == -1) {
                    printf("Um ou ambos os IDs nao foram encontrados.\n");
                } else if (tem_conexao(grafo, a, b)) {
                    printf("Existe conexao direta entre %d e %d.\n", a, b);
                } else {
                    printf("Nao existe conexao direta entre %d e %d.\n", a, b);
                }
                break;
            }
            case 9: {
                int origem;
                printf("ID do livro inicial: ");
                if (!ler_inteiro(&origem)) break;
                executar_bfs(grafo, origem);
                break;
            }
            case 10: {
                int a, b;
                printf("ID de origem: ");
                if (!ler_inteiro(&a)) break;
                printf("ID de destino: ");
                if (!ler_inteiro(&b)) break;

                int res = tem_caminho(grafo, a, b);
                if (res == -1) {
                    printf("IDs nao encontrados no grafo.\n");
                } else if (res == 1) {
                    printf("Existe caminho entre os livros %d e %d.\n", a, b);
                } else {
                    printf("Nao existe caminho entre os livros %d e %d.\n", a, b);
                }
                break;
            }
            case 11: {
                ver_ultimas_cinco(historico);
                break;
            }
            case 0:
                printf("Saindo e liberando memoria...\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (op != 0);

    liberar_bst(arvore);
    liberar_grafo(grafo);
    liberar_pilha(historico);

    return 0;
}