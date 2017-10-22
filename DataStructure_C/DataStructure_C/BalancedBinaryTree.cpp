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

//消除左子树的不平衡性成为左旋转，反之成为右旋转
PBSTNode SingleRotationWithLeft(PBSTNode r)
{
	//对于节点r，其左孩子的左子树过“高”,保证二叉树有序性为前提进行旋转
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
		//证明该节点不存在，可成功插入
		r = (PBSTNode)malloc(sizeof(BSTNode));
		r->h = 0; r->x = e;
		r->lChild = r->rChild = NULL;
		return 1;
	}
	//节点存在，无法插入
	if (r->x == e) return 0;

	if (e < r->x) {
		//若插入失败，则直接中断返回
		if (InsertBST(r->lChild, e) == 0) return 0;
		//因为e插入到了左子树中，故只有左子树高度可能增加，从而可能破坏平衡性
		//因为在此之前树一定是平衡的，所以无需考虑会大于2或者小于等于-2的情况
		if (getHigh(r->lChild) - getHigh(r->rChild) == 2) {
			//已知平衡性破坏必然有插入e引起，故判断e插入位置从而确定单旋转还是双旋转
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
	//及时更新当前节点高度
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