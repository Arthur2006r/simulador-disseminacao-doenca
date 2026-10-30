#include "pessoa.h"

#include <string.h>

struct pessoa {
    char nome[100];
    int id;
    int idade;
};

Pessoa *cria_pessoa(char nome[], int id, int idade) {
    Pessoa *p = malloc(sizeof(Pessoa));
    if(!p) return NULL;

    strcpy(p->nome, nome);
    p->id = id;
    p->idade = idade;

    return p;
}

int verifica_prioridade(const Pessoa *p1, const Pessoa *p2) {
    if(p1->idade > p2->idade)
        return 0;
    else if(p1->idade < p2->idade)
        return 1;
    else 
        return (p1->id < p2->id) ? 0 : 1;

    return -1;
}

int get_id(const Pessoa *p) {
    return p->id;
}
