#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct NoA {
    char info;
    struct NoA *esq;
    struct NoA *dir;
} TNoA;

void imprime(TNoA *nodo, int tab) {
    for (int i = 0; i < tab; i++) {
        printf("-");
    }
    if (nodo != NULL) {
        printf("%c\n", nodo->info);
        imprime(nodo->esq, tab + 2);
        printf("\n");
        imprime(nodo->dir, tab + 2);
    } else printf("vazio");
}

TNoA *criaNo(char ch) {
    TNoA *novo;
    novo = (TNoA *) malloc(sizeof(TNoA));
    novo->info = ch;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

int full(TNoA *no){

    // caso base - arvore nula
    if (no == NULL)
    {
        return 1;
    }


    // verifica se a arvore tem 2 ou 0 filhos
    if (no->esq == NULL && no->dir == NULL)
    {
        return 1;
    }
    else if (no->esq != NULL && no->dir != NULL)
    {
        
        return full(no->esq) && full(no->dir);
    }
    else{
        return 0;
    }        
}

int main(void) {
    TNoA *raiz;
    raiz = criaNo('A');
    raiz->esq = criaNo('B');
    raiz->dir = criaNo('C');
    raiz->dir->esq = criaNo('D');
    raiz->dir->dir = criaNo('E');
    imprime(raiz, 0);
    printf("\n");

    printf("%d", full(raiz));
};