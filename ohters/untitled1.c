#include<stdio.h>
#include<stdlib.h>
int main() {
	int m, n;
	scanf("%d %d", &m, &n);
	double**A = (double**)malloc(m * sizeof(double*));
	for (int i = 0; i < m; i++) {
		A[i] = (double*)malloc(n * sizeof(double));
		for (int j = 0; j < n; j++) {
			scanf("%lf", &A[i][j]);
		}
	}
	
	int s, t;
	scanf("%d %d", &s, &t);
	double**B = (double**)malloc(s * sizeof(double*));
	for (int i = 0; i < s; i++) {
		B[i] = (double*)malloc(t * sizeof(double));
		for (int j = 0; j < t; j++) {
			scanf("%lf", &B[i][j]);
		}
	}
	printf("积为：\n");	
	double**C = (double**)malloc(m * s * sizeof(double*));
	for (int i = 0; i < m*s; i++) {
		C[i] = (double*)malloc(n * t * sizeof(double));
		for (int j = 0; j < t*n; j++) {
			int bi = i % s;
			int bj = j % t;
			int ai = i / s;
			int aj = j / t;
			C[i][j] = A[ai][aj] * B[bi][bj];
			printf("%lf ", C[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < m; i++) {
		free(A[i]);
	}
	free(A);
	for (int i = 0; i < s; i++) {
		free(B[i]);
	}
	free(B);
	for (int i = 0; i < m * s; i++) {
		free(C[i]);
	}
	free(C);

}
