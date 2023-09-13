#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct avl TAVL;

void TAVL_libera(TAVL *t);
TAVL* TAVL_busca(int e, TAVL *t);
TAVL* TAVL_insere(int e, TAVL *t);
void TAVL_imprime(TAVL *a);
TAVL* TAVL_retira(int x, TAVL *t);
