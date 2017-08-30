#define OVERFLOW -2
#define ERRO -1
#define EMPTY 0
#define OK 1

#define LIST_INIT_SIZE 100 //���Ա��ʼ����
#define LISTINCREMENT 10 //��������
#define ElemType int

typedef struct LinearList{
	ElemType *e; //���Ա��ַ
	int length; //���Ա�Ԫ�ظ���
	int listsize; //���䳤��
}SqList;

int equal(ElemType a,ElemType b);
int greater(ElemType a,ElemType b);
int smaller(ElemType a,ElemType b);
int visit(ElemType x);

int InitList(SqList& L);

int ListInsert(SqList& L,int i,ElemType x);

int ListDelete(SqList& L,int i,ElemType& x);

int LocateElem(SqList& L,ElemType x,int (*compare)(ElemType,ElemType));

int MergeList(SqList La,SqList Lb,SqList& Lc);

void DestroyList(SqList& L);

int ClearList(SqList& L);

int ListEmpty(SqList L);

int ListLength(SqList L);

int GetElem(SqList L,int i,ElemType& x);

int PreElem(SqList L,ElemType x1,ElemType& x2);

int NextElem(SqList L,ElemType x1,ElemType& x2);

int ShowList(SqList L,int (*visit)(ElemType));