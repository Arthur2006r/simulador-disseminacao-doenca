#ifndef PESSOA_H
#define PESSOA_H

typedef struct pessoa Pessoa;

Pessoa *cria_pessoa(char nome[], int id, int idade);

int verifica_prioridade(const Pessoa *p1, const Pessoa *p2);

int get_id(const Pessoa *p);

#endif
