#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "coloracao.h"

int main(void) {
    int n = 5;
    GrafoLista *g = criar_grafo_lista(n);

    // Grafo ciclo de 5 vértices (C5) 
    inserir_aresta_lista(g, 0, 1);
    inserir_aresta_lista(g, 1, 2);
    inserir_aresta_lista(g, 2, 3);
    inserir_aresta_lista(g, 3, 4);
    inserir_aresta_lista(g, 4, 0);

    printf("--- Coloração Gulosa ---\n");
    int num_cores_gulosa;
    int *cores_gulosa = coloracao_gulosa(g, &num_cores_gulosa);
    printf("Total de cores: %d\n", num_cores_gulosa);
    free(cores_gulosa);

    printf("--- Coloração Welsh-Powell ---\n");
    int num_cores_wp;
    int *cores_wp = coloracao_welsh_powell(g, &num_cores_wp);
    printf("Total de cores: %d\n", num_cores_wp);
    free(cores_wp);

    printf("--- Bipartição ---\n");
    printf("O grafo eh bipartido? %s\n", eh_bipartido(g) ? "Sim" : "Nao");

    liberar_grafo_lista(g);
    return 0;
}