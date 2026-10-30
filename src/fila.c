#include "fila.h"

#include <stdlib.h>

struct celula {
    Pessoa *pessoa;
    struct celula *prox;
};

struct fila {
    int n;
    Celula *ini;
    Celula *fim;
};

Fila *fila_inicia() {
    Fila *fila = malloc(sizeof(Fila));
    if(fila) {
        fila->ini = malloc(sizeof(Celula));
        if(fila->ini) {
            fila->fim = fila->ini;
            fila->ini->prox = NULL;

            fila->n = 0;
        } else {
            free(fila);
            fila = NULL;
        }
    }

    return fila;
}

Fila *fila_libera(Fila *fila) {
    if(!fila) return NULL;

    Celula *atual = fila->ini;
    Celula *proximo;

    while(atual) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    free(fila);

    return NULL;
}

bool fila_eh_vazia(Fila *fila) {
    if(!fila) return true;

    return fila->ini == fila->fim || fila->n == 0;
}

bool enfileira(Fila *fila, Pessoa *pessoa) {
    if(!fila) return false;

    Celula *novo = malloc(sizeof(Celula));
    if(!novo) return false;

    novo->pessoa = pessoa;
    novo->prox = NULL;

    fila->fim->prox = novo;
    fila->fim = novo;

    fila->n++;

    return true;
}

Pessoa *desenfileira(Fila *fila) {
    if(fila_eh_vazia(fila)) return NULL;

    Celula *aux = fila->ini->prox;
    Pessoa *pessoa = aux->pessoa;

    fila->ini->prox = aux->prox;

    if(aux == fila->fim)
        fila->fim = fila->ini;

    free(aux);
    fila->n--;

    return pessoa;
}
