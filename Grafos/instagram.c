#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct vizinho {
    char nome[10];
    struct vizinho *prox;
} TVizinho;

typedef struct grafo {
    char nome[10];
    int idade;
    TVizinho *prim_vizinho;
    struct grafo *prox;
} TGrafo;

typedef struct verticesList
{
    char nome;
    int seguidores;
    struct vertices *prox;
} TypeList;

int numero_vizinhos = 0;
TypeList *verticesList;

TGrafo *insere_vertice(TGrafo *g, char *nome, int idade) {
    TGrafo *vertice = (TGrafo *) malloc(sizeof(TGrafo));
    strcpy(vertice->nome, nome);
    vertice->idade = idade;
    vertice->prox = g;
    vertice->prim_vizinho = NULL;
    return vertice;
}

TGrafo *busca_vertice(TGrafo *vertice, char *nome) {
    while ((vertice != NULL) && (strcmp(vertice->nome, nome) != 0)) {
        vertice = vertice->prox;
    }
    return vertice;
}

TVizinho *busca_vizinho(TVizinho *vizinho, char *nome) {
    while ((vizinho != NULL) && (strcmp(vizinho->nome, nome) != 0)) {
        vizinho = vizinho->prox;
    }
    return vizinho;
}

void insere_aresta(TGrafo *g, char *nome_origem, char *nome_destino) {
    TGrafo *vertice = busca_vertice(g, nome_origem);
    TVizinho *vizinho = (TVizinho *) malloc(sizeof(TVizinho));
    strcpy(vizinho->nome, nome_destino);
    vizinho->prox = vertice->prim_vizinho;
    vertice->prim_vizinho = vizinho;
}

void imprime(TGrafo *vertice) {
    while (vertice != NULL) {
        printf("Pessoa: %s - %d anos\n", vertice->nome, vertice->idade);
        printf("Segue: ");
        TVizinho *vizinho = vertice->prim_vizinho;
        while (vizinho != NULL) {
            printf("%s ", vizinho->nome);
            vizinho = vizinho->prox;
        }
        printf("\n\n");
        vertice = vertice->prox;
    }
}
 
int numero_seguidos(TGrafo *g, char *nome) {       
    if ((g != NULL) && (strcmp(g->nome, nome) == 0))
    {
        TVizinho *vizinho = g->prim_vizinho;
        while (vizinho != NULL )
        {
            numero_vizinhos++;
            vizinho = vizinho->prox;
        }            
    }
    else
    {
        numero_seguidos(g->prox, nome);
    }                       
    return numero_vizinhos;
}

int seguidores(TGrafo *g, char *nome, int imprime) {
    if (g != NULL)
    {
        TVizinho *seguidor = busca_vizinho(g->prim_vizinho, nome);
        if (seguidor != NULL)
        {
            printf("%s ", g->nome);
        }
        
        seguidores(g->prox, nome, imprime);
    }    else
    {
        printf("\n");
    }
    
    return 0;    
}

TypeList* insere_vertice_lista(TypeList* verticesList, char name){
    TypeList* newVertex = (TypeList*)malloc(sizeof(TypeList));
    newVertex->nome = name;
    newVertex->seguidores = 0;
    newVertex->prox = NULL;
    TypeList* pointerOfLastElement = verticesList;
    if (pointerOfLastElement->prox == NULL)
    {
        verticesList = newVertex;
    }else{
        while (pointerOfLastElement != NULL){
            verticesList = verticesList->prox;
        }
        pointerOfLastElement->prox = newVertex;
    }
    return verticesList;    
}

void cria_lista(TGrafo *grafo, TypeList** list){
    if (grafo != NULL)
    {
        insere_vertice_lista(list, grafo->nome);
        cria_lista(grafo->prox, list);
    }    
}

void exibir_lista_vertices(TypeList *lista_vertices) {
    printf("Lista de Vértices:\n");
    while (lista_vertices != NULL) {
        printf("Nome: %s, Seguidores: %d\n", lista_vertices->nome, lista_vertices->seguidores);
        lista_vertices = lista_vertices->prox;
    }
}

