#include <stack>
using namespace std;

typedef struct BiNode {
	char data;
	struct BiNode *lChild, *rChild, *Parent;
	int lTag, rTag;//0表示孩子，1表示线索
}BiTNode, *BiTree;

typedef struct StackNode {
	BiTree r;
	int cnt;
}SNode;

//stack<BiTree> s;
stack<SNode> s;

void CreateBiTree(BiTree& R, BiTree f);

void PreOrder1(BiTree r);

void InOrder1(BiTree r);

void PostOrder1(BiTree r);

void PreOrder2(BiTree r);

void InOrder2(BiTree r);

void PostOrder2(BiTree r);

//线索化二叉树操作
//中序
void InThreading(BiTree rt, BiTree& pre);

void InOrderThreading(BiTree r, BiTree& tr);

void InOrderTraverse_Thr(BiTree r);

//先序
void PreThreading(BiTree rt, BiTree& pre);

void PreOrderThreading(BiTree r, BiTree& tr);

void PreOrderTraverse_Thr(BiTree r);

//后序
void PostThreading(BiTree rt, BiTree& pre);

void PostOrderThreading(BiTree r, BiTree& tr);

void PostOrderTraverse_Thr(BiTree r);

