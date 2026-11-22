#ifndef HISTORICO_H
#define HISTORICO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de cada movimentação concluída (Lista Simplesmente Encadeada)
typedef struct Movimentacao {
    char acao[30];              // Ex: "Emprestimo", "Devolucao", "Manutencao", "Cancelamento"
    int id_equipamento;         // ID do equipamento movimentado (0 se for cancelamento de fila)
    int protocolo_solicitacao;  // Protocolo relacionado (0 se não houver)
    char responsavel[50];       // Nome e matrícula do mineiro envolvido
    struct Movimentacao *prox;
} Movimentacao;

// Estrutura de controle (Gerente) para manter a ordem cronológica (inserção no fim)
typedef struct Historico {
    Movimentacao *inicio;
    Movimentacao *fim;
} Historico;

// Protótipos das funções do Histórico
void inicializar_historico(Historico *h);
int inserir_movimentacao(Historico *h, Movimentacao dados);
void imprimir_historico(Historico *h);
void liberar_historico(Historico *h);

#endif