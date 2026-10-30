#include "simulação.h"
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
        Evento evento = criar_evento(get_id(pessoa), dia, estado_origem, estado_final);
        empilhar(historico, evento);
    }
}

void simular_epidemia(Parametros parametros, Lista *estado_1, 
    Lista *estado_2, Lista *estado_3, Lista *estado_4, 
    Lista *estado_5, Fila *fila_infectados, Pilha *historico) {
        for(int d = 0; d < parametros.D; d++) {
            if(d >= parametros.R) {
                fase_vacinacao(
                    parametros, 
                    estado_1, 
                    estado_2, 
                    estado_3, 
                    estado_4, 
                    estado_5, 
                    fila_infectados, 
                    historico
                );
            }

            fase_infeccao(
                estado_1, 
                estado_2, 
                fila_infectados, 
                historico,
                parametros.L,
                d
            );

            fase_infeccao(
                estado_1, 
                estado_3, 
                fila_infectados, 
                historico,
                parametros.K,
                d
            );

            fase_evolucao_estado_2(
                parametros, 
                estado_1, 
                estado_2, 
                estado_3, 
                historico,
                parametros.F,
                d
            );

            fase_evolucao_estado_3(
                parametros, 
                estado_1, 
                estado_3, 
                estado_4, 
                historico,
                parametros.M,
                d
            );

            fase_fim_dia(
                parametros, 
                estado_1, 
                estado_2, 
                estado_3, 
                estado_4, 
                estado_5, 
                fila_infectados, 
                historico
            );
        }
}

void fase_vacinacao(Parametros parametros, Lista *estado_1, Lista *estado_2, 
    Lista *estado_3, Lista *estado_4, Lista *estado_5, Fila *fila_infectados, Pilha *historico) {

}

void fase_infeccao(Lista *estado_1, Lista *estado_sup, Fila *fila_infectados, Pilha *historico, int probabilidade, int dia) {
        for(Celula *celula = estado_sup->cabeca; celula != NULL; celula = celula->prox) {
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

void fase_evolucao_estado_2(Parametros parametros, Lista *estado_1, Lista *estado_2, 
    Lista *estado_3, Pilha *historico, int probabilidade, int dia) {

}

void fase_evolucao_estado_3(Parametros parametros, Lista *estado_1, Lista *estado_3, 
    Lista *estado_4, Pilha *historico, int probabilidade, int dia) {

}

void fase_fim_dia(Parametros parametros, Lista *estado_1, Lista *estado_2, 
    Lista *estado_3, Lista *estado_4, Lista *estado_5, Fila *fila_infectados, Pilha *historico) {

}