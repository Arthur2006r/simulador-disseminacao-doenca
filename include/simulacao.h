#ifndef SIMULACAO_H
#define SIMULACAO_H

#include "parametros.h"
#include "lista.h"
#include "fila.h"
#include "pilha.h"

void registra_evento(Pilha *historico, Pessoa *pessoa, int dia, int estado_origem, int estado_final);

void simular_epidemia(Parametros parametros, Lista *estado_1, 
                     Lista *estado_2, Lista *estado_3, Lista *estado_4, 
                     Lista *estado_5, Fila *fila_infectados, Pilha *historico);

void fase_vacinacao(Parametros parametros, Lista *estado_1, Lista *estado_5, Pilha *historico, int dia);

void fase_infeccao(Lista *estado_1, Lista *estado_sup, Fila *fila_infectados, 
                   Pilha *historico, int probabilidade, int dia);

void fase_evolucao_estado_2(Lista *estado_1, Lista *estado_2, 
                            Lista *estado_3, Pilha *historico, int probabilidade, int dia);

void fase_evolucao_estado_3(Lista *estado_1, Lista *estado_3, 
                            Lista *estado_4, Pilha *historico, int probabilidade, int dia);

void fase_fim_dia(Lista *estado_2, Fila *fila_infectados);

#endif