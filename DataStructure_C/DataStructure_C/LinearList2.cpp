#include <stdio.h>
#include <stdlib.h>

#define OVERFLOW -2
#define ERRO -1
#define EMPTY 0
#define OK 1

#define ElemType int

typedef struct LNode{
	ElemType e;
	struct LNode* next;
}LNode,*LinkList;

int InitList(LinkList& L)
{
	//带头结点头指针的链表
	L=(LinkList)malloc(sizeof(LNode));
	if(L==NULL) return OVERFLOW;
	L->next=NULL;
	return OK;
}

void ShowList(LinkList L)
{
	LinkList p=L->next;
	while(p!=NULL){
		printf("%d ",p->e);
		p=p->next;
	}
	printf("\n");
}

int ListInsert(LinkList& L,int i,ElemType x)
{
	//在第i个元素前插入x
	LinkList q;
	q=(LinkList)malloc(sizeof(LNode));
	if(q==NULL) return OVERFLOW;
	if(i<1) return ERRO;
	LinkList p=L;
	int j=0;
	while(j<i-1){
		if(p==NULL) return ERRO;
		p=p->next;
		j++;
	}
	q->e=x;
	q->next=p->next;
	p->next=q;
	return OK;
}

int ListDelete(LinkList& L,int i,ElemType& x)
{
	if(i<1) return ERRO;
	LinkList p=L;
	int j=0;
	while(j<i-1){
		if(p==NULL) return ERRO;
		p=p->next;
		j++;
	}
	if(p->next==NULL) return ERRO;
	LinkList q=p->next;
	x=q->e;
	p->next=q->next;
	free(q);
	return OK;
}

int main()
{
	LinkList L;

	InitList(L);

	ElemType x1=1,x2=2,x3=3;
	printf("Insert:\n");
	ListInsert(L,1,x1);ListInsert(L,2,x2);ListInsert(L,3,x3);
	ShowList(L);

	ElemType d;
	ListDelete(L,2,d);
	printf("Delete:\n");
	printf("%d\n",d);
	ShowList(L);

	return 0;
}