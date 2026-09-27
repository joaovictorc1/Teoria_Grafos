#ifndef PLANARIDADE_H
#define PLANARIDADE_H

#include "grafo_lista.h"

int eh_planar_euler(GrafoLista *g);
int heuristica_kuratowski(GrafoLista *g);
void verificar_planaridade(GrafoLista *g);

#endif