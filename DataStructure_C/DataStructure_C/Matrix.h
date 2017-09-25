#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRIPLE_SIZE 100
#define MAX_MATRIX_SIZE 1000

typedef struct Triple {
	int i, j;
	int v;
}Triple;

typedef struct Matrix {
	Triple e[MAX_TRIPLE_SIZE];
	int row, col, size;
}Matrix;

void TransposeMatrix1(Matrix A, Matrix& B);

void TransposeMatrix2(Matrix A, Matrix& B);

int MultiplyMatrix(Matrix A, Matrix B, Matrix& C);