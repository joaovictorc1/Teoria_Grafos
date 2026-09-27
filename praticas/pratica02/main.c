#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "busca_largura.h"
#include "busca_profundidade.h"

int main(void) {
    int n = 5;
    GrafoLista *g = criar_grafo_lista(n);
    
    inserir_aresta_lista(g, 0, 1);
    inserir_aresta_lista(g, 1, 2);
    inserir_aresta_lista(g, 3, 4);
    
    printf("--- Teste BFS ---\n");
    int *dist = (int*) malloc(n * sizeof(int));
    int *pred = (int*) malloc(n * sizeof(int));
    bfs(g, 0, dist, pred);
    printf("Distância de 0 a 2: %d\n", dist[2]);
    free(dist); free(pred);
    
    printf("--- Teste DFS ---\n");
    printf("Componentes conexos: %d\n", contar_componentes(g));
    printf("Tem ciclo? %s\n", tem_ciclo(g) ? "Sim" : "Nao");
    printf("Eh bipartido? %s\n", eh_bipartido(g) ? "Sim" : "Nao");
    
    liberar_grafo_lista(g);
    return 0;
}