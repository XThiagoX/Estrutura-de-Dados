#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNoA {
    int chave;
    struct sNoA *esq;
    struct sNoA *dir;
} TNoA;


TNoA *menor(TNoA *no) {      
    TNoA *menorNo = no;
    if (no->esq != NULL)
    {        
        TNoA *menorEsquerda = menor(no->esq);
        if (menorEsquerda->chave < menorNo->chave)
        {
            menorNo = menorEsquerda;
        }        
    }
    if (no->dir != NULL)
    {        
        TNoA *menorDireita = menor(no->dir);
        if (menorDireita->chave < menorNo->chave)
        {
            menorNo = menorDireita ;
        }        
    }             
    return menorNo;                         
}

void imprime(TNoA *nodo, int tab) {
    for (int i = 0; i < tab; i++) {
        printf("-");
    }
    if (nodo != NULL) {
        printf("%d\n", nodo->chave);
        imprime(nodo->esq, tab + 2);
        printf("\n");
        imprime(nodo->dir, tab + 2);
    } else printf("vazio");
}

TNoA *insere(TNoA *no, int chave) {
    if (no == NULL) {
        no = (TNoA *) malloc(sizeof(TNoA));
        no->chave = chave;
        no->esq = NULL;
        no->dir = NULL;
    } else if (chave < (no->chave))
        no->esq = insere(no->esq, chave);
    else if (chave > (no->chave)) {
        no->dir = insere(no->dir, chave);
    } else {
        printf("Inserção inválida! ");
        exit(1);
    }
    return no;
}

int main(void) {
    /* A função main lê os dados de entrada, cria a árvore e chama a função solicitada no problema
     * depois imprime o resultado solicitado
     * ELA NÃO DEVE SER MODIFICADA
     * */
    TNoA *raiz, *no;
    raiz = NULL;
    char l[100];
    char delimitador[] = "-";
    char *ptr;
    int valor;


    /* lê valores para criar a arvore
     * valores devem ser informados separados por traço
     * exemplo: 1-3-5-2-7-9-21-6 */
    scanf("%s", l);
    //quebra a string de entrada
    ptr = strtok(l, delimitador);
    while(ptr != NULL) {
        valor = atoi(ptr);
        raiz = insere(raiz, valor);
        ptr = strtok(NULL, delimitador);
    }


    //
    //Chama função
    no = menor(raiz);
    if (no != NULL) {
        printf("\n%d\n", no->chave);
    }
    //imprime(raiz,0);
};