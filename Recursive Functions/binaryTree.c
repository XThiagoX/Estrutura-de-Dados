#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
typedef struct Node {
    char data; // valor do nó
    struct Node* left; // filho esquerdo
    struct Node* right; // filho direito
} Node;

// Função para criar um novo nó da árvore
Node* newNode(char data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Função para criar uma árvore binária cheia com níveis definidos pelo usuário
Node* createTree(int level, char c) {
    if (level == 0) {
        return NULL;
    } else {
        Node* node = newNode(c);
        node->left = createTree(level - 1, c + 1);
        node->right = createTree(level - 1, c + 2);
        return node;
    }
}

// Função para percorrer e imprimir os nós da árvore de forma recursiva
void printTree(Node* node, int tab) {
    for (int i = 0; i < tab; i++)
    {
        printf("-");
    }    
    if (node != NULL) {
       
        printf("%c\n", node->data);
        printTree(node->left, tab + 2);
        printf("\n");
        printTree(node->right, tab + 2);
        
    } else {
        printf("vazio");
    }
}

// Função principal
int main() {
    int level;
    char c = 'A';

    printf("Digite o número de níveis da árvore: ");
    scanf("%d", &level);

    Node* root = createTree(level, c);

    printf("A árvore criada é:\n");
    printTree(root, 0);

    return 0;
}
