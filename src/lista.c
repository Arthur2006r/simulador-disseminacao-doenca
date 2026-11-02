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
    if (lista) {
        lista->cabeca = malloc(sizeof(Celula));
        if (lista->cabeca) {
            lista->cabeca->pessoa = NULL; 
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

int lista_tamanho(Lista *lista) {
    if (!lista) return 0;
    return lista->n;
}

void lista_libera_com_pessoas(Lista *lista) {
    if (!lista) return;

    Celula *atual = get_lista_primeiro(lista);
    while (atual) {
        Pessoa *p = get_celula_get_pessoa(atual);
        if (p) {
            pessoa_libera(p);
        }
        atual = get_celula_proximo(atual);
    }

    lista_libera(lista);
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

bool lista_insere_apos(Lista *lista, Celula *pino, Pessoa *pessoa) {
    if (!lista || !pino) return false;

    Celula *novo = malloc(sizeof(Celula));
    if (!novo) return false;

    novo->pessoa = pessoa;
    novo->prox = pino->prox;
    pino->prox = novo;

    if (pino == lista->cauda) {
        lista->cauda = novo;
    }

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

Pessoa *lista_remove_apos(Lista *lista, Celula *pino) {
    if (!lista || !pino || !pino->prox) return NULL;

    Celula *aux = pino->prox;
    Pessoa *pessoa = aux->pessoa;

    pino->prox = aux->prox;

    if (aux == lista->cauda) {
        lista->cauda = pino;
    }

    free(aux);
    lista->n--;

    return pessoa;
}

Celula *get_lista_primeiro(Lista *lista) {
    if (!lista || !lista->cabeca) return NULL;

    return lista->cabeca->prox;
}

Celula *get_celula_proximo(Celula *celula) {
    if (!celula) return NULL;

    return celula->prox;
}

Pessoa *get_celula_get_pessoa(Celula *celula) {
    if (!celula) return NULL;

    return celula->pessoa;
}
