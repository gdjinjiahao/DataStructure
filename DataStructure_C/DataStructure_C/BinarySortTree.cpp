#include "BinarySortTree.h"

void InOrder(PTNode r)
{
	if (r) {
		InOrder(r->lChild);
		printf("%d ", r->x);
		InOrder(r->rChild);
	}
}

void Destroy(PTNode r)
{
	if (r) {
		Destroy(r->lChild);
		Destroy(r->rChild);
		free(r);
	}
}

int SearchBST(PTNode r, int key, PTNode& f, PTNode& p)
{
	//若找到关键字为key的节点，则p指向该节点，否则指向上一次访问的节点
	if (r == NULL) {
		p = f;
		return 0;
	}
	if (r->x == key) {
		p = r;
		return 1;
	}
	else if (key < r->x) SearchBST(r->lChild, key, f = r, p);
	else SearchBST(r->rChild, key, f = r, p);
}

int InsertBST(PTNode& r, int e)
{
	PTNode p, f = NULL;
	//已存在，无法插入
	if (SearchBST(r, e, f, p) == 1) return 0;

	PTNode temp = (PTNode)malloc(sizeof(TNode));
	temp->x = e;
	temp->lChild = temp->rChild = 0;
	
	if (r == NULL) r = temp;
	else {
		if (e < p->x) p->lChild = temp;
		else p->rChild = temp;
	}
	return 1;
}

int DeleteBST(PTNode& r, int e)
{
	//先查找要删除的节点，若找不到返回0
	if (r == NULL) return 0;
	if (e < r->x) return DeleteBST(r->lChild, e);
	else if (e > r->x) return DeleteBST(r->rChild, e);
	else {
		//删除分为三种情况，1.无子树，2.只有一个子树，3.有两个子树
		if (r->rChild == NULL) {
			PTNode p = r;
			r = r->lChild;
			free(p);
		}
		else if (r->lChild == NULL) {
			PTNode p = r;
			r = r->rChild;
			free(p);
		}
		else {
			//对于两个子树的情况，找该节点左子树最大节点代替该节点，并删除左子树中最大节点
			PTNode p = r->lChild;
			PTNode f = r;
			while (p->rChild) { f = p; p = p->rChild; }
			if (f == r) {
				p->rChild = r->rChild;
				r = p;
				free(f);
			}
			else {
				r->x = p->x;
				f->rChild = p->lChild;
				free(p);
			}
		}
		return 1;
	}
}

/*
6
5 2 7 1 4 3
*/

/*int main()
{
	int n;
	while (scanf("%d", &n) == 1 && n > 0) {
		PTNode root = NULL;
		for (int i = 0; i < n; i++) {
			int temp;
			scanf("%d", &temp);
			InsertBST(root, temp);
		}

		InOrder(root);
		printf("\n");

		int m;
		scanf("%d", &m);
		while (m--) {
			int e;
			scanf("%d", &e);
			DeleteBST(root, e);
			InOrder(root);
			printf("\n");
		}
		Destroy(root);
	}
}*/