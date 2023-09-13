#include "TAVL.h"

struct avl{
  int info;
  struct avl *esq, *dir;
  int alt;
};

void TAVL_libera(TAVL *t){
  if(t){
    TAVL_libera(t->esq);
    TAVL_libera(t->dir);
    free(t);
  }
}

TAVL* TAVL_busca(int e, TAVL *t){
  if(!t) return NULL;
  if(e < t->info) return TAVL_busca(e, t->esq);
  if(e > t->info) return TAVL_busca(e, t->dir);
  return t;
}

static int calc_alt(TAVL *t){
  if(!t) return -1;
  return t->alt;
}

static int max(int l, int r){
  return l > r ? l : r;
}

static TAVL* TAVL_rot_dir(TAVL *t){
  TAVL *novo = t->esq;
  t->esq = novo->dir;
  novo->dir = t;
  t->alt = max(calc_alt(t->esq), calc_alt(t->dir)) + 1;
  novo->alt = max(calc_alt(novo->esq), t->alt) + 1;
  return novo; /* nova raiz */
}


static TAVL* TAVL_rot_esq(TAVL *t){
  TAVL *novo = t->dir;
  t->dir = novo->esq;
  novo->esq = t;
  t->alt = max(calc_alt(t->esq), calc_alt(t->dir)) + 1;
  novo->alt = max(calc_alt(novo->dir), t->alt) + 1;
  return novo;  /* nova raiz */
}


static TAVL* TAVL_rot_esq_dir(TAVL *t){
  t->esq = TAVL_rot_esq(t->esq);
  return TAVL_rot_dir(t);
}


static TAVL* TAVL_rot_dir_esq(TAVL *t){
  t->dir = TAVL_rot_dir(t->dir);
  return TAVL_rot_esq(t);
}


TAVL* TAVL_insere(int e, TAVL *t){
  if(!t){
    t = (TAVL*) malloc(sizeof(TAVL));
    if(!t){
      fprintf (stderr, "Falta memoria!!! (insere)\n");
      exit(1);
    }
    else{
      t->info = e;
      t->alt = 0;
      t->esq = t->dir = NULL;
    }
  }
  else if(e < t->info){
    t->esq = TAVL_insere(e, t->esq);
    if(calc_alt(t->esq) - calc_alt(t->dir) == 2)
      if(e < t->esq->info){
        printf("RSD(%d)\n", t->info);
        t = TAVL_rot_dir(t);
      }else{
        printf("RED(%d)\n", t->info);
        t = TAVL_rot_esq_dir(t);
      }
  }
  else if(e > t->info){
    t->dir = TAVL_insere(e, t->dir);
    if(calc_alt(t->esq) - calc_alt(t->dir) == -2)
      if(e > t->dir->info){
        printf("RSE(%d)\n", t->info);
        t = TAVL_rot_esq(t);
      }else{
        printf("RDE(%d)\n", t->info);
        t = TAVL_rot_dir_esq(t);
      }
  }
  t->alt = max(calc_alt(t->esq), calc_alt(t->dir)) + 1;
  return t;
}


int calc_alt_retira(TAVL *t){
  int lh, rh;
  if(!t) return 0;
  if(!t->esq) lh = 0;
  else lh = 1 + t->esq->alt;
  if(!t->dir) rh = 0;
  else rh = 1 + t->dir->alt;
  if(lh > rh) return lh;
  return rh;
}


int FB(TAVL *t){
  int lh, rh;
  if(!t) return -1;
  if(!t->esq) lh = -1;
  else lh = t->esq->alt;
  if(!t->dir) rh = -1;
  else rh = t->dir->alt;
  return (lh - rh);
}


void imprime_aux(TAVL *a, int andar){
  int j;
  if(a){
    imprime_aux(a->esq,andar + 1);
    for(j = 0; j <= andar; j++) printf("\t"); //printf("   ");
    printf("%d\n", a->info);
    imprime_aux(a->dir, andar + 1);
  }
  else{
   for(j = 0; j <= andar; j++) printf("\t");
   printf("N\n");
  }
}

void TAVL_imprime(TAVL *a){
  imprime_aux(a, 0);
}


TAVL* TAVL_retira(int x, TAVL *t){     
  if(!t) return t;
  else if(x > t->info){
    t->dir = TAVL_retira(x, t->dir);
    if(FB(t) == 2)
      if(FB(t->esq) >= 0){
        printf("RSD(%d)\n", t->info);
        t = TAVL_rot_dir(t);
      }else{
        printf("RED(%d)\n", t->info);
        t = TAVL_rot_esq_dir(t);
      }
  }
  else if(x < t->info){
    t->esq = TAVL_retira(x, t->esq);
    if(FB(t) == -2)
      if(FB(t->dir) <= 0){
        printf("RSE(%d)\n", t->info);
        t = TAVL_rot_esq(t);
      }else{
        printf("RDE(%d)\n", t->info);
        t = TAVL_rot_dir_esq(t);
      }
  }
  else{
    if(t->esq){
      TAVL *p = t->esq;
      while(p->dir) p = p->dir;
      t->info = p->info;
      t->esq = TAVL_retira(p->info, t->esq);
      if(FB(t) == -2)
        if(FB(t->dir) <= 0){
          printf("RSE(%d)\n", t->info);
          t = TAVL_rot_esq(t);
        }else{
          printf("RDE(%d)\n", t->info);
          t = TAVL_rot_dir_esq(t);
        }
    }else{
       TAVL *x = t;
       t = t->dir;
       free(x);
       return(t);
    }
  }
  t->alt = calc_alt_retira(t);
  return t;
}

