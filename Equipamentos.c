#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipamentos.h" 


          // INSERÇÃO ORDENADA (Crescente pelo ID)
int inserir_equipamento(Equipamento **inicio, Equipamento dados) {
    // Etapa 1: Alocação
    Equipamento *novo = (Equipamento *) malloc(sizeof(Equipamento));
    if (novo == NULL) {
        return 0; // Falha por falta de memória
    }

             //  Preenchimento dos dados
    novo->id = dados.id;
     strcpy(novo->descricao, dados.descricao); 
    novo->prox = NULL;

    // Etapa 3: Ligação na lista
            // a Lista vazia ou novo ID é o menor de todos (vai para o início)
    if (*inicio == NULL || dados.id < (*inicio)->id) {
        novo->prox = *inicio;
        *inicio = novo;
        return 1;
    }

                 //Caminhar pela lista para achar a posição no meio ou final
    Equipamento *atual = *inicio;
    while (atual->prox != NULL && atual->prox->id < novo->id) {
        atual = atual->prox;
    }

                   // Encaixa o novo equipamento na lista          
    novo->prox = atual->prox;
    atual->prox = novo;

    return 1;
}

                    // BUSCA DE EQUIPAMENTO
int buscar_equipamento(Equipamento *inicio, int id_procurado) {
    Equipamento *atual = inicio;

    // Roda até a lista acabar
    while (atual != NULL) {
        if (atual->id == id_procurado) {
            return 1; // Encontrou
        }
        atual = atual->prox; // coloca o atual dando um passo para o prox
    }

    return 0; //significa que  Não encontrou
}

         //  IMPRESSÃO DA LISTA
void imprimir_equipamentos(Equipamento *inicio) {
    Equipamento *atual = inicio;
    
    printf("\n--- LISTA DE EQUIPAMENTOS DISPONIVEIS ---\n");
    if (atual == NULL) {
        printf("A lista esta vazia.\n");
    }

    while (atual != NULL) {
        printf("Equipamento ID: %d\n", atual->id);
        atual = atual->prox;
    }
    printf("-----------------------------------------\n");
}

            // FAXINA (Liberação de Memória)
void liberar_equipamentos(Equipamento **inicio) {
    Equipamento *atual = *inicio;
    Equipamento *proximo;

    while (atual != NULL) {
        proximo = atual->prox; // Salva o próximo endereço
        free(atual);           // Destrói a gaveta atual
        atual = proximo;       // Pula para o endereço salvo
    }

    *inicio = NULL; // Zera a placa principal por segurança
}