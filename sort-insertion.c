#include <stdio.h>
#define max 5

void insercao(int n, int vet[]) {
	int i, j, x;
	for (i = 1; i < n; i++) {
		x = vet[i];
		for (j = i-1; j >= 0 && vet[j] > x; j--) {
			vet[j+1] =  vet[j];
		}
		vet[j+1] = x;
	}
}

int main() {
	int vetor[max] = {7,3,2,5,4};
	int i;
	insercao(max,vetor);
	for (i = 0; i < max; i++) {
		printf("%d ", vetor[i]);
	}
	getch();
	return(0);
}
