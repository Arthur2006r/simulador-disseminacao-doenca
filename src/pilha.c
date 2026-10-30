#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>

struct celula {
    Evento evento;
    struct celula *prox;
};

struct pilha {
    int n;
    Celula *cabeca; // aqui onde o *prox vai apontar para o topo da pilha
};

Pilha *pilha_inicia() {
    Pilha *pilha = malloc(sizeof(Pilha));
    if(pilha) {
        pilha->cabeca = malloc(sizeof(Celula));
        if(pilha->cabeca) {
            pilha->cabeca->prox = NULL;

            pilha->n = 0;
        } else {
            free(pilha);
            pilha = NULL;
        }
    }

    return pilha;
}

Pilha *pilha_libera(Pilha *pilha) {
    if(!pilha) return pilha;

    Celula *atual = pilha->cabeca;
    Celula *proximo;

    while(atual) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    free(pilha);

    return NULL;
}

bool pilha_eh_vazia(Pilha *pilha) {
    if(!pilha) return true;

    return pilha->n == 0 || pilha->cabeca->prox == NULL;
}

bool empilhar(Pilha *pilha, Evento evento) {
    if(!pilha) return false;

    Celula *novo = malloc(sizeof(Celula));
    if(!novo) return false;

    novo->evento = evento;
    
    Celula *aux = pilha->cabeca->prox;
    novo->prox = aux;
    pilha->cabeca->prox = novo;

    pilha->n++;

    return true;
}

bool desempilhar(Pilha *pilha, Evento *evento) {
    if(pilha_eh_vazia(pilha)) return false;

    Celula *aux = pilha->cabeca->prox;
    pilha->cabeca->prox = aux->prox;

    // TODO: ADAPTAR PARA EVENTO
    if(evento)
        *evento = aux->evento;
    
    free(aux);

    pilha->n--;

    return true;
}

Evento criar_evento(int id_pessoa, int estado_origem, int estado_final, int dia) {
    Evento evento;

    evento.id_pessoa = id_pessoa;
    evento.estado_origem = estado_origem;
    evento.estado_final = estado_final;
    evento.dia = dia;

    return evento;
}
