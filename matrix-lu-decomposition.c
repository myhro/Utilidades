/*
	Implementação da decomposição LU (também conhecida como fatoração LU).
	O que este programa faz é receber uma matriz (ou os coeficientes de N equações lineares) e decompô-la em matriz triangular inferior e superior.
	Daí em diante basta utilizar os passos L.Y = B e U.X = Y onde X será a solução do sistema de equações lineares.
*/

#include <stdio.h>
#include <stdlib.h>

void imprime(float *mat, int l, int c) {
	int i, j;

	printf("\n");

	for (i = 0; i < l; i++) {
		for (j = 0; j < c; j++) {;
			printf("%.2f ", mat[i*c+j]);
		}
		printf("\n");
	}
}

void inicializa(float *mat, int n) {
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j) {
				mat[i*n+j] = 1;
			}
			else {
				mat[i*n+j] = 0;
			}
		}
	}
}

void inicializa_zero(float *mat, int n) {
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			mat[i*n+j] = 0;
		}
	}
}

void inverte(float *mat_a, float *mat_b, int n) {
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			mat_b[i*n+j] = mat_a[i*n+j];
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if ((j < i) && (mat_b[i*n+j] != 0)) {
				mat_b[i*n+j] *= -1;
			}
		}
	}
}

void modifica(float *mat_a, float *mat_b, int n, int m) {
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (j < i) {
				mat_b[i*n+(m-1)] = mat_a[i*n+(m-1)] / mat_a[(m-1)*n+(m-1)];
				if ((((mat_b[i*n+(m-1)] * mat_a[(m-1)*n+(m-1)]) + mat_a[i*n+(m-1)] + mat_a[(i+1)*n+(m-1)]) != 1) && (m - 1) != i) {
					mat_b[i*n+(m-1)] *= -1;
				}
			}
		}
	}
}

void multiplica(float *mat_a, float *mat_b, int n, float *res) {
	int i, j, k;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++) {
				res[i*n+j] += mat_a[i*n+k] * mat_b[k*n+j];
			}
		}
	}
}

void preenche(float *mat, int l, int c) {
	int i, j;

	for (i = 0; i < l; i++) {
		printf("\nEquacao %d: \n\n", i+1);
		for (j = 0; j < c; j++) {
			printf("Coeficiente de x%d: ", j+1);
			scanf("%f", &mat[i*c+j]);
		}
	}
}

void preenche_res(float *mat, int l, int c) {
	int i, j;

	printf("\n");

	for (i = 0; i < l; i++) {
		for (j = 0; j < c; j++) {
			printf("Resultado da equacao %d: ", i+1);
			scanf("%f", &mat[i*c+j]);
		}
	}
}

int main() {
	int n, i, j;
	float *a_0, *a_1, *a_2, *m_0, *im_0, *m_1, *im_1, *B, *L, *U, *X, *Y;

	printf("Quantas sao as equacoes lineares? ");
	scanf("%d", &n);

	a_0 = (float *) malloc(n*n*sizeof(float));
	if (a_0 == NULL) {
		printf("\nMemoria insuficiente.\n");
		return(1);
	}

	preenche(a_0,n,n);

	printf("\nMatriz A0: \n");
	imprime(a_0,n,n);

	m_0 = (float *) malloc(n*n*sizeof(float));
	if (m_0 == NULL) {
		printf("\nMemoria insuficiente.\n");
		return(1);
	}

	inicializa(m_0,n);
	modifica(a_0,m_0,n,1);

	printf("\nMatriz M0: \n");
	imprime(m_0,n,n);

	im_0 = (float *) malloc(n*n*sizeof(float));
	if (im_0 == NULL) {
		printf("\nMemoria insuficiente.\n");
		return(1);
	}

	inverte(m_0,im_0,n);
	printf("\nMatriz M0^-1: \n");
	imprime(im_0,n,n);

	a_1 = (float *) malloc(n*n*sizeof(float));
	if (a_1 == NULL) {
		printf("\nMemoria insuficiente.\n");
		return(1);
	}

	inicializa_zero(a_1,n);
	multiplica(m_0,a_0,n,a_1);
	printf("\nMatriz A1: \n");
	imprime(a_1,n,n);

	m_1 = (float *) malloc(n*n*sizeof(float));
	if (m_1 == NULL) {
		printf("\nMemoria insuficiente.\n");
		return(1);
	}

	inicializa(m_1,n);
	modifica(a_1,m_1,n,2);
	printf("\nMatriz M1: \n");
	imprime(m_1,n,n);

	im_1 = (float *) malloc(n*n*sizeof(float));
	if (im_1 == NULL) {
		printf("\nMemoria insuficiente.\n");
		return(1);
	}

	inverte(m_1,im_1,n);
	printf("\nMatriz M1^-1: \n");
	imprime(im_1,n,n);

	a_2 = (float *) malloc(n*n*sizeof(float));
	if (a_2 == NULL) {
		printf("\nMemoria insuficiente.\n");
		return(1);
	}

	inicializa_zero(a_2,n);
	multiplica(m_1,a_1,n,a_2);
	printf("\nMatriz A2: \n");
	imprime(a_2,n,n);

	L = (float *) malloc(n*n*sizeof(float));
	if (L == NULL) {
		printf("\nMemoria insuficiente.\n");
		return(1);
	}

	inicializa_zero(L,n);
	multiplica(im_0,im_1,n,L);
	printf("\nMatriz L: \n");
	imprime(L,n,n);

	free(a_0);
	free(B);
	free(m_0);
	free(im_0);
	free(a_1);
	free(m_1);
	free(im_1);
	free(a_2);
	free(L);

	return(0);
}
