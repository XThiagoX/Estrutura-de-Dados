#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct noA {
    char info;
    struct noA *esq;
    struct noA *dir;
} TNoA;

typedef struct no_lista {
    char info;
    struct no_lista *prox;
} NoLista;

void insere_lista(NoLista **lista, char info) {
    NoLista *novo = (NoLista*) malloc(sizeof(NoLista));
    novo->info = info;
    novo->prox = NULL;

    if (*lista == NULL) {
        *lista = novo;
    } else {
        NoLista *aux = *lista;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
}

void cria_lista(TNoA *raiz, NoLista **lista) {
    if (raiz != NULL) {
        cria_lista(raiz->esq, lista);
        insere_lista(lista, raiz->info);
        cria_lista(raiz->dir, lista);
    }
}

int mesmos_nos(TNoA *a1, TNoA *a2) {   
    NoLista *list1 = NULL;
    //list1 = create_list(a1, &list1);
    cria_lista(a1, &list1);
    NoLista *list2 = NULL;
    //list2 = create_list(a2, &list2); 
    cria_lista(a2, &list2);

    NoLista *no1 = list1;
    NoLista *no2 = list2;

    while (no1 != NULL)
    {         
        int encontrado = 0;
        while (no2 != NULL) {
            if (no1->info == no2->info) {
                encontrado = 1;
                break;
            }
            no2 = no2->prox;
        }
        if (encontrado == 0) {
            return 0;
        }
        no1 = no1->prox;
        no2 = list2;
    }        
    return 1;
}

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

void imprimeProfundidade(TNoA *nodo, int altura) {
    altura = altura - 1;
    if (nodo != NULL) {
        printf("%c", nodo->info);
        if (altura > 0) {
            imprimeProfundidade(nodo->esq, altura);
            imprimeProfundidade(nodo->dir, altura);
        }
    } else {
        printf("*");
        //Trata caso de subarvore NULL em nível menor que altura da árvore
        if (altura > 0) {
            imprimeProfundidade(NULL, altura);
            imprimeProfundidade(NULL, altura);
        }
    }
}

TNoA *criaArvore(char entrada[100], int tamanho) {
    char novaEntrada[100];
    int i,j;
    TNoA *novo;
    novo = NULL;
    if ((tamanho > 0) && (entrada[0] != '*')) {
        novo = (TNoA *) malloc(sizeof(TNoA));
        novo->info = entrada[0];
        tamanho = tamanho / 2;

        //divide a entrada em duas partes e chama a função criaArvore recursivamente
        i = 1; //inicio da subarvore esquerda na string entrada
        j = 0; //cursor da nova string de entrada que conterá apenas a subárvore desejada
        while (i <= tamanho) {
            novaEntrada[j] = entrada[i];
            i++;
            j++;
        }
        novaEntrada[i] = '\0';
        novo->esq = criaArvore(novaEntrada, tamanho);

        i = tamanho+1; //inicio da subarvore direita na string entrada
        j = 0; //cursor da nova string de entrada que conterá apenas a subárvore desejada
        while (i <= tamanho*2) {
            novaEntrada[j] = entrada[i];
            i++;
            j++;
        }
        novaEntrada[i] = '\0';
        novo->dir = criaArvore(novaEntrada, tamanho);
    }
    return novo;
}

int main (void) {
    /* A função main lê os dados de entrada, cria as árvores e chama a função solicitada no exercício
     * depois imprime o resultado
     * Ela NÃO DEVE SER MODIFICADA
     * */
    TNoA* a1 = NULL;
    TNoA* a2 = NULL;
    int tam;
    char entrada1[100];
    char entrada2[100];

    /* lê valores para criar a árvore 1
     * exemplo: FBC */
    scanf("%s", entrada1);
    tam = strlen(entrada1);
    a1 = criaArvore(entrada1 , tam);

    /* le valores para criar a arvore 2 */
    scanf("%s", entrada2);
    tam = strlen(entrada2);
    a2 = criaArvore(entrada2 , tam);
    /* imprime(a1, tam);
    printf("\n");
    imprime(a2, tam); */
    printf("%d", mesmos_nos(a1, a2));
    
}

