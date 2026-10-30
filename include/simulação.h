#ifndef SIMULACAO_H
#define SIMULACAO_H

#include "parametros.h"
#include "lista.h"
#include "pilha.h"
#include "fila.h"

void simular_epidemia(Parametros parametros, Lista *estado_1, Lista *estado_2, 
    Lista *estado_3, Lista *estado_4, Lista *estado_5, Fila *fila_infectados, Pilha *historico);

#endif