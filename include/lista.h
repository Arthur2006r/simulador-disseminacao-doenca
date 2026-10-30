#ifndef LISTA_H
#define LISTA_H

#include "pessoa.h"
#include <stdbool.h>

typedef struct celula Celula;
typedef struct lista Lista;

Lista *lista_inicia();
Lista *lista_libera(Lista *lista);

bool lista_eh_vazia(Lista *lista);
bool lista_insere_inicio(Lista *lista, Pessoa *pessoa);
Pessoa *lista_remove_inicio(Lista *lista);

#endif