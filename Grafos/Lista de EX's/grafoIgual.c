#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct viz{
    int id_vizinho;
    struct viz *prox;
}TVizinho;
typedef struct grafo{
    int id;
    struct grafo *prox;
    TVizinho *primeiro_vizinho;
}TGrafo;

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

    //Encontra a quantidade de vertices do grafo.
    int qtd_vertice = 0 ;
    int qtd_aresta = 0;
    qtd_aresta = quantidade_arestas(g, qtd_aresta);
    qtd_vertice = quantidade_verticies(g, qtd_vertice);

    printf("\nO grafo tem: %d", qtd_vertice);
    printf(" vértices \n");
     printf("\nO grafo tem: %d", qtd_aresta);
    printf(" arestas \n");

    imprime(g);


    libera_vertice(g);
}
 