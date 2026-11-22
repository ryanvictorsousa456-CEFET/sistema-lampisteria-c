#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Equipamentos.h"
#include "Solicitacoes.h"
#include "Operacoes.h"
#include "historico.h"
#include "arquivos.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ler_texto(char *destino, int tamanho) {
    if (fgets(destino, tamanho, stdin) != NULL) {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        }
    }
}

void registrar_op(Operacao **topo, const char *desc, const char *data) {
    Operacao op;
    strcpy(op.descricao_acao, desc);
    strcpy(op.data, data);
    op.prox = NULL;
    empilhar_operacao(topo, op);
}

void registrar_hist(Historico *h, const char *acao, int id_eq, int prot, const char *resp) {
    Movimentacao mov;
    strcpy(mov.acao, acao);
    mov.id_equipamento = id_eq;
    mov.protocolo_solicitacao = prot;
    strcpy(mov.responsavel, resp);
    mov.prox = NULL;
    inserir_movimentacao(h, mov);
}

int main() {
    Equipamento *lista_equipamentos = NULL;
    Fila fila_solicitacoes;
    Operacao *pilha_operacoes = NULL;
    Historico historico_mov;

    inicializar_fila(&fila_solicitacoes);
    inicializar_historico(&historico_mov);

    int opcao = -1;
    int proximo_protocolo = 1;
    char log_buffer[100];
    char resp_buffer[50];

    do {
        printf("\n================ CONTROLE DA LAMPISTERIA ================\n");
        printf("1.  Cadastrar equipamento\n");
        printf("2.  Listar equipamentos\n");
        printf("3.  Buscar equipamento\n");
        printf("4.  Registrar solicitacao\n");
        printf("5.  Listar solicitacoes pendentes\n");
        printf("6.  Atender proxima solicitacao\n");
        printf("7.  Registrar devolucao\n");
        printf("8.  Alterar manutencao\n");
        printf("9.  Cancelar solicitacao\n");
        printf("10. Mostrar estado do sistema\n");
        printf("11. Salvar dados\n");
        printf("12. Carregar dados\n");
        printf("0.  Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Erro: entrada invalida.\n");
            limpar_buffer();
            opcao = -1;
            continue;
        }
        limpar_buffer();

        switch (opcao) {
            case 1: { // CADASTRAR EQUIPAMENTO
                Equipamento novo;
                printf("Identificador (ID inteiro): ");
                scanf("%d", &novo.id);
                limpar_buffer();

                if (buscar_equipamento(lista_equipamentos, novo.id) == 1) {
                    printf("Erro: ja existe equipamento com identificador %d.\n", novo.id);
                    break;
                }

                printf("Descricao (ex: Lanterna - Disponivel): ");
                ler_texto(novo.descricao, sizeof(novo.descricao));
                novo.prox = NULL;

                if (inserir_equipamento(&lista_equipamentos, novo)) {
                    printf("Equipamento %d cadastrado.\n", novo.id);
                    sprintf(log_buffer, "Cadastro do equipamento %d", novo.id);
                    registrar_op(&pilha_operacoes, log_buffer, "Turno Atual");
                } else {
                    printf("Erro ao alocar memoria para o equipamento.\n");
                }
                break;
            }

            case 2: { // LISTAR EQUIPAMENTOS
                imprimir_equipamentos(lista_equipamentos);
                break;
            }

            case 3: { // BUSCAR EQUIPAMENTO
                int id_busca;
                printf("Digite o ID do equipamento: ");
                scanf("%d", &id_busca);
                limpar_buffer();

                if (buscar_equipamento(lista_equipamentos, id_busca) == 1) {
                    Equipamento *atual = lista_equipamentos;
                    while (atual != NULL) {
                        if (atual->id == id_busca) {
                            printf("Encontrado -> ID: %d | Descricao: %s\n", atual->id, atual->descricao);
                            break;
                        }
                        atual = atual->prox;
                    }
                } else {
                    printf("Erro: equipamento %d nao encontrado.\n", id_busca);
                }
                break;
            }

            case 4: { // REGISTRAR SOLICITACAO
                Solicitacao nova_sol;
                printf("ID (matricula) do mineiro: ");
                scanf("%d", &nova_sol.id_mineiro);
                limpar_buffer();

                printf("ID do equipamento desejado: ");
                scanf("%d", &nova_sol.id_equipamento_desejado);
                limpar_buffer();

                nova_sol.prox = NULL;

                if (enfileirar_solicitacao(&fila_solicitacoes, nova_sol)) {
                    int prot = proximo_protocolo++;
                    printf("Solicitacao registrada. Protocolo: %d.\n", prot);
                    sprintf(log_buffer, "Solicitacao prot %d (Mineiro %d -> Eq %d)",
                            prot, nova_sol.id_mineiro, nova_sol.id_equipamento_desejado);
                    registrar_op(&pilha_operacoes, log_buffer, "Turno Atual");
                } else {
                    printf("Erro ao registrar solicitacao.\n");
                }
                break;
            }

            case 5: { // LISTAR SOLICITACOES PENDENTES
                imprimir_fila(&fila_solicitacoes);
                break;
            }

            case 6: { // ATENDER PROXIMA SOLICITACAO
                if (fila_solicitacoes.inicio == NULL) {
                    printf("Fila de solicitacoes vazia.\n");
                    break;
                }

                int id_mineiro_at = fila_solicitacoes.inicio->id_mineiro;
                int id_eq_at = fila_solicitacoes.inicio->id_equipamento_desejado;

                if (buscar_equipamento(lista_equipamentos, id_eq_at) == 1) {
                    desenfileirar_solicitacao(&fila_solicitacoes);

                    printf("Solicitacao atendida: Mineiro %d recebeu equipamento %d.\n",
                           id_mineiro_at, id_eq_at);

                    sprintf(log_buffer, "Emprestimo eq %d ao mineiro %d", id_eq_at, id_mineiro_at);
                    registrar_op(&pilha_operacoes, log_buffer, "Turno Atual");

                    sprintf(resp_buffer, "Mineiro %d", id_mineiro_at);
                    registrar_hist(&historico_mov, "Emprestimo", id_eq_at, 0, resp_buffer);
                } else {
                    int escolha;
                    printf("Equipamento %d indisponivel no momento.\n", id_eq_at);
                    printf("(1) Manter no inicio  (2) Recolocar no final  (3) Cancelar: ");
                    scanf("%d", &escolha);
                    limpar_buffer();

                    if (escolha == 1) {
                        printf("Solicitacao mantida no inicio da fila.\n");
                    } else if (escolha == 2) {
                        Solicitacao movida;
                        movida.id_mineiro = id_mineiro_at;
                        movida.id_equipamento_desejado = id_eq_at;
                        movida.prox = NULL;

                        desenfileirar_solicitacao(&fila_solicitacoes);
                        enfileirar_solicitacao(&fila_solicitacoes, movida);
                        printf("Solicitacao recolocada no final da fila.\n");
                    } else if (escolha == 3) {
                        desenfileirar_solicitacao(&fila_solicitacoes);
                        printf("Solicitacao cancelada.\n");

                        sprintf(resp_buffer, "Mineiro %d", id_mineiro_at);
                        registrar_hist(&historico_mov, "Cancelamento", id_eq_at, 0, resp_buffer);
                    }
                }
                break;
            }

            case 7: { // REGISTRAR DEVOLUCAO
                int id_dev, id_min;
                printf("ID do equipamento devolvido: ");
                scanf("%d", &id_dev);
                limpar_buffer();

                printf("ID (matricula) do mineiro que devolveu: ");
                scanf("%d", &id_min);
                limpar_buffer();

                if (buscar_equipamento(lista_equipamentos, id_dev) == 1) {
                    printf("Devolucao do equipamento %d registrada.\n", id_dev);
                    sprintf(log_buffer, "Devolucao eq %d (Mineiro %d)", id_dev, id_min);
                    registrar_op(&pilha_operacoes, log_buffer, "Turno Atual");

                    sprintf(resp_buffer, "Mineiro %d", id_min);
                    registrar_hist(&historico_mov, "Devolucao", id_dev, 0, resp_buffer);
                } else {
                    printf("Erro: equipamento %d nao encontrado.\n", id_dev);
                }
                break;
            }

            case 8: { // ALTERAR MANUTENCAO
                int id_man;
                printf("ID do equipamento para alterar status de manutencao: ");
                scanf("%d", &id_man);
                limpar_buffer();

                if (buscar_equipamento(lista_equipamentos, id_man) == 1) {
                    printf("Status de manutencao do equipamento %d atualizado.\n", id_man);
                    sprintf(log_buffer, "Alteracao de manutencao eq %d", id_man);
                    registrar_op(&pilha_operacoes, log_buffer, "Turno Atual");
                    registrar_hist(&historico_mov, "Manutencao", id_man, 0, "Lampisteria");
                } else {
                    printf("Erro: equipamento %d nao encontrado.\n", id_man);
                }
                break;
            }

            case 9: { // CANCELAR PRIMEIRA SOLICITACAO DA FILA
                if (fila_solicitacoes.inicio == NULL) {
                    printf("Fila de solicitacoes vazia.\n");
                } else {
                    int id_min = fila_solicitacoes.inicio->id_mineiro;
                    int id_eq = fila_solicitacoes.inicio->id_equipamento_desejado;

                    desenfileirar_solicitacao(&fila_solicitacoes);
                    printf("Solicitacao do mineiro %d (eq %d) cancelada.\n", id_min, id_eq);

                    sprintf(log_buffer, "Cancelamento solicitacao mineiro %d", id_min);
                    registrar_op(&pilha_operacoes, log_buffer, "Turno Atual");

                    sprintf(resp_buffer, "Mineiro %d", id_min);
                    registrar_hist(&historico_mov, "Cancelamento", id_eq, 0, resp_buffer);
                }
                break;
            }

            case 10: { // MOSTRAR ESTADO DO SISTEMA
                printf("\n=== Equipamentos ===\n");
                imprimir_equipamentos(lista_equipamentos);

                printf("\n=== Fila de solicitacoes ===\n");
                imprimir_fila(&fila_solicitacoes);

                printf("\n=== Operacoes recentes (topo primeiro) ===\n");
                imprimir_operacoes(pilha_operacoes);

                printf("\n=== Historico de movimentacoes ===\n");
                imprimir_historico(&historico_mov);
                break;
            }

            case 11: { // SALVAR DADOS
                int ok_eq = salvar_equipamentos("equipamentos.bin", lista_equipamentos);
                int ok_hist = salvar_historico("historico.bin", &historico_mov);

                if (ok_eq && ok_hist) {
                    printf("Dados salvos com sucesso em equipamentos.bin e historico.bin.\n");
                } else {
                    printf("Erro ao salvar arquivos binarios.\n");
                }
                break;
            }

            case 12: { // CARREGAR DADOS
                lista_equipamentos = carregar_equipamentos("equipamentos.bin", lista_equipamentos);
                int ok_hist = carregar_historico("historico.bin", &historico_mov);

                if (lista_equipamentos != NULL || ok_hist) {
                    printf("Dados carregados com sucesso.\n");
                } else {
                    printf("Nenhum dado encontrado ou erro ao abrir arquivos.\n");
                }
                break;
            }

            case 0: { // SAIR
                char resp;
                printf("Deseja salvar antes de sair? (s/n): ");
                scanf(" %c", &resp);
                limpar_buffer();

                if (resp == 's' || resp == 'S') {
                    salvar_equipamentos("equipamentos.bin", lista_equipamentos);
                    salvar_historico("historico.bin", &historico_mov);
                    printf("Dados salvos.\n");
                }

                liberar_equipamentos(&lista_equipamentos);
                liberar_fila(&fila_solicitacoes);
                liberar_operacoes(&pilha_operacoes);
                liberar_historico(&historico_mov);

                printf("Memoria liberada. Encerrando...\n");
                break;
            }

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}