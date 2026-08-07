# Detective Quest - Coleta de Pistas

Projeto desenvolvido em linguagem C para uma atividade da disciplina de Analise e Desenvolvimento de Sistemas.

## Objetivo

O objetivo deste programa e ampliar o mapa da mansao do projeto Detective Quest, adicionando pistas aos comodos e uma arvore binaria de busca para organizar as pistas coletadas.

Durante a exploracao, o jogador percorre a mansao a partir do Hall de entrada e escolhe os caminhos disponiveis. Sempre que uma sala possui uma pista, ela e adicionada automaticamente a arvore de pistas.

Ao final da exploracao, todas as pistas coletadas sao exibidas em ordem alfabetica.

## Conceitos utilizados

Neste exercicio foram aplicados os seguintes conceitos da linguagem C:
- `struct`
- arvore binaria
- arvore binaria de busca (BST)
- ponteiros
- alocacao dinamica com `malloc()`
- recursividade
- comparacao de strings com `strcmp()`
- modularizacao com funcoes
- liberacao de memoria com `free()`

## Estruturas usadas

A estrutura `Sala` representa os comodos da mansao:

```c
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;
```

A estrutura `PistaNode` representa cada pista armazenada na arvore binaria de busca:

```c
typedef struct PistaNode {
    char descricao[100];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;
```

## Funcionamento do programa

1. O mapa fixo da mansao e criado no `main()`.
2. Cada sala recebe um nome e pode possuir uma pista.
3. O jogador inicia a exploracao no Hall de entrada.
4. A opcao `e` leva para o caminho da esquerda.
5. A opcao `d` leva para o caminho da direita.
6. A opcao `s` encerra a exploracao.
7. Ao chegar a uma sala com pista, ela e inserida na BST.
8. Ao final, as pistas coletadas sao exibidas em ordem alfabetica.
9. A memoria das duas arvores e liberada com `free()`.

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
Cria dinamicamente uma sala com nome, pista e ponteiros para os caminhos.

### `inserirPista`
Insere uma pista na arvore binaria de busca, organizando os dados por ordem alfabetica.

### `explorarSalasComPistas`
Controla a navegacao do jogador pela mansao e registra as pistas encontradas.

### `exibirPistas`
Percorre a BST em ordem e exibe as pistas alfabeticamente.

### `liberarSalas`
Libera a memoria usada pela arvore da mansao.

### `liberarPistas`
Libera a memoria usada pela arvore de pistas.

## Codigo-fonte

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

typedef struct PistaNode {
    char descricao[100];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

Sala *criarSala(char nome[], char pista[]) {
    Sala *novaSala;

    novaSala = (Sala *) malloc(sizeof(Sala));

    if (novaSala == NULL) {
        printf("Erro ao alocar memoria para a sala.\n");
        exit(1);
    }

    strcpy(novaSala->nome, nome);
    strcpy(novaSala->pista, pista);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala;
}

void inserirPista(PistaNode **raiz, char descricao[]) {
    PistaNode *novo;

    if (*raiz == NULL) {
        novo = (PistaNode *) malloc(sizeof(PistaNode));

        if (novo == NULL) {
            printf("Erro ao alocar memoria para a pista.\n");
            exit(1);
        }

        strcpy(novo->descricao, descricao);
        novo->esquerda = NULL;
        novo->direita = NULL;
        *raiz = novo;
    } else if (strcmp(descricao, (*raiz)->descricao) < 0) {
        inserirPista(&((*raiz)->esquerda), descricao);
    } else {
        inserirPista(&((*raiz)->direita), descricao);
    }
}

void exibirPistas(PistaNode *raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->descricao);
        exibirPistas(raiz->direita);
    }
}

void explorarSalasComPistas(Sala *salaAtual, PistaNode **pistas) {
    char escolha;

    while (salaAtual != NULL) {
        printf("\nVoce esta em: %s\n", salaAtual->nome);

        if (strlen(salaAtual->pista) > 0) {
            printf("Pista encontrada: %s\n", salaAtual->pista);
            inserirPista(pistas, salaAtual->pista);
        } else {
            printf("Nenhuma pista encontrada neste comodo.\n");
        }

        printf("\nEscolha um caminho:\n");

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
            printf("\nExploracao encerrada.\n");
            break;
        } else {
            printf("\nOpcao invalida. Escolha e, d ou s.\n");
        }
    }
}

void liberarSalas(Sala *sala) {
    if (sala != NULL) {
        liberarSalas(sala->esquerda);
        liberarSalas(sala->direita);
        free(sala);
    }
}

void liberarPistas(PistaNode *raiz) {
    if (raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
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

    PistaNode *arvorePistas = NULL;

    hall = criarSala(
        "Hall de entrada",
        "Existe uma marca de barro proxima a porta principal."
    );

    salaDeEstar = criarSala(
        "Sala de estar",
        "Um relogio parou exatamente as 22 horas."
    );

    cozinha = criarSala(
        "Cozinha",
        "Foi encontrada uma faca limpa sobre a mesa."
    );

    biblioteca = criarSala(
        "Biblioteca",
        "Um livro sobre a familia desapareceu da estante."
    );

    jardim = criarSala(
        "Jardim",
        "Ha pegadas recentes perto das flores."
    );

    quarto = criarSala(
        "Quarto",
        "Uma janela estava aberta durante a noite."
    );

    porao = criarSala(
        "Porao",
        "Um bilhete menciona a palavra segredo."
    );

    hall->esquerda = salaDeEstar;
    hall->direita = cozinha;

    salaDeEstar->esquerda = biblioteca;
    salaDeEstar->direita = jardim;

    cozinha->direita = quarto;
    quarto->direita = porao;

    printf("====================================\n");
    printf("   DETECTIVE QUEST - COLETA DE PISTAS\n");
    printf("====================================\n");
    printf("\nA exploracao comeca no Hall de entrada.\n");

    explorarSalasComPistas(hall, &arvorePistas);

    printf("\n====================================\n");
    printf("       PISTAS COLETADAS\n");
    printf("====================================\n");

    if (arvorePistas == NULL) {
        printf("Nenhuma pista foi coletada.\n");
    } else {
        exibirPistas(arvorePistas);
    }

    liberarSalas(hall);
    liberarPistas(arvorePistas);

    return 0;
}
```

## Como compilar

Salve o codigo como:

```bash
detective_quest_aventureiro.c
```

Depois, no terminal do VS Code:

```bash
gcc detective_quest_aventureiro.c -Wall -Wextra -o detective_quest_aventureiro
```

Para executar:

```bash
./detective_quest_aventureiro
```

## Estrutura do projeto

```bash
projeto/
├── detective_quest_aventureiro.c
└── README.md
```

## Observacoes

- O mapa da mansao e fixo e criado manualmente no `main()`.
- As pistas sao inseridas na BST durante a exploracao.
- A exibicao em ordem usa o percurso esquerda, raiz e direita.
- O jogador pode sair da exploracao a qualquer momento usando `s`.
- As duas arvores sao liberadas com `free()` ao final do programa.
- O codigo utiliza somente caracteres sem acentuacao para evitar problemas de codificacao.

## Autor

Felipe de Lima
