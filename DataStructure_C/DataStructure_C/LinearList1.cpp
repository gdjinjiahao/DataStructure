#include <stdio.h>
#include <stdlib.h>
#include "LinearList1.h"


int equal(ElemType a,ElemType b)
{
	if(a==b) return 1;
	return 0;
}
int greater(ElemType a,ElemType b){
	if(a>b) return 1;
	return 0;
}
int smaller(ElemType a,ElemType b)
{
	if(a<b) return 1;
	return 0;
}
int visit(ElemType x)
{
	printf("%d\n",x);
	return OK;
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
	//在第i个位置前插入元素x
	//i的合法值为[1,L.length+1]
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
	//若找到则返回其在L中的位置，否则返回0
	int pos=0;
	while(pos<L.length&&!(*compare)(L.e[pos],x)) pos++;
	if(pos<L.length) return pos+1;
	return 0;
}

int MergeList(SqList La,SqList Lb,SqList& Lc)
{
	//假设La和Lb均按非递减序排列
	//得到Lc也按非递减序排列
	Lc.e=(ElemType*)malloc((La.length+Lb.length)*sizeof(ElemType));
	if(Lc.e==NULL) return OVERFLOW;
	Lc.listsize=Lc.length=La.length+Lb.length;
	int i=0,j=0,pos=0;
	while(i<La.length&&j<Lb.length){
		if(La.e[i]<Lb.e[j]) Lc.e[pos++]=La.e[i++];
		else Lc.e[pos++]=Lb.e[j++];
	}
	while(i<La.length) Lc.e[pos++]=La.e[i++];;
	while(j<Lb.length) Lc.e[pos++]=Lb.e[j++];
	return OK;
}

void DestroyList(SqList& L)
{
	free(L.e);
	L.length=L.listsize=0;
}

int ClearList(SqList& L)
{
	ElemType* newbase=(ElemType*)realloc(L.e,LIST_INIT_SIZE*sizeof(ElemType));
	if(newbase==NULL) return OVERFLOW;
	L.e=newbase;
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	return OK;
}

int ListEmpty(SqList L)
{
	if(L.length>0) return OK;
	return EMPTY;
}

int ListLength(SqList L)
{
	return L.length;
}

int GetElem(SqList L,int i,ElemType& x)
{
	if(i<1||i>L.length) return ERRO;
	x=L.e[i-1];
	return OK;
}

int PreElem(SqList L,ElemType x1,ElemType& x2)
{
	int pos=LocateElem(L,x1,equal);
	if(pos==0||pos==1) return ERRO;
	x2=L.e[pos-1-1];
	return OK;
}

int NextElem(SqList L,ElemType x1,ElemType& x2)
{
	int pos=LocateElem(L,x1,equal);
	if(pos==0||pos==L.length) return ERRO;
	x2=L.e[pos-1+1];
	return OK;
}

int ShowList(SqList L,int (*visit)(ElemType))
{
	int i;
	for(i=0;i<L.length;i++) if((*visit)(L.e[i])==ERRO)
		return ERRO;
	return OK;
}

/*
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

	SqList L2,L3;
	InitList(L2);
	ElemType x4=2,x5=3,x6=4,x7=5;
	ListInsert(L2,1,x4);ListInsert(L2,2,x5);ListInsert(L2,3,x6);ListInsert(L2,4,x7);
	MergeList(L,L2,L3);
	printf("MergeList:\n");
	for(int i=0;i<L3.length;i++) printf("%d\n",L3.e[i]);
	
	return 0;
}
*/