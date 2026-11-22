#include "historico.h"

void inicializar_historico(Historico *h) {
    h->inicio = NULL;
    h->fim = NULL;
}

int inserir_movimentacao(Historico *h, Movimentacao dados) {
    Movimentacao *novo = (Movimentacao *) malloc(sizeof(Movimentacao));
    if (novo == NULL) {
        return 0; // Falha na alocação de memória
    }

    // Cópia segura dos dados
    strcpy(novo->acao, dados.acao);
    novo->id_equipamento = dados.id_equipamento;
    novo->protocolo_solicitacao = dados.protocolo_solicitacao;
    strcpy(novo->responsavel, dados.responsavel);
    novo->prox = NULL;

    // Encadeamento cronológico (sempre no final)
    if (h->inicio == NULL) {
        h->inicio = novo;
    } else {
        h->fim->prox = novo;
    }

    h->fim = novo;
    return 1;
}

void imprimir_historico(Historico *h) {
    if (h->inicio == NULL) {
        printf("Historico de movimentacoes vazio.\n");
        return;
    }

    Movimentacao *atual = h->inicio;
    int contador = 1;

    while (atual != NULL) {
        printf("%d. %s", contador, atual->acao);
        
        if (atual->id_equipamento > 0) {
            printf(" | equipamento %d", atual->id_equipamento);
        }
        if (strlen(atual->responsavel) > 0) {
            printf(" | %s", atual->responsavel);
        }
        if (atual->protocolo_solicitacao > 0) {
            printf(" | protocolo %d", atual->protocolo_solicitacao);
        }
        
        printf("\n");
        contador++;
        atual = atual->prox;
    }
}

void liberar_historico(Historico *h) {
    Movimentacao *atual = h->inicio;
    Movimentacao *removido;

    while (atual != NULL) {
        removido = atual;
        atual = atual->prox;
        free(removido);
    }

    h->inicio = NULL;
    h->fim = NULL;
}