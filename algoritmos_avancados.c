#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

/*
 * Cria uma nova sala usando alocacao dinamica.
 */
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

/*
 * Permite que o jogador explore a arvore
 * escolhendo os caminhos da esquerda ou da direita.
 */
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

/*
 * Libera a memoria dos nos da arvore.
 */
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
    Sala *porão;

    /*
     * Criacao das salas da mansao.
     */
    hall = criarSala("Hall de entrada");
    salaDeEstar = criarSala("Sala de estar");
    cozinha = criarSala("Cozinha");
    biblioteca = criarSala("Biblioteca");
    jardim = criarSala("Jardim");
    quarto = criarSala("Quarto");
    porão = criarSala("Porao");

    /*
     * Montagem manual da arvore binaria.
     *
     *                 Hall
     *                /    \
     *       Sala de estar  Cozinha
     *          /    \          \
     *   Biblioteca Jardim     Quarto
     *                              \
     *                              Porao
     */
    hall->esquerda = salaDeEstar;
    hall->direita = cozinha;

    salaDeEstar->esquerda = biblioteca;
    salaDeEstar->direita = jardim;

    cozinha->direita = quarto;
    quarto->direita = porão;

    printf("====================================\n");
    printf("     DETECTIVE QUEST - MANSÃO\n");
    printf("====================================\n");
    printf("\nA exploracao comeca no Hall de entrada.\n");

    explorarSalas(hall);

    liberarSalas(hall);

    return 0;
}
