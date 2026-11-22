#ifndef SOLICITACOES_H
#define SOLICITACOES_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da Fila 
typedef struct Solicitacao {
    int id_mineiro;
    int id_equipamento_desejado;
    struct Solicitacao *prox;
} Solicitacao;

// Controle da Fila 

typedef struct{
    Solicitacao *inicio; // Placa de onde as pessoas saem (são atendidas)
    Solicitacao *fim;    // Placa de onde as pessoas entram
} Fila;

// Protótipos das funções de solicitações
void inicializar_fila(Fila *f);
int enfileirar_solicitacao(Fila *f, Solicitacao dados);
int desenfileirar_solicitacao(Fila *f);
void imprimir_fila(Fila *f);
void liberar_fila(Fila *f);

#endif
