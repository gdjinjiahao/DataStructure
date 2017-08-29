#include <stdio.h>
#include <stdlib.h>

#define OVERFLOW -1
#define ERRO 0
#define OK 1

#define LIST_INIT_SIZE 100 //���Ա��ʼ����
#define LISTINCREMENT 10 //��������
#define ElemType int

typedef struct LinearList{
	ElemType *e; //���Ա��ַ
	int length; //���Ա�Ԫ�ظ���
	int listsize; //���䳤��
}SqList;

int equal(ElemType a,ElemType b)
{
	if(a==b) return 1;
	return 0;
}

int InitList(SqList& L)
{
	L.e=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(L.e==NULL) return OVERFLOW;
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	return OK;
}

int ListInsert(SqList& L,int i,ElemType x)
{
	//�ڵ�i��λ��ǰ����Ԫ��x
	//i�ĺϷ�ֵΪ[1,L.length+1]
	if(i<1||i>L.length+1) return ERRO;
	if(L.length>=L.listsize){
		ElemType* newbase=(ElemType*)realloc(L.e,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(newbase==NULL) return OVERFLOW;
		L.e=newbase;
		L.listsize+=LISTINCREMENT;
	}
	int pos=L.length-1;
	while(pos>=i-1){
		L.e[pos+1]=L.e[pos];
		pos--;
	}
	L.e[i-1]=x;
	L.length++;
	return OK;
}

int ListDelete(SqList& L,int i,ElemType& x)
{
	if(i<1||i>L.length) return ERRO;
	x=L.e[i-1];
	int pos=i; //pos=i-1+1
	while(pos<L.length){
		L.e[pos-1]=L.e[pos];
		pos++;
	}
	L.length--;
	return OK;
}

int LocateElem(SqList& L,ElemType x,int (*compare)(ElemType,ElemType))
{
	//���ҵ��򷵻�����L�е�λ�ã����򷵻�0
	int pos=0;
	while(pos<L.length&&!(*compare)(L.e[pos],x)) pos++;
	if(pos<L.length) return pos+1;
	return 0;
}

int main()
{
	SqList L;

	InitList(L);

	ElemType x1=1,x2=2,x3=3;
	ListInsert(L,1,x1);
	ListInsert(L,2,x2);
	ListInsert(L,3,x3);
	printf("INSERT:\n");
	printf("%d %d %d\n",L.e[0],L.e[1],L.e[2]);

	ElemType d;
	ListDelete(L,2,d);
	printf("DELETE:\n%d\n",d);

	ElemType f1=1,f2=2;
	printf("LocateElem:\n");
	printf("%d %d\n",LocateElem(L,f1,equal),LocateElem(L,f2,equal));


	printf("\n\n");
	for(int i=0;i<L.length;i++) printf("%d\n",L.e[i]);
	return 0;
}