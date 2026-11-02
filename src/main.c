#include <stdio.h>
#include <stdlib.h>

#include "simulacao.h"

int main() {
    Parametros parametros;

    // Leitura dos 9 parâmetros da 1ª linha
    if (scanf("%d %f %f %f %f %f %d %d %d", 
              &parametros.N, &parametros.P, &parametros.L, &parametros.K, 
              &parametros.F, &parametros.M, &parametros.D, &parametros.R, 
              &parametros.Y) != 9) {
        return 1;
    }

    // Alocação zera-memória (calloc) do cadastro original
    Pessoa **cadastro_original = calloc(parametros.N, sizeof(Pessoa *));
    if (!cadastro_original) return 1;

    int lidos = 0;
    for (int i = 0; i < parametros.N; i++) {
        char nome[100];
        int id, idade;
        if (scanf("%99s %d %d", nome, &id, &idade) == 3) {
            cadastro_original[i] = pessoa_cria(nome, id, idade);
            lidos++;
        } else {
            break; // Interrompe caso o arquivo termine antes de N
        }
    }
    parametros.N = lidos; 

    double soma_est1 = 0, soma_est2 = 0, soma_est3 = 0, soma_est4 = 0, soma_est5 = 0;

    for (int rep = 0; rep < I; rep++) {
        Lista *estado_1 = lista_inicia();
        Lista *estado_2 = lista_inicia();
        Lista *estado_3 = lista_inicia();
        Lista *estado_4 = lista_inicia();
        Lista *estado_5 = lista_inicia();

        Fila *fila_infectados = fila_inicia();
        Pilha *historico = pilha_inicia();

        // Popula Estado 1 com cópias
        for (int i = 0; i < parametros.N; i++) {
            if (cadastro_original[i]) {
                Pessoa *p_copia = pessoa_copia(cadastro_original[i]);
                lista_insere_inicio(estado_1, p_copia);
            }
        }

        // Executa simulação
        simular_epidemia(
            parametros, 
            estado_1, 
            estado_2, 
            estado_3, 
            estado_4, 
            estado_5, 
            fila_infectados, 
            historico
        );

        // Somatório dos estados ao fim de D dias
        soma_est1 += lista_tamanho(estado_1);
        soma_est2 += lista_tamanho(estado_2);
        soma_est3 += lista_tamanho(estado_3);
        soma_est4 += lista_tamanho(estado_4);
        soma_est5 += lista_tamanho(estado_5);

        // Desalocação segura da simulação atual
        lista_libera_com_pessoas(estado_1);
        lista_libera_com_pessoas(estado_2);
        lista_libera_com_pessoas(estado_3);
        lista_libera_com_pessoas(estado_4);
        lista_libera_com_pessoas(estado_5);

        fila_libera(fila_infectados);
        pilha_libera(historico);
    }

    // Liberação do cadastro base
    for (int i = 0; i < parametros.N; i++) {
        if (cadastro_original[i]) {
            pessoa_libera(cadastro_original[i]);
        }
    }
    free(cadastro_original);

    double total_amostras = (double)I * parametros.N;
    if (total_amostras > 0) {
        printf("Estado 1: %.2f%%\n", (soma_est1 / total_amostras) * 100.0);
        printf("Estado 2: %.2f%%\n", (soma_est2 / total_amostras) * 100.0);
        printf("Estado 3: %.2f%%\n", (soma_est3 / total_amostras) * 100.0);
        printf("Estado 4: %.2f%%\n", (soma_est4 / total_amostras) * 100.0);
        printf("Estado 5: %.2f%%\n", (soma_est5 / total_amostras) * 100.0);
    }

    return 0;
}