#include "BalancedBinaryTree.h"

void InOrder(PBSTNode r)
{
	if (r) {
		InOrder(r->lChild);
		printf("%d ", r->x);
		InOrder(r->rChild);
	}
}

void Destroy(PBSTNode r)
{
	if (r) {
		Destroy(r->lChild);
		Destroy(r->rChild);
		free(r);
	}
}

int Max(int a, int b)
{
	if (a >= b) return a;
	return b;
}

int getHigh(PBSTNode r)
{
	if (r == NULL) return -1;
	return r->h;
}

//�����������Ĳ�ƽ���Գ�Ϊ����ת����֮��Ϊ����ת
PBSTNode SingleRotationWithLeft(PBSTNode r)
{
	//���ڽڵ�r�������ӵ������������ߡ�,��֤������������Ϊǰ�������ת
	PBSTNode rl = r->lChild;
	r->lChild = rl->rChild;
	rl->rChild = r;

	rl->h = Max(getHigh(rl->lChild), getHigh(rl->rChild)) + 1;
	r->h = Max(getHigh(r->lChild), getHigh(r->rChild)) + 1;

	return rl;
}

PBSTNode SingleRotationWithRight(PBSTNode r)
{
	PBSTNode rr = r->rChild;
	r->rChild = rr->lChild;
	rr->lChild = r;

	rr->h = Max(getHigh(rr->lChild), getHigh(rr->rChild)) + 1;
	r->h = Max(getHigh(r->lChild), getHigh(r->rChild)) + 1;

	return rr;
}

PBSTNode DoubleRotationWithLeft(PBSTNode r)
{
	r->lChild = SingleRotationWithRight(r->lChild);

	return SingleRotationWithLeft(r);
}

PBSTNode DoubleRotationWithRight(PBSTNode r)
{
	r->rChild = SingleRotationWithLeft(r->rChild);

	return SingleRotationWithRight(r);
}

int InsertBST(PBSTNode& r, int e)
{
	if (r == NULL) {
		//֤���ýڵ㲻���ڣ��ɳɹ�����
		r = (PBSTNode)malloc(sizeof(BSTNode));
		r->h = 0; r->x = e;
		r->lChild = r->rChild = NULL;
		return 1;
	}
	//�ڵ���ڣ��޷�����
	if (r->x == e) return 0;

	if (e < r->x) {
		//������ʧ�ܣ���ֱ���жϷ���
		if (InsertBST(r->lChild, e) == 0) return 0;
		//��Ϊe���뵽���������У���ֻ���������߶ȿ������ӣ��Ӷ������ƻ�ƽ����
		//��Ϊ�ڴ�֮ǰ��һ����ƽ��ģ��������迼�ǻ����2����С�ڵ���-2�����
		if (getHigh(r->lChild) - getHigh(r->rChild) == 2) {
			//��֪ƽ�����ƻ���Ȼ�в���e���𣬹��ж�e����λ�ôӶ�ȷ������ת����˫��ת
			if (e < r->lChild->x)
				r = SingleRotationWithLeft(r);
			else
				r = DoubleRotationWithLeft(r);
		}
	}
	else {
		if (InsertBST(r->rChild, e) == 0) return 0;
		if(getHigh(r->rChild)-getHigh(r->lChild)==2){
			if (e > r->rChild->x)
				r = SingleRotationWithRight(r);
			else
				r = DoubleRotationWithRight(r);
		}
	}
	//��ʱ���µ�ǰ�ڵ�߶�
	r->h = Max(getHigh(r->lChild), getHigh(r->rChild)) + 1;
	return 1;
}

/*int main()
{
	int n;
	while (scanf("%d", &n) == 1 && n > 0) {
		PBSTNode root = NULL;
		for (int i = 0; i < n; i++) {
			int t;
			scanf("%d", &t);
			InsertBST(root, t);

			InOrder(root);
			printf("\n");
		}
		printf("\n");
		Destroy(root);
	}
	return 0;
}*/