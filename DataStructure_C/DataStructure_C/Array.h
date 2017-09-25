#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAX_ARRAY_DIM 8
typedef struct MyArray {
	int *base;//元素存储空间的基址
	int dim;//数组维数
	int *bounds;//数组，存储每一维的大小
	int *constants;//存储每维增加一个单位，在存储空间中需要增加几个单位
}Array; 

int InitArray(Array& A, int dim, ...);

void DestroyArray(Array& A);

int Locate(Array A, va_list ap, int& adr);

int getValue(Array A, int *e, ...);

int setValue(Array& A, int e, ...);

