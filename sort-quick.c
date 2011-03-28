#include <stdio.h>
#define max 10

void troca(int *a, int *b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int particionar(int *vet, int esq, int dir) {
	int i, j;

	i = esq;
	for (j = esq + 1; j <= dir; j++) {
		if (vet[j] < vet[esq]) {
			i++;
			troca(&vet[i], &vet[j]);
		}
	}
	troca(&vet[esq], &vet[i]);

	return i;
}

void quicksort(int *vet, int esq, int dir) {
	int r;

	if (dir > esq) {
		r = particionar(vet, esq, dir);
		quicksort(vet, esq, r - 1);
		quicksort(vet, r + 1, dir);
	}
}

int main() {
	int vetor[max] = {5,2,7,8,10,6,1,4,9,3};
	int i;
	quicksort(vetor,0,(max-1));
	for (i = 0; i < max; i++) {
		printf("%d ", vetor[i]);
	}
	return(0);
}
