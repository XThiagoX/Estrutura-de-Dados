#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *prox;
} No;

void insere_inicio(No **inicio, int valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = *inicio;
    *inicio = novo;
}

void exibe_lista(No *inicio) {
    printf("Lista: ");
    while (inicio != NULL) {
        printf("%d ", inicio->valor);
        inicio = inicio->prox;
    }
    printf("\n");
}

int main() {
    No *inicio = NULL;
    int opcao, valor;
    
    do {
        printf("\nEscolha uma opcao:\n");
        printf("1. Inserir no inicio\n");
        printf("2. Exibir lista\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                printf("\nDigite o valor a ser inserido: ");
                scanf("%d", &valor);
                insere_inicio(&inicio, valor);
                break;
            case 2:
                exibe_lista(inicio);
                break;
            case 0:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
    
    return 0;
    
}
