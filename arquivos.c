#include "arquivos.h"


int salvar_equipamentos(const char *nome_arquivo, Equipamento *inicio) {
    FILE *arq = fopen(nome_arquivo, "wb");
    if (arq == NULL) {
        return 0;
    }

    Equipamento *atual = inicio;
    while (atual != NULL) {
        fwrite(atual, sizeof(Equipamento), 1, arq);
        atual = atual->prox;
    }

    fclose(arq);
    return 1;
}

Equipamento* carregar_equipamentos(const char *nome_arquivo, Equipamento *inicio_atual) {
    // Libera a lista existente antes de carregar os dados do disco
    liberar_equipamentos(&inicio_atual);

    FILE *arq = fopen(nome_arquivo, "rb");
    if (arq == NULL) {
        return NULL;
    }

    Equipamento temp;
    while (fread(&temp, sizeof(Equipamento), 1, arq) == 1) {
        temp.prox = NULL; // Descarta o ponteiro antigo salvo no arquivo
        inserir_equipamento(&inicio_atual, temp);
    }

    fclose(arq);
    return inicio_atual;
}

// ====================================================
// HISTÓRICO DE MOVIMENTAÇÕES
// ====================================================

int salvar_historico(const char *nome_arquivo, Historico *h) {
    FILE *arq = fopen(nome_arquivo, "wb");
    if (arq == NULL) {
        return 0;
    }

    Movimentacao *atual = h->inicio;
    while (atual != NULL) {
        fwrite(atual, sizeof(Movimentacao), 1, arq);
        atual = atual->prox;
    }

    fclose(arq);
    return 1;
}

int carregar_historico(const char *nome_arquivo, Historico *h) {
    // Libera o histórico em memória antes de reconstruir
    liberar_historico(h);

    FILE *arq = fopen(nome_arquivo, "rb");
    if (arq == NULL) {
        return 0;
    }

    Movimentacao temp;
    while (fread(&temp, sizeof(Movimentacao), 1, arq) == 1) {
        temp.prox = NULL; // Descarta o endereço de memória antigo
        inserir_movimentacao(h, temp);
    }

    fclose(arq);
    return 1;
}