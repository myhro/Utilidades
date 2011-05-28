#include <stdio.h>

int pesquisa(int *vet, int n, int chave) {
	int i, esq = 0, dir = n - 1;
	if (n == 0) {
		return -1;
	}
	while (1) {
		i = (esq + dir) / 2;
		if (chave > vet[i]) {
			esq++;
		}
		else {
			dir--;
		}
		if (chave == vet[i] || esq > dir) {
			break;
		}
	}
	if (vet[i] == chave) {
		return i;
	}
	else {
		return -1;
	}
}

int main() {
	int vet[8] = {1,2,3,4,5,6,7,8}, chave, x;
	printf("Buscar: ");
	scanf("%d", &chave);
	x = pesquisa(vet,8,chave);
	if (x != -1) {
		printf("Elemento %d encontrado na posicao %d.\n", chave, x);
	}
	else {
		printf("\nElemento nao encontrado.\n", chave);
	}
	return 0;
}
