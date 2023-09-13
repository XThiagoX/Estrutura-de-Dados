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

int numero_arestas(TGrafo *g) {
    int numArestas = 0;
    TGrafo *vertice = g;

    while (vertice != NULL) {
        TVizinho *vizinho = vertice->prim_vizinho;

        while (vizinho != NULL) {
            numArestas++;
            vizinho = vizinho->prox;
        }

        vertice = vertice->prox;
    }

    // Divide por 2 porque cada aresta é contada duas vezes (uma para cada vértice)
    return numArestas;
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
    printf("numero de arestas do grafo: %d\n", numero_arestas(g));

    libera_vertice(g);
}
 