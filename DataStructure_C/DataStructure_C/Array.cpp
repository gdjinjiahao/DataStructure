#include "Array.h"

int InitArray(Array& A, int dim, ...)
{
	if (dim<1 || dim>MAX_ARRAY_DIM) return 0;
	A.dim = dim;
	A.bounds = (int *)malloc(dim*sizeof(int));
	if (A.bounds == NULL) return 0;
	//elemtotal用于计算元素数组元素总数
	int elemtotal = 1;
	//ap用于得到变长参数
	va_list ap;
	va_start(ap, dim);
	for (int i = 0; i < dim; i++) {
		//va_arg每次以int类型返回ap中的下一个参数
		A.bounds[i] = va_arg(ap, int);
		if (A.bounds[i] < 0) {
			va_end(ap);
			return 0;
		}
		elemtotal *= A.bounds[i];
	}
	va_end(ap);

	A.base = (int *)malloc(elemtotal * sizeof(int));
	if (A.base == NULL) return 0;

	A.constants = (int *)malloc(dim * sizeof(int));
	if (A.constants == NULL) return 0;
	A.constants[dim - 1] = 1;
	for (int i = dim - 2; i >= 0; i--) {
		A.constants[i] = A.constants[i + 1] * A.bounds[i + 1];
	}
	return 1;
}

void DestroyArray(Array& A)
{
	if (A.base) free(A.base);
	if (A.bounds) free(A.bounds);
	if (A.constants) free(A.constants);
}

int Locate(Array A, va_list ap, int& adr)
{
	//获取映射到一维后的相对地址
	adr = 0;
	for (int i = 0; i < A.dim; i++) {
		int t = va_arg(ap, int);
		if (t < 0 || t >= A.bounds[i]) return 0;
		adr += A.constants[i] * t;
	}
	return 1;
}

int getValue(Array A, int *e, ...)
{
	va_list ap;
	va_start(ap, e);
	int adr = 0;
	if (!Locate(A, ap, adr)) {
		va_end(ap);
		return 0;
	}
	*e = *(A.base + adr);
	va_end(ap);
	return 1;
}

int setValue(Array& A, int e, ...)
{
	va_list ap;
	va_start(ap, e);
	int adr = 0;
	if (!Locate(A, ap, adr)) {
		va_end(ap);
		return 0;
	}
	*(A.base + adr) = e;
	return 1;
}

/*int main()
{
	Array A;
	if (!InitArray(A, 3, 2, 2, 2)) return 0;
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			for (int k = 0; k < 2; k++) {
				int t;
				scanf("%d", &t);
				setValue(A, t, i, j, k);
			}
	int x = 0;
	getValue(A, &x, 1, 0, 1);
	printf("%d\n", x);
	DestroyArray(A);
	return 0;
}*/