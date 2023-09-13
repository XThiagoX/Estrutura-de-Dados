#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct adjacent {
    char key[4];
    struct adjacent* next;
} adjacentNode;

typedef struct Graph {
    char key[4];
    adjacentNode* first_neighbor;
    struct Graph* next;
} Graph;

// Função para criar um novo vértice
Graph* createVertex(char key[]) {
    Graph* newVertex = (Graph*)malloc(sizeof(Graph));
    strcpy(newVertex->key, key);
    newVertex->first_neighbor = NULL;
    newVertex->next = NULL;
    return newVertex;
}

// Função para criar um novo nó adjacente
adjacentNode* createAdjacentNode(char key[]) {
    adjacentNode* newNode = (adjacentNode*)malloc(sizeof(adjacentNode));
    strcpy(newNode->key, key);
    newNode->next = NULL;
    return newNode;
}

// Função para encontrar um vértice no grafo
Graph* findVertex(Graph* graph, char key[]) {
    Graph* current = graph;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

// Função para inserir uma aresta entre dois vértices
void insertEdge(Graph** graph, char srcKey[], char destKey[]) {
    Graph* srcVertex = findVertex(*graph, srcKey);
    Graph* destVertex = findVertex(*graph, destKey);

    if (srcVertex == NULL || destVertex == NULL) {
        printf("Um ou mais vértices não foram encontrados. Aresta não pode ser inserida.\n");
        return;
    }

    // Inserir aresta do vértice de origem para o de destino
    adjacentNode* newAdjacentNode = createAdjacentNode(destKey);
    newAdjacentNode->next = srcVertex->first_neighbor;
    srcVertex->first_neighbor = newAdjacentNode;

    // Inserir aresta do vértice de destino para o de origem (grafo não orientado)
    newAdjacentNode = createAdjacentNode(srcKey);
    newAdjacentNode->next = destVertex->first_neighbor;
    destVertex->first_neighbor = newAdjacentNode;
}

// Função para exibir o grafo
void displayGraph(Graph* graph) {
    Graph* current = graph;
    while (current != NULL) {
        printf("Vértice: %s -> ", current->key);
        adjacentNode* neighbor = current->first_neighbor;
        while (neighbor != NULL) {
            printf("%s ", neighbor->key);
            neighbor = neighbor->next;
        }
        printf("\n");
        current = current->next;
    }
}

char* testek(Graph *grafh, int k){
    int nevel;
    while (grafh != NULL)
    {
        adjacentNode *neighbor = grafh->first_neighbor;
        nevel = 0;
        while (neighbor != NULL)
        {
            nevel++;
            neighbor = neighbor->next;
        }
        if (nevel == k)
        {                    
            grafh = grafh->next;
        }
        else
        {
            return "não";
            
        }                        
    }
    return "sim";   
}

int* graphics_Similarity(Graph *graph1, Graph *graph2){
    while (graph1 != NULL)
    {
        Graph *vertex;
        vertex = findVertex(graph2, graph1->key);
        // comparar listas
        adjacentNode *list_VertexGraph1 = graph1->first_neighbor;
        adjacentNode *list_VertexGraph2 = vertex->first_neighbor;

        int found = 0;
        while (list_VertexGraph1 != NULL)
        {
            while (list_VertexGraph2 != NULL)
            {
                if (list_VertexGraph1->key == list_VertexGraph2->key)
                {
                    found = 1;
                    break;
                }                            
                list_VertexGraph2 = list_VertexGraph2->next;
            }
            if (found == 0)
            {
                return 0;
            }            
            list_VertexGraph1 = list_VertexGraph1->next;
            list_VertexGraph2 = vertex->first_neighbor;
        }
        graph1 = graph1->next;
    }    
    return 1;
}

// Função principal
int main() {
    Graph* graph = NULL;
    char key[4];
    char input[10];
    int k = 2;
    int graphicsSimilarity;
    
    printf("Insira os vértices no formato 'chave' linha por linha (Digite 'fim' para encerrar):\n");
    while (1) {
        fgets(input, sizeof(input), stdin);
        if (strcmp(input, "fim\n") == 0 || strcmp(input, "FIM\n") == 0 || strcmp(input, "Fim\n") == 0)
            break;
        sscanf(input, "%s", key);

        Graph* newVertex = createVertex(key);
        newVertex->next = graph;
        graph = newVertex;
    }

    printf("Insira as ligações entre os vértices no formato 'vertice1-vertice2' linha por linha (Digite 'fim' para encerrar):\n");
    while (1) {
        fgets(input, sizeof(input), stdin);
        if (strcmp(input, "fim\n") == 0 || strcmp(input, "FIM\n") == 0 || strcmp(input, "Fim\n") == 0)
            break;

        char srcKey[4], destKey[4];
        sscanf(input, "%[^-]-%s", srcKey, destKey);

        insertEdge(&graph, srcKey, destKey);
    }

    printf("\nGrafo resultante:\n");
    displayGraph(graph);
    
    printf("Todos os vértices tem mesmo  nível? %s\n", testek(graph, k));
  
    Graph *graph2 = NULL;
    // Inserir vértices manualmente
    Graph* newVertex = createVertex("A");
    newVertex->next = graph2;
    graph2 = newVertex;

    newVertex = createVertex("B");
    newVertex->next = graph2;
    graph2 = newVertex;

    newVertex = createVertex("C");
    newVertex->next = graph2;
    graph2 = newVertex;

    newVertex = createVertex("D");
    newVertex->next = graph2;
    graph2 = newVertex;
    // Inserir arestas manualmente
    insertEdge(&graph2, "A", "B");
    insertEdge(&graph2, "B", "C");
    insertEdge(&graph2, "C", "D");
    insertEdge(&graph2, "D", "A");
    insertEdge(&graph2, "B", "D");

    graphicsSimilarity = graphics_Similarity(graph,graph2);
    displayGraph(graph2);

    printf("\nOs grafos são iguais: %d \n", graphicsSimilarity);

    return 0;
}