void popularidade(TGrafo *g,TypeList *verticesList){
    while (g != NULL)
    {        
        // verificar existencia do vertice atual na lista de vertices        
        TVizinho *vizinho = g->prim_vizinho;
        while (vizinho != NULL )// percorrendo lista de arestas
        {
            while (verticesList != NULL)// percorrendo lista de nomes
            {
                if (vizinho->nome == verticesList->nome)
                {
                    verticesList->seguidores++;
                }                
                verticesList = verticesList->prox;
            }                        
            vizinho = vizinho->prox;
        }                                
        g = g->prox;
    }
}

TGrafo *mais_popular(TGrafo *g) {
    cria_lista(g, &verticesList);
    
    popularidade(g, verticesList);    

    TGrafo *popular;
    TypeList *atual, *anterior;

    while (verticesList != NULL)
    {    
        anterior = verticesList;
        atual = verticesList->prox;

        if (atual->seguidores >= anterior->seguidores)
        {
            popular = atual;            
        }else
        {
            popular = anterior;
        }
        verticesList = verticesList->prox;
    }             
    return popular;
}

int segue_mais_velho(TGrafo *g, int imprime) {
    //TODO: Implementar essa função
    return 0;
}

void libera_vizinho(TVizinho *vizinho) {
    if (vizinho != NULL) {
        libera_vizinho(vizinho->prox);
        free(vizinho);
    }
}

void libera_vertice(TGrafo *vertice) {
    if (vertice != NULL) {
        libera_vizinho(vertice->prim_vizinho);
        libera_vertice(vertice->prox);
        free(vertice);
    }
}

void imprime_lista(TypeList *verticesList){
    while (verticesList != NULL)
    {
        printf("%s :", verticesList->nome);
        printf("%d :", verticesList->seguidores);
    }
    
}

int main() {    
    /* A função main lê os dados de entrada, cria o grafo e chama as funções solicitadas no problema
    * depois imprime os resultados solicitados
    * ELA NÃO DEVE SER MODIFICADA
    * */
    int num_vertices, num_arestas;
    char nome[30];
    char origem[30], destino[30];
    char l[100];
    char delimitador[] = "-";
    char *ptr;
    int idade;
    int i;
    TGrafo *g = NULL;

    //le numero de vertices
    scanf("%d", &num_vertices);
    //le e cria os vertices
    for (i = 0; i < num_vertices; i++) {
        scanf("%s", l);
        //quebra a string de entrada
        ptr = strtok(l, delimitador);
        strcpy(nome,ptr);
        //printf("%s", nome);
        ptr = strtok(NULL, delimitador);
        idade = atoi(ptr);
        g = insere_vertice(g, nome, idade);
    }

    //Le numero de arestas e depois le os dados de cada aresta
    //Cria as arestas no grafo
    scanf("%d", &num_arestas);
    for (i = 0; i < num_arestas; i++) {
        scanf("%s", l);
        //quebra a string de entrada
        ptr = strtok(l, delimitador);
        strcpy(origem,ptr);
        //printf("%s", nome);
        ptr = strtok(NULL, delimitador);
        strcpy(destino,ptr);
        insere_aresta(g, origem, destino);
    }

    //Le nome de pessoa
    scanf("%s", nome);

    //Encontra o número de seguidos dessa pessoa
    printf("SEGUIDOS por %s: %d\n", nome, numero_seguidos(g, nome));

    //Encontra os seguidores de uma determinada pessoa
    printf("SEGUIDORES de %s:\n", nome);
    seguidores(g, nome, 1);    

    TGrafo *p;

    //Encontra mais popular
    p = mais_popular(g);
    printf("MAIS POPULAR: %s\n", p->nome); 

    //Encontra as pessoas que seguem apenas pessoas mais velhas
    printf("SEGUEM APENAS PESSOAS MAIS VELHAS:\n");
    segue_mais_velho(g,1);

    libera_vertice(g);
}
 