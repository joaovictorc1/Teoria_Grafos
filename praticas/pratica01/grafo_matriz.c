#include <stdlib.h>
#include "grafo_matriz.h"

GrafoMatriz* criar_grafo_matriz(int n) {
    GrafoMatriz *grafo = (GrafoMatriz *) malloc(sizeof(GrafoMatriz));
    grafo->n = n;
    grafo->adj = (int **) malloc(n * sizeof(int *));
    
    for (int i = 0; i < n; i++) {
        grafo->adj[i] = (int *) malloc(n * sizeof(int));
    }
    
    return grafo;
}

void inserir_aresta_matriz(GrafoMatriz *grafo, int u, int v) {
    grafo->adj[u][v] = 1;
    grafo->adj[v][u] = 1;
}

void remover_aresta_matriz(GrafoMatriz *grafo, int u, int v) {
    grafo->adj[u][v] = 0;
    grafo->adj[v][u] = 0;
}

int grau_matriz(GrafoMatriz *grafo, int u) {
    int grau = 0;
    for (int i = 0; i < grafo->n; i++) {
        grau += grafo->adj[u][i];
    }
    return grau;
}

int sao_adjacentes_matriz(GrafoMatriz *grafo, int u, int v) {
    return grafo->adj[u][v];
}

void liberar_grafo_matriz(GrafoMatriz *grafo) {
    // Libera as colunas de cada linha (de dentro)
    for (int i = 0; i < grafo->n; i++) {
        free(grafo->adj[i]);
    }
    // Libera o array de ponteiros principal
    free(grafo->adj);
    // Libera a estrutura do grafo (para fora)
    free(grafo);
}