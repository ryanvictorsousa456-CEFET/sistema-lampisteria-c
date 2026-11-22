#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <stdio.h>
#include <stdlib.h>
#include "equipamentos.h"
#include "historico.h"

// Persistência de Equipamentos
int salvar_equipamentos(const char *nome_arquivo, Equipamento *inicio);
Equipamento* carregar_equipamentos(const char *nome_arquivo, Equipamento *inicio_atual);

// Persistência do Histórico de Movimentações
int salvar_historico(const char *nome_arquivo, Historico *h);
int carregar_historico(const char *nome_arquivo, Historico *h);

#endif