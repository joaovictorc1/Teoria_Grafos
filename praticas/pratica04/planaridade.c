#include <stdio.h>
#include <stdlib.h>
#include "planaridade.h"

// Conta o total de arestas de um grafo não direcionado
int contar_arestas(GrafoLista *g) {
    int m = 0;
    for (int u = 0; u < g->n; u++) {
        No *atual = g->adj[u];
        while (atual != NULL) {
            m++;
            atual = atual->prox;
        }
    }
    return m / 2; // Divide por 2 pois cada aresta é contada duas vezes no GrafoLista
}

int eh_planar_euler(GrafoLista *g) {
    if (g->n < 3) return 1; // Grafos com 1 ou 2 vértices são sempre planares
    
    int m = contar_arestas(g);
    // Fórmula de Euler para planaridade: m <= 3n - 6
    return (m <= 3 * g->n - 6);
}

// Heurística simplificada de força bruta (baseada em graus) para K_5 e K_3,3 em n <= 10
int heuristica_kuratowski(GrafoLista *g) {
    if (g->n > 10) return 1; // Aplicar apenas para grafos pequenos conforme as instruções
    
    int vertices_grau_4 = 0;
    int vertices_grau_3 = 0;
    
    for (int i = 0; i < g->n; i++) {
        int grau = 0;
        No *atual = g->adj[i];
        while (atual != NULL) {
            grau++;
            atual = atual->prox;
        }
        if (grau >= 4) vertices_grau_4++;
        if (grau >= 3) vertices_grau_3++;
    }
    
    // Condições necessárias (mas não suficientes) para conter K_5 ou K_3,3
    if (g->n >= 5 && vertices_grau_4 >= 5) return 0; // Potencial K_5
    if (g->n >= 6 && vertices_grau_3 >= 6) return 0; // Potencial K_3,3
    
    return 1;
}

void verificar_planaridade(GrafoLista *g) {
    printf("Teste de Planaridade:\n");
    if (!eh_planar_euler(g)) {
        printf("- Rejeitado pela formula de Euler (m > 3n - 6).\n");
    } else if (g->n <= 10 && !heuristica_kuratowski(g)) {
        printf("- Rejeitado pela heuristica de Kuratowski (potencial K_5 ou K_3,3).\n");
    } else {
        printf("- O grafo tem alta probabilidade de ser planar.\n");
    }
}