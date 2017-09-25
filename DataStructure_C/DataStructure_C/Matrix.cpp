/*
��Ҫ����ϡ�����Sparse Matrix��
�����Ǵ�[1,1]��ʼ
��������Ϊ��
4 4 4
1 1 1
2 3 2
3 4 3
4 2 4
������
1 0 0 0
0 0 2 0
0 0 0 3
0 4 0 0
*/

#include "Matrix.h"

void TransposeMatrix1(Matrix A, Matrix& B)
{
	//ʱ�临�Ӷ�O(size*col)
	B.row = A.col;
	B.col = A.row;
	B.size = A.size;
	int pos = 0;
	for(int i=1;i<=A.col;i++)
		for (int p = 0; p < A.size; p++) if (A.e[p].j == i) {
			B.e[pos].i = i;
			B.e[pos].j = A.e[p].i;
			B.e[pos].v = A.e[p].v;
			pos++;
		}
}

void TransposeMatrix2(Matrix A, Matrix& B)
{
	//�ȼ���ÿ�й�����Ԫ�أ�֮�����ÿ��ת�ú���һά�����е�һ��Ԫ�ص�λ��
	//���Ӷ���O(size+col)
	int num[MAX_MATRIX_SIZE], pos[MAX_MATRIX_SIZE];
	for (int i = 1; i <= A.col; i++) num[i] = 0;
	for (int i = 0; i < A.size; i++) num[A.e[i].j]++;
	pos[1] = 0;
	for (int i = 2; i <= A.col; i++) pos[i] = pos[i - 1] + num[i - 1];
	B.row = A.col;
	B.col = A.row;
	B.size = A.size;
	for (int i = 0; i < A.size; i++) {
		int p = pos[A.e[i].j]++;
		B.e[p].i = A.e[i].j;
		B.e[p].j = A.e[i].i;
		B.e[p].v = A.e[i].v;
	}
}

int MultiplyMatrix(Matrix A, Matrix B, Matrix& C)
{
	if (A.col != B.row) return 0;
	C.row = A.row;
	C.col = B.col;
	C.size = 0;
	if (A.size*B.size == 0) return 1;
	//����A,B�����������з֣�ÿ�е�һ��Ԫ�ص�λ��
	int num[MAX_MATRIX_SIZE], apos[MAX_MATRIX_SIZE], bpos[MAX_MATRIX_SIZE], temp[MAX_MATRIX_SIZE];
	memset(num, 0, sizeof(num));
	for (int i = 0; i < A.size; i++) num[A.e[i].i]++;
	apos[1] = 0;
	for (int i = 2; i <= A.col; i++) apos[i] = apos[i - 1] + num[i - 1];

	memset(num, 0, sizeof(num));
	for (int i = 0; i < B.size; i++) num[B.e[i].i]++;
	bpos[1] = 0;
	for (int i = 2; i <= B.col; i++) bpos[i] = bpos[i - 1] + num[i - 1];

	//arow����ö�پ���A������
	for (int arow = 1; arow <= A.row; arow++) {
		//aendΪA.e��Ϊ��arow�е����һ��Ԫ�ص���һ��λ��
		int aend=0;
		if (arow < A.row) aend = apos[arow + 1];
		else aend = A.size;
		//temp[j]��ʾA[arow,k]*B[k,j]=C[arow,j]��ֵ
		//����k�ɵ�ǰA��arow��Ԫ�ص���ȷ��
		memset(temp, 0, sizeof(temp));
		for (int i = apos[arow]; i < aend; i++) {
			//��ǰA��arow��Ԫ�ص��м�ΪӦ��֮��˵��ӵ�B��Ԫ�ص���
			int brow = A.e[i].j;
			int bend = 0;
			if (brow < B.row) bend = bpos[brow + 1];
			else bend = B.size;
			for (int j = bpos[brow]; j < bend; j++) {
				temp[B.e[j].j] += A.e[i].v*B.e[j].v;
			}
		}

		for (int i = 1; i <= B.col; i++) if (temp[i]) {
			C.e[C.size].i = arow;
			C.e[C.size].j = i;
			C.e[C.size].v = temp[i];
			C.size++;
		}
	}
	return 1;
}

/*int main()
{
	Matrix A, B, C;
	scanf("%d%d%d", &A.row, &A.col, &A.size);
	for (int i = 0; i < A.size; i++)
		scanf("%d%d%d", &A.e[i].i, &A.e[i].j, &A.e[i].v);

	TransposeMatrix1(A, B);
	printf("\n");
	for (int i = 0; i < B.size; i++)
		printf("%d %d %d\n", B.e[i].i, B.e[i].j, B.e[i].v);

	TransposeMatrix2(A, B);
	printf("\n");
	for (int i = 0; i < B.size; i++)
		printf("%d %d %d\n", B.e[i].i, B.e[i].j, B.e[i].v);

	MultiplyMatrix(A, B, C);
	printf("\n");
	for (int i = 0; i < C.size; i++)
		printf("%d %d %d\n", C.e[i].i, C.e[i].j, C.e[i].v);

	return 0;
}*/