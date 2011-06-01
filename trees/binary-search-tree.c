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
        return 0;
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

Arvore *retira(Arvore *a, int n) {
    Arvore *filho, *pai, *tmp;
    if (vazia(a))
        return NULL;
    else if (a->info > n)
        a->esq = retira(a->esq, n);
    else if (a->info < n)
        a->dir = retira(a->dir, n);
    else { // Achou o elemento
        if (vazia(a->esq) && vazia(a->dir)) { // Nó sem filhos
            free(a);
            a = NULL;
        }
        else if (vazia(a->esq)) { // Só tem filho à direita
            tmp = a;
            a = a->dir;
            free(tmp);
        }
        else if (vazia(a->dir)) { // Só tem filho à esquerda
            tmp = a;
            a = a->esq;
            free(tmp);
        }
        else { // Tem os dois filhos
            pai = a;
            filho = a->esq;
            while (!vazia(filho->dir)) {
                pai = filho;
                filho = filho->dir;
            }
            a->info = filho->info; // Troca as informações
            filho->info = n;
            a->esq = retira(a->esq,n);
            }
    }
    return a;
}

int contar_nos(Arvore *a) {
    if (vazia(a))
        return 0;
    else
        return (1 + contar_nos(a->esq) + contar_nos(a->dir));
}

int contar_folhas(Arvore *a) {
    if (vazia(a))
        return 0;
    if (vazia(a->esq) && vazia(a->dir))
        return 1;
    return (contar_folhas(a->esq) + contar_folhas(a->dir));
}

int altura(Arvore *a) {
    int he, hd;
    if (vazia(a))
        return -1; // Se a árvore não tiver nós, sua altura é -1
    else {
        he = altura(a->esq);
        hd = altura(a->dir);
    if (he < hd)
        return hd + 1;
    else
        return he + 1;
   }
}

void linha() {
    int i;
    for (i = 0; i < 15; i++)
        printf("-");
    printf("\n");
}

int main() {
    Arvore *arv = inicializa(arv);

	/*
		Não é necessário retornar o ponteiro ao se adicionar um nó, exceto ao inserir a raiz. Embora
		seja interessante o retorno pois a árvore pode ter sido reinicializada (em um menu, por ex).
	*/
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

    printf("Nos: %d \t Folhas: %d \t Altura: %d\n", contar_nos(arv), contar_folhas(arv), altura(arv));
    linha();

	/*
		É necessário receber o ponteiro na retirada, pois caso o último nó for removido (ou o nó seja
		a raiz e não possua subárvore a esquerda) os endereços (apontando para NULL no primeiro caso)
		mudam e as próximas chamadas de funções	podem gerar erros.
	*/
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

    printf("Nos: %d \t Folhas: %d \t Altura: %d\n", contar_nos(arv), contar_folhas(arv), altura(arv));
    linha();

    printf("Encontrou 7: %d \t\t Nao encontrou 10: %d\n", busca(arv,7), busca(arv,10));

    linha();

    arv = libera(arv); // A mesma coisa acontece ao se liberar (remover todos os nós) a árvore.
    printf("Nos: %d \t Folhas: %d \t Altura: %d\n", contar_nos(arv), contar_folhas(arv), altura(arv));
    imprime(arv);

    return 0;
}
