#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "dag.h"

// Função local para inserir aresta DIRECIONADA, já que o algoritmo exige um DAG
void inserir_aresta_direcionada(GrafoLista *g, int u, int v) {
    No *novo_no = (No*) malloc(sizeof(No));
    novo_no->destino = v;
    novo_no->prox = g->adj[u];
    g->adj[u] = novo_no;
}

int main(void) {
    int n = 6;
    GrafoLista *g = criar_grafo_lista(n);
    
    // Construindo um DAG (Grafo Direcionado Acíclico) clássico
    inserir_aresta_direcionada(g, 5, 2);
    inserir_aresta_direcionada(g, 5, 0);
    inserir_aresta_direcionada(g, 4, 0);
    inserir_aresta_direcionada(g, 4, 1);
    inserir_aresta_direcionada(g, 2, 3);
    inserir_aresta_direcionada(g, 3, 1);
    
    printf("--- Teste de DAG ---\n");
    printf("O grafo eh um DAG? %s\n", eh_dag(g) ? "Sim" : "Nao");

    int tamanho_kahn;
    int *ordem_kahn = ordenacao_topologica_kahn(g, &tamanho_kahn);
    if (ordem_kahn != NULL) {
        printf("Ordenacao Topologica (Kahn): ");
        for (int i = 0; i < tamanho_kahn; i++) {
            printf("%d ", ordem_kahn[i]);
        }
        printf("\n");
        free(ordem_kahn);
    }

    int tamanho_dfs;
    int *ordem_dfs = ordenacao_topologica_dfs(g, &tamanho_dfs);
    if (ordem_dfs != NULL) {
        printf("Ordenacao Topologica (DFS):  ");
        for (int i = 0; i < tamanho_dfs; i++) {
            printf("%d ", ordem_dfs[i]);
        }
        printf("\n");
        free(ordem_dfs);
    }
    
    liberar_grafo_lista(g);
    return 0;
}