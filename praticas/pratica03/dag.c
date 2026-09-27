#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    int *grau_entrada = (int*) calloc(g->n, sizeof(int));
    
    // Calcula o grau de entrada de todos os vértices
    for (int u = 0; u < g->n; u++) {
        No *atual = g->adj[u];
        while (atual != NULL) {
            grau_entrada[atual->destino]++;
            atual = atual->prox;
        }
    }

    int *fila = (int*) malloc(g->n * sizeof(int));
    int inicio = 0, fim = 0;

    // Enfileira vértices com grau de entrada 0
    for (int i = 0; i < g->n; i++) {
        if (grau_entrada[i] == 0) {
            fila[fim++] = i;
        }
    }

    int *ordem = (int*) malloc(g->n * sizeof(int));
    int count = 0;

    // Processa a fila
    while (inicio < fim) {
        int u = fila[inicio++];
        ordem[count++] = u;

        No *atual = g->adj[u];
        while (atual != NULL) {
            int v = atual->destino;
            grau_entrada[v]--;
            if (grau_entrada[v] == 0) {
                fila[fim++] = v;
            }
            atual = atual->prox;
        }
    }

    free(grau_entrada);
    free(fila);

    // Se count < n, o grafo possui um ciclo
    if (count != g->n) {
        free(ordem);
        *tamanho = 0;
        return NULL;
    }

    *tamanho = count;
    return ordem;
}

// Função auxiliar recursiva para a DFS topológica
void dfs_topologica(GrafoLista *g, int u, int *visitado, int *pilha, int *topo, int *tem_ciclo, int *em_processamento) {
    visitado[u] = 1;
    em_processamento[u] = 1; // Marca como na pilha de recursão atual (para achar ciclo)

    No *atual = g->adj[u];
    while (atual != NULL) {
        int v = atual->destino;
        if (em_processamento[v]) {
            *tem_ciclo = 1; // Aresta de retorno = ciclo
        }
        if (!visitado[v]) {
            dfs_topologica(g, v, visitado, pilha, topo, tem_ciclo, em_processamento);
        }
        atual = atual->prox;
    }

    em_processamento[u] = 0;
    pilha[(*topo)--] = u; // Empilha na saída
}

int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    int *visitado = (int*) calloc(g->n, sizeof(int));
    int *em_processamento = (int*) calloc(g->n, sizeof(int));
    int *pilha = (int*) malloc(g->n * sizeof(int));
    int topo = g->n - 1; // Preenchemos de trás para frente
    int tem_ciclo = 0;

    for (int i = 0; i < g->n; i++) {
        if (!visitado[i]) {
            dfs_topologica(g, i, visitado, pilha, &topo, &tem_ciclo, em_processamento);
        }
    }

    free(visitado);
    free(em_processamento);

    if (tem_ciclo) {
        free(pilha);
        *tamanho = 0;
        return NULL;
    }

    *tamanho = g->n;
    return pilha;
}

int eh_dag(GrafoLista *g) {
    int tamanho;
    int *ordem = ordenacao_topologica_kahn(g, &tamanho);
    if (ordem == NULL) {
        return 0; // Tem ciclo, não é DAG
    }
    free(ordem);
    return 1; // É acíclico, é DAG
}