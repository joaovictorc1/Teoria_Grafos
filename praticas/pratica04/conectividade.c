#include <stdio.h>
#include <stdlib.h>
#include "conectividade.h"

// Função auxiliar para retornar o mínimo
int min_val(int a, int b) {
    return (a < b) ? a : b;
}

// Algoritmo de Tarjan para vértices de corte
void dfs_articulacoes(GrafoLista *g, int u, int *descoberta, int *low, int *pai, int *articulacao, int *tempo) {
    int filhos = 0;
    descoberta[u] = low[u] = ++(*tempo);

    No *atual = g->adj[u];
    while (atual != NULL) {
        int v = atual->destino;

        if (descoberta[v] == 0) { // Não visitado
            filhos++;
            pai[v] = u;
            dfs_articulacoes(g, v, descoberta, low, pai, articulacao, tempo);

            // Atualiza o valor low de u
            low[u] = min_val(low[u], low[v]);

            // Caso 1: u é raiz da DFS e tem mais de 1 filho
            if (pai[u] == -1 && filhos > 1)
                articulacao[u] = 1;

            // Caso 2: u não é raiz e o low do filho v >= descoberta de u
            if (pai[u] != -1 && low[v] >= descoberta[u])
                articulacao[u] = 1;
                
        } else if (v != pai[u]) {
            // Aresta de retorno (back-edge)
            low[u] = min_val(low[u], descoberta[v]);
        }
        atual = atual->prox;
    }
}

void encontrar_articulacoes(GrafoLista *g) {
    int *descoberta = (int*) calloc(g->n, sizeof(int));
    int *low = (int*) calloc(g->n, sizeof(int));
    int *pai = (int*) malloc(g->n * sizeof(int));
    int *articulacao = (int*) calloc(g->n, sizeof(int));
    int tempo = 0;

    for (int i = 0; i < g->n; i++) pai[i] = -1;

    for (int i = 0; i < g->n; i++) {
        if (descoberta[i] == 0) {
            dfs_articulacoes(g, i, descoberta, low, pai, articulacao, &tempo);
        }
    }

    printf("Articulacoes (Vertices de Corte): ");
    int achou = 0;
    for (int i = 0; i < g->n; i++) {
        if (articulacao[i]) {
            printf("%d ", i);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhuma");
    printf("\n");

    free(descoberta); free(low); free(pai); free(articulacao);
}

// DFS específica para detectar pontes
void dfs_pontes(GrafoLista *g, int u, int *descoberta, int *low, int *pai, int *tempo) {
    descoberta[u] = low[u] = ++(*tempo);

    No *atual = g->adj[u];
    while (atual != NULL) {
        int v = atual->destino;

        if (descoberta[v] == 0) { // Não visitado
            pai[v] = u;
            dfs_pontes(g, v, descoberta, low, pai, tempo);

            low[u] = min_val(low[u], low[v]);

            // Condição para ser ponte: low[v] > descoberta[u]
            if (low[v] > descoberta[u]) {
                printf("(%d, %d) ", u, v);
            }
        } else if (v != pai[u]) {
            low[u] = min_val(low[u], descoberta[v]);
        }
        atual = atual->prox;
    }
}

void detectar_pontes(GrafoLista *g) {
    int *descoberta = (int*) calloc(g->n, sizeof(int));
    int *low = (int*) calloc(g->n, sizeof(int));
    int *pai = (int*) malloc(g->n * sizeof(int));
    int tempo = 0;

    for (int i = 0; i < g->n; i++) pai[i] = -1;

    printf("Pontes (Arestas de Corte): ");
    for (int i = 0; i < g->n; i++) {
        if (descoberta[i] == 0) {
            dfs_pontes(g, i, descoberta, low, pai, &tempo);
        }
    }
    printf("\n");

    free(descoberta); free(low); free(pai);
}