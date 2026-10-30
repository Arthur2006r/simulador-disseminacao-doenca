#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>

typedef struct evento {
    int id_pessoa;
    int estado_origem;
    int estado_final;
    int dia;
} Evento;

typedef struct celula Celula;
typedef struct pilha Pilha;

Pilha *pilha_inicia();
Pilha *pilha_libera(Pilha *pilha);

bool pilha_eh_vazia(Pilha *pilha);

bool empilhar(Pilha *pilha, Evento evento);
bool desempilhar(Pilha *pilha, Evento *evento);

Evento criar_evento(int id_pessoa, int estado_origem, int estado_final, int dia);

#endif