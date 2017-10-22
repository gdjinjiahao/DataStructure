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
	//���ҵ��ؼ���Ϊkey�Ľڵ㣬��pָ��ýڵ㣬����ָ����һ�η��ʵĽڵ�
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
	//�Ѵ��ڣ��޷�����
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
	//�Ȳ���Ҫɾ���Ľڵ㣬���Ҳ�������0
	if (r == NULL) return 0;
	if (e < r->x) return DeleteBST(r->lChild, e);
	else if (e > r->x) return DeleteBST(r->rChild, e);
	else {
		//ɾ����Ϊ���������1.��������2.ֻ��һ��������3.����������
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
			//��������������������Ҹýڵ����������ڵ����ýڵ㣬��ɾ�������������ڵ�
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