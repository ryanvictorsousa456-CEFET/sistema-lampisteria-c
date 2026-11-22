#ifndef OPERACOES_H
#define OPERACOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Operacao {
    char descricao_acao[100];
    char data[15];
    struct Operacao *prox; 
} Operacao;


int empilhar_operacao(Operacao **topo, Operacao dados);
int desempilhar_operacao(Operacao **topo);
void imprimir_operacoes(Operacao *topo);
void liberar_operacoes(Operacao **topo);


#endif