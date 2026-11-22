#include "operacoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int empilhar_operacao(Operacao **topo, Operacao dados) {
    // Alocação
    Operacao *novo = (Operacao *) malloc(sizeof(Operacao));
    if (novo == NULL) { return 0; }


    strcpy(novo->descricao_acao, dados.descricao_acao);
    strcpy(novo->data, dados.data);

    // O novo empurra o topo para baixo
    novo->prox = *topo; 
    *topo = novo;       

    return 1;
}

int desempilhar_operacao(Operacao **topo) {
    // verifico se meu topo está vazio
    if (*topo == NULL) {
        return 0; 
    }

    // o  *removido vai segurar o meu topo atual 
    Operacao *removido = *topo;

    // o meu *topo vai descer para a gaveta de baixo
    *topo = removido->prox;
    
    //  liberaro a memória RAM
    free(removido);
    
    return 1;
}
void liberar_operacoes(Operacao **topo) {
    Operacao *atual = *topo;
    Operacao *removido;

    while (atual != NULL) {
        removido = atual;
        atual = atual->prox;
        free(removido);
    }

    *topo = NULL;
}
void imprimir_operacoes(Operacao *topo) {
    if (topo == NULL) {
        printf("Nenhuma operacao recente registrada.\n");
        return;
    }

    Operacao *atual = topo;
    int i = 1;
    while (atual != NULL) {
        printf("%d. [%s] %s\n", i, atual->data, atual->descricao_acao);
        i++;
        atual = atual->prox;
    }
}