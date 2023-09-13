#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNoA {
    int chave;
    struct sNoA *esq;
    struct sNoA *dir;
} TNoA;

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

TNoA* buscaRecursiva(TNoA *no, int chave) {
    if (no == NULL){
        return NULL;
    }
    else if (no->chave == chave){
        return no;
    }
    else if (no->chave > chave){
        return buscaRecursiva(no->esq, chave);
    }else{
        return buscaRecursiva(no->dir, chave);
    }
}

void libera_no(TNoA *no){
    TNoA *aux = no;
    free(aux);
}

TNoA *deletePairs(TNoA *no){        
    if (no != NULL)
    {
        
        no->esq = deletePairs(no->esq);
        no->dir = deletePairs(no->dir);
        if (no->chave % 2 == 0)
        {
            //excluir
            if (no->dir == NULL && no->esq == NULL)
            {
                //excluir nó folha
                free(no);
                return NULL;
            }
            else if (no->dir != NULL && no->esq != NULL)
            {
                /* duas sub-arv. -> trocar com maior da esquerda */
                TNoA* temp = no->esq;
                while (temp->dir != NULL) {
                    temp = temp->dir;
                }
                no->chave = temp->chave;
                temp->chave = NULL;
                no->esq = deletePairs(no->esq);
            }else{
                if (no->esq == NULL)
                {
                    TNoA* temp = no->dir;
                    free(no);
                    return temp;
                }
                if (no->dir == NULL)
                {
                    // ligar o nó anterior a esse no
                    TNoA* temp = no->esq;
                    free(no);
                    return temp;
                }                
            }                        
        }                
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
    
    printf("Antes da exclução: \n");
    imprime(raiz, 0);
    printf("\n");
    raiz = deletePairs(raiz);
    printf("Depois da exclução: \n");    
    imprime(raiz, 0);
    printf("\n");
};