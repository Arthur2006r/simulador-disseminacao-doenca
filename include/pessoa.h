#ifndef PESSOA_H
#define PESSOA_H

typedef struct pessoa Pessoa;

Pessoa *pessoa_cria(const char *nome, int id, int idade);
Pessoa *pessoa_copia(Pessoa *p);
void pessoa_libera(Pessoa *p);

int get_id(Pessoa *p);
int get_idade(Pessoa *p);
const char *get_nome(Pessoa *p);

int verifica_prioridade(Pessoa *p1, Pessoa *p2);

#endif