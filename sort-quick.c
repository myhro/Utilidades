#include <stdio.h>
#define max 10

void troca(int *a, int *b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int particionar(int *vec, int left, int right) {
	int i, j;

	i = left;
	for (j = left + 1; j <= right; j++) {
		if (vec[j] < vec[left]) {
			i++;
			troca(&vec[i], &vec[j]);
		}
	}
	troca(&vec[left], &vec[i]);

	return i;
}

void quickSort(int *vec, int left, int right) {
	int r;

	if (right > left) {
		r = particionar(vec, left, right);
		quickSort(vec, left, r - 1);
		quickSort(vec, r + 1, right);
	}
}

int main() {
	int vetor[max] = {5,2,7,8,10,6,1,4,9,3};
	int i;
	quickSort(vetor,0,(max-1));
	for (i = 0; i < max; i++) {
		printf("%d ", vetor[i]);
	}
	return(0);
}
