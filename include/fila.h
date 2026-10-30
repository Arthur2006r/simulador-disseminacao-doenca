#ifndef FILA_H
#define FILA_H

#include "pessoa.h"
#include <stdbool.h>

typedef struct celula Celula;
typedef struct fila Fila;

Fila *fila_inicia();
Fila *fila_libera(Fila *fila);

bool fila_eh_vazia(Fila *fila);

bool enfileira(Fila *fila, Pessoa *pessoa);
Pessoa *desenfileira(Fila *fila);

#endif