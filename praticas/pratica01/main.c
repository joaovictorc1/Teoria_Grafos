#include <stdio.h>
#include <stdlib.h>
#include "grafo_matriz.h"
#include "grafo_lista.h"

int main(void) {
    int n = 5;

    // Testando o Grafo com Matriz de Adjacência
    GrafoMatriz* grafo_m = criar_grafo_matriz(n);
    inserir_aresta_matriz(grafo_m, 0, 1);
    inserir_aresta_matriz(grafo_m, 1, 2);
    printf("Grau do vertice 1 na Matriz: %d\n", grau_matriz(grafo_m, 1));
    liberar_grafo_matriz(grafo_m);

    // Testando o Grafo com Lista de Adjacência
    GrafoLista* grafo_l = criar_grafo_lista(n);
    inserir_aresta_lista(grafo_l, 0, 1);
    inserir_aresta_lista(grafo_l, 1, 2);
    printf("Grau do vertice 1 na Lista: %d\n", grau_lista(grafo_l, 1));
    liberar_grafo_lista(grafo_l);

    return 0;
}