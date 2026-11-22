# Sistema de Controle da Lampisteria

**Disciplina:** INTRODUÇÃO A PROGRAMAÇÃO DE COMPUTADORES
**Instituição:** UFCIMG — Engenharia de Computação  
**Autor(es):** Ryan Víctor De Sousa Costa

---

## Sobre o Projeto

Sistema desenvolvido em linguagem C para gerenciar o controle de equipamentos de uma lampisteria de mineração. O software controla todo o ciclo operacional de empréstimos, devoluções, manutenções e fila de atendimento dos mineiros, utilizando alocação dinâmica de memória e persistência de dados em arquivos binários.

---

## Arquitetura e Estruturas de Dados

O projeto foi modularizado em cabeçalhos (`.h`) e implementações (`.c`), aplicando a estrutura de dados mais adequada para cada responsabilidade:

| Módulo | Estrutura de Dados | Justificativa Técnica |
| :--- | :--- | :--- |
| **`Equipamentos.h / .c`** | Lista Encadeada Simples (Ordenada) | Permite crescimento dinâmico do inventário e mantém os equipamentos sempre ordenados pelo ID, evitando duplicidades. |
| **`Solicitacoes.h / .c`** | Fila (FIFO - *First In, First Out*) | Garante justiça no atendimento: o primeiro mineiro a solicitar um equipamento é o primeiro a ser atendido. |
| **`Operacoes.h / .c`** | Pilha (LIFO - *Last In, First Out*) | Armazena o log das ações do turno atual, mantendo sempre a operação mais recente no topo para consulta rápida. |
| **`historico.h / .c`** | Lista Duplamente Encadeada | Registra de forma permanente todas as movimentações (empréstimos, devoluções, manutenções e cancelamentos). |
| **`arquivos.h / .c`** | Arquivos Binários (`fread` / `fwrite`) | Salva e restaura o estado do inventário (`equipamentos.bin`) e do histórico (`historico.bin`) entre execuções. |
| **`main.c`** | Controlador / Menu Interativo | Integra todos os módulos, valida entradas do usuário e gerencia o ciclo de vida da memória. |

---

## Como Compilar e Executar

### Pré-requisitos
- Compilador **GCC** (MinGW / MSYS2 no Windows ou GCC padrão no Linux).

### Compilação
Abra o terminal (CMD, PowerShell ou Bash) dentro da pasta do projeto e execute:

cd /d "C:\Users\Ryan\OneDrive\trabalho Guido 2" && gcc -Wall -Wextra main.c Equipamentos.c Solicitacoes.c Operacoes.c historico.c arquivos.c -o lampisteria && lampisteria.exe

