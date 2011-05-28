#include <stdio.h>
#include <stdlib.h>

typedef struct arvore Arvore;

struct arvore {
    int info;
    Arvore *esq, *dir;
};

Arvore *inicializa() {
    return NULL;
}

int vazia(Arvore *a) {
    return (a == NULL);
}

void _imprime(Arvore *a) {
    if (!vazia(a)) {
        _imprime(a->esq);
        printf("%d\n", a->info);
        _imprime(a->dir);
    }
}

void imprime(Arvore *a) {
    if (!vazia(a))
        _imprime(a);
    else
        printf("Arvore vazia.\n");
}

Arvore *libera(Arvore *a) {
    if(!vazia(a)) {
        libera(a->esq);
        libera(a->dir);
        free(a);
    }
    return NULL;
}

int busca(Arvore *a, int n) {
    if (vazia(a))
        return -1;
    else if (a->info > n)
        return busca(a->esq,n);
    else if (a->info < n)
        return busca(a->dir,n);
    else
        return n;
}

Arvore *insere(Arvore *a, int n) {
    if (vazia(a)) {
        a = (Arvore *) malloc(sizeof(Arvore));
        a->info = n;
        a->esq = NULL;
        a->dir = NULL;
    }
    else if (n < a->info)
        a->esq = insere(a->esq,n);
    else
        a->dir = insere(a->dir,n);
    return a;
}

Arvore* retira(Arvore* a, int n) {
    Arvore *filho, *pai, *tmp;
    if (vazia(a))
        return NULL;
    else if (a->info > n)
        a->esq = retira(a->esq, n);
    else if (a->info < n)
        a->dir = retira(a->dir, n);
    else { /* achou o elemento */
        if (vazia(a->esq) && vazia(a->dir)) { /* elemento sem filhos */
            free(a);
            a = NULL;
        }
        else if (vazia(a->esq)) { /* só tem filho à direita */
            tmp = a;
            a = a->dir;
            free(tmp);
        }
        else if (vazia(a->dir)) { /* só tem filho à esquerda */
            tmp = a;
            a = a->esq;
            free(tmp);
        }
        else { /* tem os dois filhos */
            pai = a;
            filho = a->esq;
            while (!vazia(filho->dir)) {
                pai = filho;
                filho = filho->dir;
            }
            a->info = filho->info; /* troca as informações */
            filho->info = n;
            a->esq = retira(a->esq,n);
            }
    }
    return a;
}

void linha() {
    int i;
    for (i = 0; i < 15; i++)
        printf("-");
    printf("\n");
}

int main() {
    Arvore *arv = inicializa(arv);
    int i, tmp;

    arv = insere(arv,5);
    arv = insere(arv,9);
    arv = insere(arv,3);
    arv = insere(arv,1);
    arv = insere(arv,4);
    arv = insere(arv,8);
    arv = insere(arv,2);
    arv = insere(arv,7);
    arv = insere(arv,6);
    imprime(arv);

    linha();

    arv = retira(arv,5);
    //arv = retira(arv,9);
    arv = retira(arv,3);
    //arv = retira(arv,1);
    arv = retira(arv,4);
    //arv = retira(arv,8);
    arv = retira(arv,2);
    //arv = retira(arv,7);
    arv = retira(arv,6);
    imprime(arv);

    linha();

    tmp = busca(arv,7);
    printf("%d\n", tmp);

    linha();

    arv = libera(arv);
    imprime(arv);

    return 0;
}
