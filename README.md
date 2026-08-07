# Detective Quest - Mapa da Mansao

Projeto desenvolvido em linguagem C para uma atividade da disciplina de Analise e Desenvolvimento de Sistemas.

## Objetivo

O objetivo deste programa e simular a exploracao de uma mansao representada por uma arvore binaria.

O jogador inicia no Hall de entrada e escolhe os caminhos disponiveis para a esquerda ou para a direita. A exploracao continua ate chegar a um comodo que nao possui novos caminhos.

## Conceitos utilizados

Neste exercicio foram aplicados os seguintes conceitos da linguagem C:
- `struct`
- arvore binaria
- ponteiros
- alocacao dinamica com `malloc()`
- funcoes
- estruturas condicionais
- exploracao interativa pelo terminal
- liberacao de memoria com `free()`

## Estrutura usada

Cada comodo da mansao e representado pela estrutura `Sala`:

```c
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;
```

Cada sala possui um nome e dois ponteiros, que podem apontar para os caminhos da esquerda e da direita.

## Funcionamento do programa

1. As salas sao criadas automaticamente usando a funcao `criarSala()`.
2. A arvore binaria e montada manualmente no codigo.
3. O jogador inicia a exploracao no Hall de entrada.
4. A opcao `e` leva para o caminho da esquerda.
5. A opcao `d` leva para o caminho da direita.
6. A opcao `s` encerra a exploracao.
7. A exploracao termina automaticamente quando o jogador chega a uma sala sem caminhos.
8. Ao final, a memoria utilizada pela arvore e liberada.

## Mapa da mansao

A arvore utilizada no programa possui a seguinte estrutura:

```text
                 Hall de entrada
                /               \
       Sala de estar           Cozinha
          /       \                 \
    Biblioteca   Jardim             Quarto
                                      \
                                      Porao
```

## Funcoes do programa

### `criarSala`
Cria uma nova sala usando alocacao dinamica de memoria e armazena seu nome.

### `explorarSalas`
Permite que o jogador navegue pela arvore escolhendo os caminhos disponiveis.

### `liberarSalas`
Libera a memoria dos nos da arvore ao final do programa.

### `main`
Cria as salas, monta o mapa da mansao e inicia a exploracao.

## Codigo-fonte

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

/* Cria uma nova sala usando alocacao dinamica. */
Sala *criarSala(char nome[]) {
    Sala *novaSala;

    novaSala = (Sala *) malloc(sizeof(Sala));

    if (novaSala == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala;
}

/* Permite que o jogador explore a arvore binaria. */
void explorarSalas(Sala *salaAtual) {
    char escolha;

    while (salaAtual != NULL) {
        printf("\nVoce esta em: %s\n", salaAtual->nome);

        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Este comodo nao possui mais caminhos.\n");
            printf("Fim da exploracao.\n");
            break;
        }

        printf("Escolha um caminho:\n");

        if (salaAtual->esquerda != NULL) {
            printf("e - Ir para a esquerda\n");
        }

        if (salaAtual->direita != NULL) {
            printf("d - Ir para a direita\n");
        }

        printf("s - Sair da exploracao\n");
        printf("Opcao: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' || escolha == 'E') {
            if (salaAtual->esquerda != NULL) {
                salaAtual = salaAtual->esquerda;
            } else {
                printf("Nao existe caminho para a esquerda.\n");
            }
        } else if (escolha == 'd' || escolha == 'D') {
            if (salaAtual->direita != NULL) {
                salaAtual = salaAtual->direita;
            } else {
                printf("Nao existe caminho para a direita.\n");
            }
        } else if (escolha == 's' || escolha == 'S') {
            printf("\nExploracao encerrada pelo jogador.\n");
            break;
        } else {
            printf("\nOpcao invalida. Escolha e, d ou s.\n");
        }
    }
}

/* Libera a memoria dos nos da arvore. */
void liberarSalas(Sala *sala) {
    if (sala != NULL) {
        liberarSalas(sala->esquerda);
        liberarSalas(sala->direita);
        free(sala);
    }
}

int main() {
    Sala *hall;
    Sala *salaDeEstar;
    Sala *cozinha;
    Sala *biblioteca;
    Sala *jardim;
    Sala *quarto;
    Sala *porao;

    /* Criacao das salas da mansao. */
    hall = criarSala("Hall de entrada");
    salaDeEstar = criarSala("Sala de estar");
    cozinha = criarSala("Cozinha");
    biblioteca = criarSala("Biblioteca");
    jardim = criarSala("Jardim");
    quarto = criarSala("Quarto");
    porao = criarSala("Porao");

    /* Montagem manual da arvore binaria. */
    hall->esquerda = salaDeEstar;
    hall->direita = cozinha;

    salaDeEstar->esquerda = biblioteca;
    salaDeEstar->direita = jardim;

    cozinha->direita = quarto;
    quarto->direita = porao;

    printf("====================================\n");
    printf("       DETECTIVE QUEST - MANSAO\n");
    printf("====================================\n");
    printf("\nA exploracao comeca no Hall de entrada.\n");

    explorarSalas(hall);

    liberarSalas(hall);

    return 0;
}
```

## Como compilar

No terminal, use:

```bash
gcc detective_quest.c -o detective_quest
```

Para executar o programa:

```bash
./detective_quest
```

## Estrutura do projeto

```bash
projeto/
├── detective_quest.c
└── README.md
```

## Observacoes

- A arvore e criada manualmente no codigo, conforme solicitado no desafio.
- O jogador nao cadastra novas salas durante a execucao.
- A exploracao comeca sempre no Hall de entrada.
- A opcao `e` representa o caminho da esquerda.
- A opcao `d` representa o caminho da direita.
- A opcao `s` encerra a exploracao.
- O programa usa `malloc()` para criar as salas e `free()` para liberar a memoria.
- O codigo utiliza apenas caracteres sem acentuacao para evitar problemas de codificacao no terminal e no GitHub.

## Autor

Felipe de Lima
