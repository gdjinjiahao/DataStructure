#include <stdio.h>
#include <stdlib.h>

#include <stack>
using namespace std;

typedef struct BiNode {
	char data;
	struct BiNode *lChild, *rChild;
}BiTNode,*BiTree;

typedef struct StackNode {
	BiTree r;
	int cnt;
}SNode;

//stack<BiTree> s;
stack<SNode> s;

void CreateBiTree(BiTree& R)
{
	char t = getchar(); getchar();
	if (t == ' '|| t == '\n') {
		R = NULL;
		return;
	}
	BiTree p = (BiTree)malloc(sizeof(BiTNode));
	p->data = t;
	R = p;
	CreateBiTree(p->lChild);
	CreateBiTree(p->rChild);
}

void PreOrder1(BiTree r)
{
	if (r) {
		printf("%c ", r->data);
		PreOrder1(r->lChild);
		PreOrder1(r->rChild);
	}
}

void InOrder1(BiTree r)
{
	if (r) {
		InOrder1(r->lChild);
		printf("%c ", r->data);
		InOrder1(r->rChild);
	}
}

void PostOrder1(BiTree r)
{
	if (r) {
		PostOrder1(r->lChild);
		PostOrder1(r->rChild);
		printf("%c ", r->data);
	}
}

void PreOrder2(BiTree r)
{
	/*while (!s.empty()) s.pop();
	if (r == NULL) return;
	s.push(r);
	while (!s.empty()) {
		BiTree t = s.top();
		s.pop();
		if (t != NULL) {
			printf("%c ", t->data);
			s.push(t->rChild);
			s.push(t->lChild);
		}
	}*/
	while (!s.empty()) s.pop();
	SNode p, t;
	p.r = r; p.cnt = 0;
	s.push(p);
	while (!s.empty()) {
		s.top().cnt++;
		p = s.top();
		if (p.r == NULL) {
			s.pop();
			continue;
		}
		if (p.cnt == 1) {
			printf("%c ", p.r->data);
			t.cnt = 0;
			t.r = p.r->lChild;
			s.push(t);
		}
		else if (p.cnt == 2) {
			t.cnt = 0;
			t.r = p.r->rChild;
			s.push(t);
		}
		else
			s.pop();
	}
}

void InOrder2(BiTree r)
{
	/*while (!s.empty()) s.pop();
	if (r == NULL) return;
	//p表示当前访问的结点
	BiTree p = r;
	while (p || !s.empty()) {
		//对于节点p，若p不为NULL，则应先处理其左子树，故先将p放入栈，若p为空，则显然栈顶节点左子树为空或左子树处理完毕，故打印栈顶元素，之后还需要处理其右子树，故将p->rChild入栈
		if (p) { s.push(p); p = p->lChild; }
		else {
			p = s.top();
			s.pop();
			printf("%c ", p->data);
			p = p->rChild;
		}
	}*/
	while (!s.empty()) s.pop();
	SNode p, t;
	p.r = r; p.cnt = 0;
	s.push(p);
	while (!s.empty()) {
		s.top().cnt++;
		p = s.top();
		if (p.r == NULL) {
			s.pop();
			continue;
		}
		if (p.cnt == 1) {
			t.cnt = 0;
			t.r = p.r->lChild;
			s.push(t);
		}
		else if (p.cnt == 2) {
			printf("%c ", p.r->data);
			t.cnt = 0;
			t.r = p.r->rChild;
			s.push(t);
		}
		else
			s.pop();
	}
}

void PostOrder2(BiTree r)
{
	/*stack<pair<BiTree, int> > ss;
	ss.push(make_pair(r, 0));
	while (!ss.empty()) {
		ss.top().second++;
		pair<BiTree, int> t = ss.top();
		BiTree p = t.first;
		if (!p) {
			ss.pop();
			continue;
		}
		if (t.second == 1) {
			ss.push(make_pair(p->lChild, 0));
		}
		else if (t.second == 2) {
			ss.push(make_pair(p->rChild, 0));
		}
		else {
			printf("%c ", p->data);
			ss.pop();
		}
	}*/
	while (!s.empty()) s.pop();
	SNode p, t;
	p.r = r; p.cnt = 0;
	s.push(p);
	while (!s.empty()) {
		s.top().cnt++;
		p = s.top();
		if (p.r == NULL) {
			s.pop();
			continue;
		}
		if (p.cnt == 1) {
			t.cnt = 0;
			t.r = p.r->lChild;
			s.push(t);
		}
		else if (p.cnt == 2) {
			t.cnt = 0;
			t.r = p.r->rChild;
			s.push(t);
		}
		else {
			printf("%c ", p.r->data);
			s.pop();
		}
	}
}

int main()
{
	BiTree root=NULL;
	//A B C     D E   G     F      
	CreateBiTree(root);

	PreOrder1(root); printf("\n");
	InOrder1(root); printf("\n");
	PostOrder1(root); printf("\n");

	printf("\n");
	PreOrder2(root); printf("\n");
	InOrder2(root); printf("\n");
	PostOrder2(root); printf("\n");

	return 0;
}