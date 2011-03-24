#include <stdio.h>
#include <stdlib.h>
#define max 10

void merge(int *vec, int n) {
  int mid;
  int i, j, k;
  int *tmp;

  tmp = (int *) malloc(n * sizeof(int));
  if (tmp == NULL) {
  	printf("Memoria insuficiente.\n");
    exit(1);
  }

  mid = n / 2;

  i = 0;
  j = mid;
  k = 0;
  while (i < mid && j < n) {
    if (vec[i] < vec[j]) {
      tmp[k] = vec[i];
      i++;
    }
    else {
      tmp[k] = vec[j];
      j++;
    }
    k++;
  }

  if (i == mid) {
    while (j < n) {
      tmp[k] = vec[j];
      j++;
      k++;
    }
  }
  else {
    while (i < mid) {
      tmp[k] = vec[i];
      i++;
      k++;
    }
  }

  for (i = 0; i < n; ++i) {
    vec[i] = tmp[i];
  }

  free(tmp);
}

void mergeSort(int *vec, int n) {
  int mid;

  if (n > 1) {
    mid = n / 2;
    mergeSort(vec, mid);
    mergeSort(vec + mid, n - mid);
    merge(vec, n);
  }
}

int main() {
	int vetor[max] = {5,2,7,8,10,6,1,4,9,3};
	int i;
	mergeSort(vetor,max);
	for (i = 0; i < max; i++) {
		printf("%d ", vetor[i]);
	}
	return(0);
}
