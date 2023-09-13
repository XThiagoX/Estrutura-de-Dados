#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct listOfEdges{
    int id_neighbor;   
    char name[10]; 
    struct listOfEdges *next;
}TypeListOfEdges;

typedef struct grafh{
    int id;
    char name[10];
    TypeListOfEdges *first_neighbor;
    struct grafh *next;
}TypeGrafh;

TypeGrafh *insert_vertex(TypeGrafh *g, char *name, int id) {
    TypeGrafh *vertex = (TypeGrafh*) malloc(sizeof(TypeGrafh));
    strcpy(vertex->name, name);
    vertex->id = id;
    vertex->next = g;
    vertex->first_neighbor = NULL;
    return vertex;
}

void insert_edge(TypeGrafh *g, char *name_origem, char *name_destino) {
    TypeGrafh *vertex = seach_vertex(g, name_origem);
    TypeListOfEdges *neighbor = (TypeListOfEdges*) malloc(sizeof(TypeListOfEdges));
    strcpy(neighbor->name, name_destino);
    neighbor->next = vertex->first_neighbor;
    vertex->first_neighbor = neighbor;
}

TypeGrafh *seach_vertex(TypeGrafh *vertex, char *name) {
    while ((vertex != NULL) && (strcmp(vertex->name, name) != 0)) {
        vertex = vertex->next;
    }
    return vertex;
}

TypeListOfEdges *seach_neighbor(TypeListOfEdges *neighbor, char *name) {
    while ((neighbor != NULL) && (strcmp(neighbor->name, name) != 0)) {
        neighbor = neighbor->next;
    }
    return neighbor;
}

void print_grafh(TypeGrafh *vertex) {
    while (vertex != NULL) {
        printf("Pessoa: %s - %d anos\n", vertex->name, vertex->id);
        printf("vizinho: ");
        TypeListOfEdges *neighbor = vertex->first_neighbor;
        while (neighbor != NULL) {
            printf("%s ", neighbor->name);
            neighbor = neighbor->next;
        }
        printf("\n\n");
        vertex = vertex->next;
    }
}

void free_neighbor(TypeListOfEdges *neighbor) {
    if (neighbor != NULL) {
        free_neighbor(neighbor->next);
        free(neighbor);
    }
}

void free_vertex(TypeGrafh *vertex) {
    if (vertex != NULL) {
        free_neighbor(vertex->first_neighbor);
        free_vertex(vertex->next);
        free(vertex);
    }
}

int main() {        
    int num_vertexs, num_arestas;
    char name[30];
    char origem[30], destino[30];
    char l[100];
    char delimitador[] = "-";
    char *ptr;
    int id;
    int i;
    TypeGrafh *grafh = NULL;

    //le numero de vertexs
    scanf("%d", &num_vertexs);
    //le e cria os vertexs
    for (i = 0; i < num_vertexs; i++) {
        scanf("%s", l);
        //quebra a string de entrada
        ptr = strtok(l, delimitador);
        strcpy(name,ptr);
        //printf("%s", nome);
        ptr = strtok(NULL, delimitador);
        id = atoi(ptr);
        grafh = insert_vertex(grafh, name, id);
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
        insert_edge(grafh, origem, destino);
    }

    //Le nome de pessoa
    scanf("%s", name);

    //Encontra o número de vértices
    print_grafh(grafh);
    

    free_vertex(grafh);
}
 