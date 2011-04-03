#include <stdio.h>
#include <stdlib.h>

void imprime(int *mat, int l, int c) {
	int i, j;

	printf("\n");

	for (i = 0; i < l; i++) {
		for (j = 0; j < c; j++) {
			printf("%.2d ",mat[i*c+j]);
		}
		printf("\n");
	}
}

void inicializa(int *mat, int l, int c) {
	int i, j;

	for (i = 0; i < l; i++) {
		for (j = 0; j < c; j++) {
			mat[i*c+j] = 0;
		}
	}
}

void multiplica(int *mat_a, int *mat_b, int l_a, int c_a, int c_b, int *res) {
	int i, j, k;

	for (i = 0; i < l_a; i++) {
		for (j = 0; j < c_b; j++) {
			for (k = 0; k < c_a; k++) {
				res[i*c_b+j] += mat_a[i*c_a+k] * mat_b[k*c_b+j];
			}
		}
	}
}

void preenche(int *mat, int l, int c) {
	int i, j;

	for (i = 0; i < l; i++) {
		for (j = 0; j < c; j++) {
			printf("Valor %dx%d: ", i+1,j+1);
			scanf("%d", &mat[i*c+j]);
		}
	}
}

int main() {
	int l_a, c_a, l_b, c_b, *mat_a, *mat_b, *res;

	printf("Quantas linhas tem a matriz A? ");
	scanf("%d", &l_a);
	printf("Quantas colunas tem a matriz A? ");
	scanf("%d", &c_a);

	mat_a = (int *) malloc(l_a*c_a*sizeof(int));
	if (mat_a == NULL) {
		printf("\nMemoria insuficiente.\n");
		return(1);
	}

	printf("Quantas linhas tem a matriz B? ");
	scanf("%d", &l_b);
	printf("Quantas colunas tem a matriz B? ");
	scanf("%d", &c_b);

	mat_b = (int *) malloc(l_b*c_b*sizeof(int));
	if (mat_b == NULL) {
		printf("\nMemoria insuficiente.\n");
		return(1);
	}

	if (c_a != l_b) {
		printf("\nNao eh possivel multiplicar as matrizes.\n");
		return(1);
	}

	res = (int *) malloc(l_a*c_b*sizeof(int));
	if (res == NULL) {
		printf("\nMemoria insuficiente.\n");
		return(1);
	}

	inicializa(res,l_a,c_b);

	printf("\nMatriz A:\n\n");
	preenche(mat_a,l_a,c_a);

	printf("\nMatriz B:\n\n");
	preenche(mat_b,l_b,c_b);

	imprime(mat_a,l_a,c_a);
	printf("\nA\nx\nB\n");
	imprime(mat_b,l_b,c_b);

	multiplica(mat_a,mat_b,l_a,c_a,c_b,res);

	printf("\n=\n");
	imprime(res,l_a,c_b);

	free(mat_a);
	free(mat_b);
	free(res);

	return(0);
}
