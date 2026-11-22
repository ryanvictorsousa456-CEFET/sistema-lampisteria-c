#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solicitacoes.h"



void inicializar_fila(Fila *f){
    f->inicio = NULL;
    f->fim = NULL;
}

int enfileirar_solicitacao(Fila *f, Solicitacao dados ){
Solicitacao *novo = (Solicitacao *)malloc(sizeof(Solicitacao));
if(novo == NULL){
    return 0;
}
novo->id_mineiro = dados.id_mineiro;
novo->id_equipamento_desejado = dados.id_equipamento_desejado;
novo->prox = NULL;

if(f->inicio == NULL){
    f->inicio = novo ; 
}else{
    f->fim->prox = novo ;  
}
f->fim = novo;
return 1;
}

int desenfileirar_solicitacao(Fila *f){
    if(f->inicio == NULL){
        return 0;
    }
    Solicitacao *removido = f->inicio;

    f->inicio = removido->prox;

    if(f->inicio == NULL){
        f->fim = NULL;
    }
    free(removido);
    return 1;
}
void liberar_fila(Fila *f) {
    Solicitacao *atual = f->inicio;
    Solicitacao *removido;

    while (atual != NULL) {
        removido = atual;
        atual = atual->prox;
        free(removido);
    }

    f->inicio = NULL;
    f->fim = NULL;
}
void imprimir_fila(Fila *f) {
    if (f->inicio == NULL) {
        printf("Fila de solicitacoes vazia.\n");
        return;
    }

    Solicitacao *atual = f->inicio;
    int pos = 1;
    while (atual != NULL) {
        printf("%d. Mineiro ID: %d | Equipamento desejado ID: %d\n",
               pos, atual->id_mineiro, atual->id_equipamento_desejado);
        pos++;
        atual = atual->prox;
    }
}