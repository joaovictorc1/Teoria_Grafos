#include <stdlib.h>
#include "grafo_lista.h"

GrafoLista* criar_grafo_lista(int n) {
    GrafoLista *grafo = (GrafoLista *) malloc(sizeof(GrafoLista));
    grafo->n = n;
    grafo->adj = (No **) malloc(n * sizeof(No *));
    
    for (int i = 0; i < n; i++) {
        grafo->adj[i] = NULL;
    }
    
    return grafo;
}

void inserir_aresta_lista(GrafoLista *grafo, int u, int v) {
    // Cria o nó para representar o destino v
    No *novo_no = (No *) malloc(sizeof(No));
    novo_no->destino = v;
    
    // Pendura o nó no início da lista de u
    novo_no->prox = grafo->adj[u];
    grafo->adj[u] = novo_no;
    
    No *novo_no_2 = (No *) malloc(sizeof(No));
    novo_no_2->destino = u;
    
    novo_no_2->prox = grafo->adj[v];
    grafo->adj[v] = novo_no_2;
}

void remover_aresta_lista(GrafoLista *grafo, int u, int v) {
    // 1. Remover v da lista de u
    No *atual = grafo->adj[u];
    No *anterior = NULL;
    
    while (atual != NULL && atual->destino != v) {
        anterior = atual;
        atual = atual->prox;
    }
    
    if (atual != NULL) { // Se encontrou o nó
        if (anterior == NULL) {
            grafo->adj[u] = atual->prox; // Era o primeiro da lista
        } else {
            anterior->prox = atual->prox; // Estava no meio ou fim
        }
        free(atual);
    }

    // 2. Remover u da lista de v (mesma lógica)
    atual = grafo->adj[v];
    anterior = NULL;
    
    while (atual != NULL && atual->destino != u) {
        anterior = atual;
        atual = atual->prox;
    }
    
    if (atual != NULL) {
        if (anterior == NULL) {
            grafo->adj[v] = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }
        free(atual);
    }
}

int sao_adjacentes_lista(GrafoLista *grafo, int u, int v) {
    No *atual = grafo->adj[u];
    
    while (atual != NULL) {
        if (atual->destino == v) {
            return 1; // Encontrou! (true)
        }
        atual = atual->prox;
    }
    
    return 0; // Percorreu tudo e não achou (false)
}

int grau_lista(GrafoLista *grafo, int u) {
    int count = 0;
    No *atual = grafo->adj[u];
    
    while (atual != NULL) {
        count++;
        atual = atual->prox;
    }
    
    return count;
}

void liberar_grafo_lista(GrafoLista *grafo) {
    // 1. Libera os nós de cada lista
    for (int i = 0; i < grafo->n; i++) {
        No *atual = grafo->adj[i];
        while (atual != NULL) {
            No *proximo = atual->prox; // Guarda o resto da corrente
            free(atual);               // Apaga o elo atual
            atual = proximo;           // Avança para o próximo
        }
    }
    
    // 2. Libera o array principal de ponteiros
    free(grafo->adj);
    
    // 3. Libera a estrutura principal do grafo
    free(grafo);
}