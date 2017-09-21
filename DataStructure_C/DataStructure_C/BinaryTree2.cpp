#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include "BinaryTree2.h"
using namespace std;


void CreateBiTree(BiTree& R, BiTree f)
{
	char t = getchar(); getchar();
	if (t == ' '|| t == '\n') {
		R = NULL;
		return;
	}
	BiTree p = (BiTree)malloc(sizeof(BiTNode));
	R = p;
	p->data = t;
	p->lTag = p->rTag = 0;
	p->Parent = f;
	CreateBiTree(p->lChild, p);
	CreateBiTree(p->rChild, p);
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

//线索化二叉树操作
//中序
void InThreading(BiTree rt, BiTree& pre)
{
	//递归的中序遍历，在遍历操作处修改指针即可
	//注意pre不是代表的当前节点的父节点，而是当前节点在中序遍历序列中的前驱节点
	if (rt == NULL) return;

	InThreading(rt->lChild, pre);
	if (rt->lChild == NULL) {
		rt->lTag = 1;
		rt->lChild = pre;
	}
	if (pre->rChild == NULL) {
		pre->rTag = 1;
		pre->rChild = rt;
	}
	pre = rt;
	InThreading(rt->rChild, pre);
}

void InOrderThreading(BiTree r, BiTree& tr)
{
	//构造线索二叉树的头结点
	tr = (BiTree)malloc(sizeof(BiNode));
	if (tr == NULL) return;
	tr->lTag = 0; tr->rTag = 1;
	tr->rChild = tr;

	if (r == NULL) tr->lChild = tr;
	else {
		BiTree pre = tr;
		tr->lChild = r;
		//递归线索化
		InThreading(r, pre);
		//最后一个节点后继为头结点，头结点左指针指向遍历序列第一个节点，右指针指向最后一个
		pre->rTag = 1; pre->rChild = tr;
		tr->rChild = pre;
	}
}

void InOrderTraverse_Thr(BiTree r)
{
	BiTree p = r->lChild;
	while (p != r) {
		//对于当前节点，若其有左子树则必然不会对其访问
		while (p->lTag == 0) p = p->lChild;
		//确定出一个没有左子树的节点
		printf("%c ", p->data);
		//对于中序遍历而言，当前节点若无右子树，则必然向其父节点回溯，而这一回溯正是借助线索实现的
		//显然，若当前节点右指针为线索，则一定没有右子树，右指针一定指向其父节点，该过程就是向上回溯
		while (p->rTag == 1 && p->rChild != r) {
			p = p->rChild;
			printf("%c ", p->data);
		}
		//若有右子树，则显然需要对其右子树进行遍历，故进入到其右子树的根节点
		p = p->rChild;
	}
}

//先序
void PreThreading(BiTree rt, BiTree& pre)
{
	//类似中序遍历，但因为对于先序遍历而言，前驱一定是该节点的父节点，但为了方便将最后一个节点和头结点相连，pre依然设为引用变量
	if (rt == NULL) return;
	if (rt->lChild == NULL) {
		rt->lTag = 1;
		rt->lChild = pre;
	}
	if (pre->rChild == NULL) {
		pre->rTag = 1;
		pre->rChild = rt;
	}
	pre = rt;
	//先序遍历和中序遍历不同，可能会在递归前修改rt左指针的值使其指向rt前驱，从而在之后递归其左指针时形成死循环
	//中序线索化之所以不会出现这种情况，是因为对左指针的递归是在修改左指针之前进行的
	//中序线索化之所以不需要在递归右指针的时候判断，是因为任何一个节点的前驱节点，要么在左子树中（不会再回溯到），要么为其祖先节点且该节点必在祖先节点右子树上，不会出现死循环
	//标准程序应在递归前判断指针是线索还是连接，多数情况下可以省略该判断
	if (rt->lTag == 0) PreThreading(rt->lChild, pre);
	if (rt->rTag == 0) PreThreading(rt->rChild, pre);
}

void PreOrderThreading(BiTree r, BiTree& tr)
{
	tr = (BiTree)malloc(sizeof(BiNode));
	tr->lTag = 0; tr->rTag = 1;
	tr->rChild = tr;
	if (r == NULL) tr->lChild = tr;
	else {
		BiTree pre = tr;
		tr->lChild = r;
		PreThreading(r, pre);
		pre->rTag = 1; pre->rChild = tr;
		tr->rChild = pre;
	}
}

void PreOrderTraverse_Thr(BiTree r)
{
	BiTree p = r->lChild;
	while (p != r) {
		//对于当前子树，先找到其没有左孩子的节点
		while (p->lTag == 0) { printf("%c ", p->data); p = p->lChild;}
		printf("%c ", p->data);
		//对于没有左孩子的节点，若其有右子树，则需要遍历其右子树，若无，则右指针指向后继子树，操作均为p = p->rChild;
		p = p->rChild;
	}
}

//后序
void PostThreading(BiTree rt, BiTree& pre)
{
	if (rt == NULL) return;

	PostThreading(rt->lChild,pre);
	PostThreading(rt->rChild, pre);

	if (rt->lChild == NULL) {
		rt->lTag = 1;
		rt->lChild = pre;
	}
	if (pre->rChild == NULL) {
		pre->rTag = 1;
		pre->rChild = rt;
	}
	pre = rt;
}

void PostOrderThreading(BiTree r, BiTree& tr)
{
	tr = (BiTree)malloc(sizeof(BiNode));
	tr->lTag = 0; tr->rChild = tr;
	tr->rTag = 1;
	if(r==NULL) tr->lChild = tr;
	else {
		r->Parent = tr;
		BiTree pre = tr;
		tr->lChild = r;
		PostThreading(tr->lChild, pre);
		pre->rTag = 1; pre->rChild = tr;
		tr->rChild = pre;
	}
}

void PostOrderTraverse_Thr(BiTree r)
{
	BiTree p = r->lChild;
	while (p != r) {
		//找到当前树的后序遍历的第一个节点
		while (p->lTag == 0) p = p->lChild;
		while (p->rTag == 0) p = p->rChild;
		//依次读取后继节点
		while (p->rTag == 1 && p->rChild != r) {
			printf("%c ", p->data);
			p = p->rChild;
		}
		
		BiTree f = p->Parent;
		//若当前节点使其父节点的右孩子，则继续向上回溯
		//若当前节点的父节点的右指针是线索，则继续往上回溯
		while (f != r && (f->rChild == p || f->rTag == 1)) {
			printf("%c ", p->data);
			if (f->rChild == p) {
				p = f;
				f = f->Parent;
			}
			else {
				p = f;
				f = f->rChild;
			}
		}
		//当前节点为其父节点的左孩子，且父节点有右孩子，故打印当前节点并对右子树进行循环操作
		printf("%c ", p->data);
		if (f == r) break;
		p = f->rChild;
	}
}

/*
对于给定节点寻找该节点的前驱后继问题，若指针为线索，则一步可求，若指针为孩子，则前驱后继一定在孩子为根的子树中，稍微处理一下即可求得
*/


/*int main()
{
	BiTree root=NULL;
	//A B C     D E   G     F      
	//A B C     D   E      
	//A B     C     
	//A B C         
	CreateBiTree(root, NULL);
	printf("\n");

	//递归遍历
	PreOrder1(root); printf("\n");
	InOrder1(root); printf("\n");
	PostOrder1(root); printf("\n");
	printf("\n");

	//非递归遍历
	PreOrder2(root); printf("\n");
	InOrder2(root); printf("\n");
	PostOrder2(root); printf("\n");
	printf("\n");

	//线索化二叉树
	BiTree thr_root = NULL;
	//中序
	//nOrderThreading(root, thr_root);
	//InOrderTraverse_Thr(thr_root);
	//PreOrderThreading(root, thr_root);
	//PreOrderTraverse_Thr(thr_root);
	//PostOrderThreading(root, thr_root);
	//PostOrderTraverse_Thr(thr_root);
	printf("\n");

	return 0;
}*/