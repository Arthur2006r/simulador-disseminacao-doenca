#include "simulacao.h"
#include "ordenacao.h"

#include <stdlib.h>
#include <stdint.h>

/**
 * Gera um número pseudo-aleatório usando o algoritmo xorshift32.
 * Retorna um número inteiro de 32 bits.
 */
static uint32_t xorshift32(void) {
    static uint32_t state = 12345;
    uint32_t x = state;
    
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    
    state = x;
    return x;
}

/**
 * Sorteia um evento que ocorre com probabilidade de "prob" por cento (0 a 100).
 * Retorna 1 (sucesso) ou 0 (fracasso).
 */
static int sorteia(int prob) {
    int valor_sorteado = (int)(xorshift32() % 100u);
    return valor_sorteado < prob;
}


/**
 * ==================================================================
 * FUNÇÕES DE SIMULAÇÃO
 * ==================================================================
 */

/**
 * Registra um evento no histórico da simulação a partir dos dados
 * fornecidos. O evento é empilhado na pilha de histórico.
 */
void registra_evento(Pilha *historico, Pessoa *pessoa, int dia, int estado_origem, int estado_final) {
    if(historico && pessoa) {
        Evento evento = criar_evento(get_id(pessoa), estado_origem, estado_final, dia);
        empilhar(historico, evento);
    }
}

void simular_epidemia(Parametros parametros, Lista *estado_1, 
    Lista *estado_2, Lista *estado_3, Lista *estado_4, 
    Lista *estado_5, Fila *fila_infectados, Pilha *historico) {
        
    // INFECÇÃO INICIAL NO DIA 0
    ordenar_lista_estado_1(estado_1);
    
    int qtd_infectados_dia0 = (int)((parametros.N * parametros.P) / 100.0f);
    for (int i = 0; i < qtd_infectados_dia0; i++) {
        if (!lista_eh_vazia(estado_1)) {
            Pessoa *p = lista_remove_inicio(estado_1);
            if (p) {
                enfileira(fila_infectados, p);
                registra_evento(historico, p, 0, 1, 2);
            }
        }
    }
    // Transfere a infecção inicial para o Estado 2 (começam a infectar no Dia 1)
    fase_fim_dia(estado_2, fila_infectados);

    // LAÇO DIÁRIO DA SIMULAÇÃO (Dias 0 a D-1)
    for (int d = 0; d < parametros.D; d++) {
        ordenar_lista_estado_1(estado_1);

        if (d >= parametros.R) {
            fase_vacinacao(parametros, estado_1, estado_5, historico, d);
        }

        fase_infeccao(estado_1, estado_2, fila_infectados, historico, parametros.L, d);
        fase_infeccao(estado_1, estado_3, fila_infectados, historico, parametros.K, d);

        // Evolução: Estado 3 primeiro, depois Estado 2
        fase_evolucao_estado_3(estado_1, estado_3, estado_4, historico, parametros.M, d);
        fase_evolucao_estado_2(estado_1, estado_2, estado_3, historico, parametros.F, d);

        fase_fim_dia(estado_2, fila_infectados);
    }
}

void fase_vacinacao(Parametros parametros, Lista *estado_1, Lista *estado_5, Pilha *historico, int dia) {
    if (dia < parametros.R) {
        return;
    }

    // Quantidade de vacinas disponibilizadas por dia
    int num_vacinas = parametros.N / parametros.Y;

    // Distribui as vacinas para os mais velhos do Estado 1
    for (int i = 0; i < num_vacinas; i++) {
        // Se não houver mais pessoas saudáveis no Estado 1, encerra a vacinação do dia
        if (lista_eh_vazia(estado_1)) {
            break;
        }

        // Remove a pessoa mais velha 
        Pessoa *pessoa = lista_remove_inicio(estado_1);

        if (pessoa != NULL) {
            // Insere no Estado 5
            lista_insere_inicio(estado_5, pessoa);

            // Registra o evento de vacinação no histórico
            registra_evento(historico, pessoa, dia, 1, 5);
        }
    }
}

void fase_infeccao(Lista *estado_1, Lista *estado_sup, Fila *fila_infectados, Pilha *historico, int probabilidade, int dia) {
        for (Celula *celula = get_lista_primeiro(estado_sup); celula != NULL; celula = get_celula_proximo(celula)) {
            if(sorteia(probabilidade)) {
                if(!lista_eh_vazia(estado_1)) {
                    Pessoa *pessoa = lista_remove_inicio(estado_1);

                    if(pessoa) {
                        enfileira(fila_infectados, pessoa);
                        registra_evento(historico, pessoa, dia, 1, 2);
                    }
                }
            }
        }
}

void fase_evolucao_estado_2(Lista *estado_1, Lista *estado_2, 
    Lista *estado_3, Pilha *historico, int probabilidade, int dia) {

    // Esvazia a lista do Estado 2 processando cada indivíduo
    while (!lista_eh_vazia(estado_2)) {
        Pessoa *pessoa = lista_remove_inicio(estado_2);
        if (!pessoa) continue;

        if (sorteia(probabilidade)) {
            // Avança para o Estado 3
            lista_insere_inicio(estado_3, pessoa);
            registra_evento(historico, pessoa, dia, 2, 3);
        } else {
            // Regride para o Estado 1
            lista_insere_inicio(estado_1, pessoa);
            registra_evento(historico, pessoa, dia, 2, 1);
        }
    }
}

void fase_evolucao_estado_3(Lista *estado_1, Lista *estado_3, 
    Lista *estado_4, Pilha *historico, int probabilidade, int dia) {

    // Esvazia a lista do Estado 3 processando cada indivíduo
    while (!lista_eh_vazia(estado_3)) {
        Pessoa *pessoa = lista_remove_inicio(estado_3);
        if (!pessoa) continue;

        if (sorteia(probabilidade)) {
            // Vai para o Estado 4
            lista_insere_inicio(estado_4, pessoa);
            registra_evento(historico, pessoa, dia, 3, 4);
        } else {
            // Cura e retorna ao Estado 1
            lista_insere_inicio(estado_1, pessoa);
            registra_evento(historico, pessoa, dia, 3, 1);
        }
    }
}

void fase_fim_dia(Lista *estado_2, Fila *fila_infectados) {

    // Retira cada novo infectado da fila e o insere na lista do Estado 2
    while (!fila_eh_vazia(fila_infectados)) {
        Pessoa *pessoa = desenfileira(fila_infectados);
        if (pessoa != NULL) {
            lista_insere_inicio(estado_2, pessoa);
        }
    }
}