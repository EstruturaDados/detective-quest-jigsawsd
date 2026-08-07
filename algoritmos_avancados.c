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

/*
 * Cria dinamicamente uma sala da mansao.
 * A sala pode receber uma pista ou ficar sem pista.
 */
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

/*
 * Insere uma nova pista na arvore binaria de busca.
 * A organizacao e feita em ordem alfabetica.
 */
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

/*
 * Exibe as pistas em ordem alfabetica.
 * O percurso em ordem visita esquerda, raiz e direita.
 */
void exibirPistas(PistaNode *raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->descricao);
        exibirPistas(raiz->direita);
    }
}

/*
 * Permite a exploracao da mansao.
 * Quando uma sala possui pista, ela e inserida na BST.
 */
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

/*
 * Libera a memoria usada pela arvore da mansao.
 */
void liberarSalas(Sala *sala) {
    if (sala != NULL) {
        liberarSalas(sala->esquerda);
        liberarSalas(sala->direita);
        free(sala);
    }
}

/*
 * Libera a memoria usada pela arvore de pistas.
 */
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

    /*
     * Criacao das salas da mansao.
     * Algumas salas possuem pistas e outras nao.
     */
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

    /*
     * Montagem manual da arvore binaria da mansao.
     *
     *                 Hall de entrada
     *                /               \
     *       Sala de estar           Cozinha
     *          /       \                 \
     *    Biblioteca   Jardim             Quarto
     *                                      \
     *                                      Porao
     */
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
