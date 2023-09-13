#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Definição da estrutura de um nó da árvore binária
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
} Queue;

// Função para obter o elemento no início da fila sem removê-lo
int peek(Queue *queue) {
    if (isEmpty(queue)) {
        printf("Erro: a fila está vazia\n");
        return -1; // Valor de erro, você pode modificar conforme necessário
    }
    
    return queue->data[queue->front];
}

// Função para inicializar a fila
void initialize(Queue *queue) {
    queue->front = -1;
    queue->rear = -1;
}

// Função para verificar se a fila está vazia
int isEmpty(Queue *queue) {
    return queue->front == -1;
}

// Função para verificar se a fila está cheia
int isFull(Queue *queue) {
    return (queue->rear + 1) % MAX_SIZE == queue->front;
}
// Função para enfileirar um elemento
void enqueue(Queue *queue, int element) {
    if (isFull(queue)) {
        printf("Erro: a fila está cheia\n");
        return;
    }
    
    if (isEmpty(queue)) {
        queue->front = 0;  // Se a fila estiver vazia, atualiza o valor de front
    }
    
    queue->rear = (queue->rear + 1) % MAX_SIZE; // Incrementa o valor de rear
    queue->data[queue->rear] = element; // Adiciona o elemento no final da fila
}

// Função para desenfileirar um elemento
int dequeue(Queue *queue) {
    if (isEmpty(queue)) {
        printf("Erro: a fila está vazia\n");
        return -1; // Valor de erro, você pode modificar conforme necessário
    }
    
    int element = queue->data[queue->front]; // Armazena o elemento a ser removido
    if (queue->front == queue->rear) {
        // Se houver apenas um elemento na fila, esvazia a fila
        initialize(queue);
    } else {
        queue->front = (queue->front + 1) % MAX_SIZE; // Incrementa o valor de front
    }
    
    return element;
}

// Função para criar um novo nó da árvore
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erro ao alocar memória para o nó\n");
        exit(1);
    }
    
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

// Função para verificar se uma árvore binária é cheia
int isBinaryTreeFull(Node* root) {
    if (root == NULL) {
        return 1;  // Árvore vazia é considerada cheia
    }
    
    // Criação de uma fila para percorrer a árvore
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Erro ao alocar memória para a fila\n");
        exit(1);
    }
    initialize(queue);
    
    // Adiciona a raiz na fila
    enqueue(queue, root);
    
    int flag = 0;  // Flag para indicar se encontramos um nó não cheio
    
    // Percorre a árvore utilizando a fila
    while (!isEmpty(queue)) {
        Node* current = dequeue(queue);  // Remove o nó da frente da fila
        
        // Verifica se o nó atual tem subárvores vazias
        if (current->left == NULL && current->right != NULL) {
            return 0;  // Árvore não é cheia
        }
        
        // Verifica se encontrou um nó não cheio no último nível
        if (flag == 1 && (current->left != NULL || current->right != NULL)) {
            return 0;  // Árvore não é cheia
        }
        
        // Marca a flag quando encontra um nó não cheio
        if (current->left == NULL || current->right == NULL) {
            flag = 1;
        }
        
        // Adiciona os filhos na fila
        if (current->left != NULL) {
            enqueue(queue, current->left);
        }
        if (current->right != NULL) {
            enqueue(queue, current->right);
        }
    }
    
    return 1;  // Árvore é cheia
}

int main() {
    // Exemplo de árvore binária cheia
    Node* root1 = createNode(1);
    root1->left = createNode(2);
    root1->right = createNode(3);
    root1->left->left = createNode(4);
    root1->left->right = createNode(5);
    root1->right->left = createNode(6);
    root1->right->right = createNode(7);

    if (isBinaryTreeFull(root1)) {
        printf("A árvore é cheia\n");
    } else {
        printf("A árvore não é cheia\n");
    }
    
    // Exemplo de árvore binária não cheia
    Node* root2 = createNode(1);
    root2->left = createNode(2);
    root2->right = createNode(3);
    root2->left->left = createNode(4);
    root2->left->right = createNode(5);
    root2->right->right = createNode(7);
    
    if (isBinaryTreeFull(root2)) {
        printf("A árvore é cheia\n");
    } else {
        printf("A árvore não é cheia\n");
    }
    
    return 0;
}
