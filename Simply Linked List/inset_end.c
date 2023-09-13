#include <stdio.h>
#include <stdlib.h>
typedef struct List{
    int info;
    struct List* prox;
} typeList;

typeList* inset_end(typeList* list, int information){// List é um ponteiro para o unicio da lista
    typeList* new = (typeList*) malloc( sizeof(struct List));
    new->info = information;
    new->prox = NULL;
    typeList* pointerOfLastElement = list;
    if(pointerOfLastElement == NULL){// Caso a lista se encontre no inicio
        list = new; // List que era um ponteiro para o ultimo elemento da list recebe o end.
                    // de new que é o end. adicionado ao final
    }else{
        while (pointerOfLastElement != NULL){
            list = list->prox;
        }
        pointerOfLastElement->prox = new;
    }
    return list;
}


int main() {
    printf("Hello, World!\n");
    return 0;
}
