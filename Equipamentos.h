#ifndef EQUIPAMENTOS_H
#define EQUIPAMENTOS_H


// Estrutura do nó da Lista Encadeada (Equipamentos)
typedef struct Equipamento{
    int id;
    char descricao[50]; 
    struct Equipamento *prox;
} Equipamento;

// Protótipos das funções de equipamentos
int inserir_equipamento(Equipamento **inicio, Equipamento dados);
int buscar_equipamento(Equipamento *inicio, int id_procurado);
void imprimir_equipamentos(Equipamento *inicio);
void liberar_equipamentos(Equipamento **inicio);

#endif