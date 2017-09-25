#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAX_ARRAY_DIM 8
typedef struct MyArray {
	int *base;//Ԫ�ش洢�ռ�Ļ�ַ
	int dim;//����ά��
	int *bounds;//���飬�洢ÿһά�Ĵ�С
	int *constants;//�洢ÿά����һ����λ���ڴ洢�ռ�����Ҫ���Ӽ�����λ
}Array; 

int InitArray(Array& A, int dim, ...);

void DestroyArray(Array& A);

int Locate(Array A, va_list ap, int& adr);

int getValue(Array A, int *e, ...);

int setValue(Array& A, int e, ...);

