#include <stdio.h>
#include <stdlib.h>

typedef struct List
{
    int information;
    struct list *next;
}typeList;

void print_list(typeList *li) {
    printf("Lista de Nós: ");
    typeList* p;
    for (p = li; p != NULL; p = p->next)
        printf("|%d|->", p->information);
        printf("NULL\n");
}

typeList* create_list( typeList * li, int size, int *values){
    typeList *new, *aux;    
    for (int i = 0; i < size; i++)
    {
        new = (typeList*) malloc(sizeof(typeList));
        new->information = values[i];
        new->next = NULL;

        // caso a lista esteja vazia
        if (li == NULL)
        {
            li = new;
        }// caso contenha elementos
        else{
            aux = li;// cópia da lista para poder percorre-la
            // Percorrimento da lista
            while (aux->next != NULL)
            {
                aux = aux->next;
            }//localizado ulimo elemento da lista, ele é apontado para um novo
            aux->next = new;
        }        
    }
    return li;
}

typeList* insert_sorted( typeList* list, int *value){
    typeList* new = (typeList*) malloc(sizeof(typeList));
    new->information = value;
    new->next = NULL;

    typeList *p = list;
    typeList *previousNode;
    while (p->next != NULL && p->information <= value )
    {
        previousNode = p;
        p = p->next;
    }// inserção em lista vazia
    if (list == NULL)
    {
        list = new;
    }// caso inserção no final da lista
    if (p->next == NULL)
    {
        p->next = new;
    }// caso inserção no meio da lista
    else{
        new->next = previousNode->next;
        previousNode->next = new;
    }            
    return list;
}

int main(){
    typeList * list = NULL;
    int size;

    printf("Defina o tamnho da lista: ");
    scanf("%d", &size);

    int values[size];
    for (int i = 0; i < size; i++)
    {
        values[i] = rand() % 20;
    }

    /* ORDENA VETOR */
    int min_idx;
    // percorre o vetor até o penúltimo elemento
    for (int i = 0; i < size-1; i++) {
        // encontra o menor elemento no subvetor não ordenado
        min_idx = i;
        for (int j = i+1; j < size; j++) {
            if (values[j] < values[min_idx]) {
                min_idx = j;
            }
        }
        // troca o menor elemento com o elemento atualmente na posição i
        int temp = values[i];
        values[i] = values[min_idx];
        values[min_idx] = temp;
    }

    list = create_list(list, size, values);
    print_list(list);

    // Criar função para incerir elementos ordenados
    int value;
    printf("Defina um valor para adicionar um Nó a lista: ");
    scanf("%d", &value);

    list = insert_sorted(list, value);
    print_list(list);

    return 0;
}