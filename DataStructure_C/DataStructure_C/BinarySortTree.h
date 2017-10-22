#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int x;
	struct TreeNode *lChild, *rChild;
}TNode, *PTNode;

void InOrder(PTNode r);

void Destroy(PTNode r);

int SearchBST(PTNode r, int key, PTNode& f, PTNode& p);

int InsertBST(PTNode& r, int e);

int DeleteBST(PTNode& r, int e);