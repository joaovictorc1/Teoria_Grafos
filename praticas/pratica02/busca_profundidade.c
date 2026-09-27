#include <stdio.h>
#include <stdlib.h>
#include "busca_profundidade.h"

Pilha* criar_pilha(int capacidade) {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    p->capacidade = capacidade;
    p->dados = (int*) malloc(capacidade * sizeof(int));
    p->topo = -1;
    return p;
}

void empilhar(Pilha *p, int valor) {
    if (p->topo < p->capacidade - 1) {
        p->dados[++(p->topo)] = valor;
    }
}

int desempilhar(Pilha *p) {
    if (p->topo >= 0) {
        return p->dados[(p->topo)--];
    }
    return -1;
}

int pilha_vazia(Pilha *p) {
    return p->topo == -1;
}

void liberar_pilha(Pilha *p) {
    free(p->dados);
    free(p);
}

void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *tempo, int *d, int *f, int *pred) {
    visitado[u] = 1;
    (*tempo)++;
    d[u] = *tempo;
    
    No *atual = g->adj[u];
    while (atual != NULL) {
        int v = atual->destino;
        if (!visitado[v]) {
            pred[v] = u;
            dfs_recursiva(g, v, visitado, tempo, d, f, pred);
        }
        atual = atual->prox;
    }
    
    (*tempo)++;
    f[u] = *tempo;
}

int contar_componentes(GrafoLista *g) {
    int *visitado = (int*) calloc(g->n, sizeof(int));
    int componentes = 0;
    int tempo = 0;
    int *d = (int*) calloc(g->n, sizeof(int));
    int *f = (int*) calloc(g->n, sizeof(int));
    int *pred = (int*) malloc(g->n * sizeof(int));
    
    for (int i = 0; i < g->n; i++) pred[i] = -1;

    for (int i = 0; i < g->n; i++) {
        if (!visitado[i]) {
            componentes++;
            dfs_recursiva(g, i, visitado, &tempo, d, f, pred);
        }
    }
    
    free(visitado); free(d); free(f); free(pred);
    return componentes;
}

// Função auxiliar para ciclo
int dfs_ciclo(GrafoLista *g, int u, int *visitado, int pai) {
    visitado[u] = 1;
    No *atual = g->adj[u];
    
    while (atual != NULL) {
        int v = atual->destino;
        if (!visitado[v]) {
            if (dfs_ciclo(g, v, visitado, u)) return 1;
        } else if (v != pai) {
            return 1; // Achou aresta de retorno (ciclo)
        }
        atual = atual->prox;
    }
    return 0;
}

int tem_ciclo(GrafoLista *g) {
    int *visitado = (int*) calloc(g->n, sizeof(int));
    for (int i = 0; i < g->n; i++) {
        if (!visitado[i]) {
            if (dfs_ciclo(g, i, visitado, -1)) {
                free(visitado);
                return 1;
            }
        }
    }
    free(visitado);
    return 0;
}