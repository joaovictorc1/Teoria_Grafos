#include <stdio.h>
#include <stdlib.h>
#include "coloracao.h"

// Função auxiliar genérica para aplicar coloração gulosa com base em uma ordem de vértices
int* aplicar_coloracao_gulosa(GrafoLista *g, int *ordem, int *num_cores) {
    int *cor = (int*) malloc(g->n * sizeof(int));
    for (int i = 0; i < g->n; i++) cor[i] = -1; // -1 significa sem cor

    int *cores_adj = (int*) malloc(g->n * sizeof(int));
    int max_cor = -1;

    for (int i = 0; i < g->n; i++) {
        int u = ordem[i];

        // Zera o rastreador de cores adjacentes
        for (int j = 0; j < g->n; j++) cores_adj[j] = 0;

        // Marca as cores já usadas pelos vizinhos
        No *atual = g->adj[u];
        while (atual != NULL) {
            int v = atual->destino;
            if (cor[v] != -1) {
                cores_adj[cor[v]] = 1;
            }
            atual = atual->prox;
        }

        // Procura a menor cor disponível
        int cr;
        for (cr = 0; cr < g->n; cr++) {
            if (cores_adj[cr] == 0) break;
        }

        cor[u] = cr;
        if (cr > max_cor) max_cor = cr;
    }

    free(cores_adj);
    *num_cores = max_cor + 1;
    return cor;
}

int* coloracao_gulosa(GrafoLista *g, int *num_cores) {
    int *ordem = (int*) malloc(g->n * sizeof(int));
    for (int i = 0; i < g->n; i++) ordem[i] = i; // Ordem natural: 0, 1, 2...

    int *resultado = aplicar_coloracao_gulosa(g, ordem, num_cores);
    free(ordem);
    return resultado;
}

// Estrutura para ordenar no Welsh-Powell
typedef struct {
    int vertice;
    int grau;
} VerticeGrau;

// Comparador para ordenar decrescente pelo grau (para o qsort)
int comparar_grau(const void *a, const void *b) {
    VerticeGrau *va = (VerticeGrau *)a;
    VerticeGrau *vb = (VerticeGrau *)b;
    return vb->grau - va->grau;
}

int* coloracao_welsh_powell(GrafoLista *g, int *num_cores) {
    VerticeGrau *vg = (VerticeGrau*) malloc(g->n * sizeof(VerticeGrau));

    // Calcula o grau de todos os vértices
    for (int i = 0; i < g->n; i++) {
        vg[i].vertice = i;
        vg[i].grau = 0;
        No *atual = g->adj[i];
        while (atual != NULL) {
            vg[i].grau++;
            atual = atual->prox;
        }
    }

    // Ordena do maior para o menor grau
    qsort(vg, g->n, sizeof(VerticeGrau), comparar_grau);

    int *ordem = (int*) malloc(g->n * sizeof(int));
    for (int i = 0; i < g->n; i++) {
        ordem[i] = vg[i].vertice;
    }

    int *resultado = aplicar_coloracao_gulosa(g, ordem, num_cores);

    free(vg);
    free(ordem);
    return resultado;
}

// Bipartição via BFS (2-coloração)
int eh_bipartido(GrafoLista *g) {
    int *cor = (int*) malloc(g->n * sizeof(int));
    for (int i = 0; i < g->n; i++) cor[i] = -1;

    int *fila = (int*) malloc(g->n * sizeof(int));

    for (int i = 0; i < g->n; i++) {
        if (cor[i] == -1) {
            int inicio = 0, fim = 0;
            fila[fim++] = i;
            cor[i] = 0;

            while (inicio < fim) {
                int u = fila[inicio++];
                No *atual = g->adj[u];

                while (atual != NULL) {
                    int v = atual->destino;
                    if (cor[v] == -1) {
                        cor[v] = 1 - cor[u]; // Alterna entre cor 0 e 1
                        fila[fim++] = v;
                    } else if (cor[v] == cor[u]) {
                        free(cor);
                        free(fila);
                        return 0; // Achou conflito (não bipartido)
                    }
                    atual = atual->prox;
                }
            }
        }
    }

    free(cor);
    free(fila);
    return 1; // É bipartido
}