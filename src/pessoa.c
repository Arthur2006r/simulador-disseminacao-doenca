#include "pessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pessoa {
    char nome[100];
    int id;
    int idade;
};

Pessoa *pessoa_cria(const char *nome, int id, int idade) {
    Pessoa *p = malloc(sizeof(Pessoa));
    if (p) {
        strncpy(p->nome, nome, sizeof(p->nome) - 1);
        p->nome[sizeof(p->nome) - 1] = '\0';
        p->id = id;
        p->idade = idade;
    }
    return p;
}

Pessoa *pessoa_copia(Pessoa *p) {
    if (!p) return NULL;
    return pessoa_cria(p->nome, p->id, p->idade);
}

void pessoa_libera(Pessoa *p) {
    if (p) free(p);
}

int get_id(Pessoa *p) {
    return p ? p->id : -1;
}

int get_idade(Pessoa *p) {
    return p ? p->idade : -1;
}

const char *get_nome(Pessoa *p) {
    return p ? p->nome : "";
}

int verifica_prioridade(Pessoa *p1, Pessoa *p2) {
    if (!p1 || !p2) return 1;

    // Retorna 0 quando p1 tem prioridade sobre p2 (idade maior ou menor ID em empate)
    if (p1->idade > p2->idade) return 0;
    if (p1->idade < p2->idade) return 1;
    if (p1->id < p2->id) return 0;
    return 1;
}