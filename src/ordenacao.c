#include "ordenacao.h"
#include <stdlib.h>

void ordenar_lista_estado_1(Lista *lista) {
    if (!lista || lista_eh_vazia(lista)) return;

    // aponta para a célula anterior ao elemento de avaliacao
    Celula *ant_atual = get_lista_primeiro(lista);
    if (!ant_atual) return;

    // Percorre cada elemento a ser ajustado na lista
    while (get_celula_proximo(ant_atual) != NULL) {
        Celula *atual = get_celula_proximo(ant_atual);
        Pessoa *pessoa_atual = get_celula_get_pessoa(atual);

        Celula *ant_busca = NULL;
        Celula *no_busca = get_lista_primeiro(lista);

        // Procura a posição correta de inserção do início até a posição de 'atual'
        while (no_busca != atual && verifica_prioridade(get_celula_get_pessoa(no_busca), pessoa_atual) == 0) {
            ant_busca = no_busca;
            no_busca = get_celula_proximo(no_busca);
        }

        // Significa que a pessoa deve ser movida para trás
        if (no_busca != atual) {
            Pessoa *pessoa_movida = lista_remove_apos(lista, ant_atual);

            if (ant_busca == NULL) {
                // Insere no início da lista 
                lista_insere_inicio(lista, pessoa_movida);
            } else {
                // Insere logo após a célula de busca
                lista_insere_apos(lista, ant_busca, pessoa_movida);
            }
        } else {
            // Se já está na posição certa, avança para a próxima célula
            ant_atual = get_celula_proximo(ant_atual);
        }
    }
}