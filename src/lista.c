#include "lista.h"

#include <stdlib.h>

struct celula {
    Pessoa *pessoa;
    struct celula *prox;
};

struct lista {
    int n;
    Celula *cabeca;
    Celula *cauda;
};

Lista *lista_inicia() {
    Lista *lista = malloc(sizeof(Lista));
    if(lista) {
       lista->cabeca = malloc(sizeof(Celula));
       if(lista->cabeca) {
           lista->cabeca->prox = NULL;
           lista->cauda = lista->cabeca;

           lista->n = 0;
        } else {
            free(lista);
            lista = NULL;
        }
    }

    return lista;
}

Lista *lista_libera(Lista *lista) {
    if(!lista) return NULL;

    Celula *atual = lista->cabeca;
    Celula *proximo;

    while(atual) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    free(lista);

    return NULL;
}

bool lista_eh_vazia(Lista *lista) {
   if(!lista || !lista->cabeca) return true;

   return lista->n == 0 || lista->cabeca->prox == NULL;
}

bool lista_insere_inicio(Lista *lista, Pessoa *pessoa) {       
    Celula *novo = malloc(sizeof(Celula));
    if(!novo) return false;

    novo->pessoa = pessoa;

    Celula *aux = lista->cabeca;

    novo->prox = aux->prox;
    aux->prox = novo;

    if(lista->n == 0)
        lista->cauda = novo;

    lista->n++;

    return true;
}

Pessoa *lista_remove_inicio(Lista *lista) {
    if(lista_eh_vazia(lista))
        return NULL;

    Celula *ant = lista->cabeca;

    Celula *aux = ant->prox;
    ant->prox = aux->prox;

    if(ant->prox == NULL)
        lista->cauda = ant;
    
    Pessoa *pessoa = aux->pessoa;

    free(aux);
    lista->n--;

    return pessoa;
}
