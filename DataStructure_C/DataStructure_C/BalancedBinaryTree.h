#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode {
	int x;
	int h;
	struct BSTNode *lChild, *rChild;
}BSTNode, *PBSTNode;

void InOrder(PBSTNode r);

void Destroy(PBSTNode r);

int Max(int a, int b);

int getHigh(PBSTNode r);

PBSTNode SingleRotationWithLeft(PBSTNode r);

PBSTNode SingleRotationWithRight(PBSTNode r);

PBSTNode DoubleRotationWithLeft(PBSTNode r);

PBSTNode DoubleRotationWithRight(PBSTNode r);

int InsertBST(PBSTNode& r, int e);