#ifndef LISTA_H
#define LISTA_H

#include "pessoa.h"
#include <stdbool.h>

typedef struct celula Celula;
typedef struct lista Lista;

Lista *lista_inicia();
Lista *lista_libera(Lista *lista);

int lista_tamanho(Lista *lista);
void lista_libera_com_pessoas(Lista *lista);

bool lista_eh_vazia(Lista *lista);
bool lista_insere_inicio(Lista *lista, Pessoa *pessoa);
bool lista_insere_apos(Lista *lista, Celula *pino, Pessoa *pessoa);

Pessoa *lista_remove_inicio(Lista *lista);
Pessoa *lista_remove_apos(Lista *lista, Celula *pino);

Celula *get_lista_primeiro(Lista *lista);
Celula *get_celula_proximo(Celula *celula);
Pessoa *get_celula_get_pessoa(Celula *celula);

#endif