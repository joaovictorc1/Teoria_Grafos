#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "conectividade.h"
#include "planaridade.h"

int main(void) {
    int n = 5;
    GrafoLista *g = criar_grafo_lista(n);
    
    // Cria um grafo com uma ponte (2-3) e dois vértices de corte (2 e 3)
    inserir_aresta_lista(g, 0, 1);
    inserir_aresta_lista(g, 1, 2);
    inserir_aresta_lista(g, 2, 0); // Ciclo 0-1-2
    
    inserir_aresta_lista(g, 2, 3); // Ponte
    
    inserir_aresta_lista(g, 3, 4); // Ligado à ponte
    
    printf("--- Teste de Conectividade (Tarjan) ---\n");
    encontrar_articulacoes(g);
    detectar_pontes(g);
    
    printf("\n");
    verificar_planaridade(g);
    
    liberar_grafo_lista(g);
    return 0;
}