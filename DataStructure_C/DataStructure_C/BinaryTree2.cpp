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
	//p��ʾ��ǰ���ʵĽ��
	BiTree p = r;
	while (p || !s.empty()) {
		//���ڽڵ�p����p��ΪNULL����Ӧ�ȴ����������������Ƚ�p����ջ����pΪ�գ�����Ȼջ���ڵ�������Ϊ�ջ�������������ϣ��ʴ�ӡջ��Ԫ�أ�֮����Ҫ���������������ʽ�p->rChild��ջ
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

//����������������
//����
void InThreading(BiTree rt, BiTree& pre)
{
	//�ݹ������������ڱ����������޸�ָ�뼴��
	//ע��pre���Ǵ���ĵ�ǰ�ڵ�ĸ��ڵ㣬���ǵ�ǰ�ڵ���������������е�ǰ���ڵ�
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
	//����������������ͷ���
	tr = (BiTree)malloc(sizeof(BiNode));
	if (tr == NULL) return;
	tr->lTag = 0; tr->rTag = 1;
	tr->rChild = tr;

	if (r == NULL) tr->lChild = tr;
	else {
		BiTree pre = tr;
		tr->lChild = r;
		//�ݹ�������
		InThreading(r, pre);
		//���һ���ڵ���Ϊͷ��㣬ͷ�����ָ��ָ��������е�һ���ڵ㣬��ָ��ָ�����һ��
		pre->rTag = 1; pre->rChild = tr;
		tr->rChild = pre;
	}
}

void InOrderTraverse_Thr(BiTree r)
{
	BiTree p = r->lChild;
	while (p != r) {
		//���ڵ�ǰ�ڵ㣬���������������Ȼ����������
		while (p->lTag == 0) p = p->lChild;
		//ȷ����һ��û���������Ľڵ�
		printf("%c ", p->data);
		//��������������ԣ���ǰ�ڵ����������������Ȼ���丸�ڵ���ݣ�����һ�������ǽ�������ʵ�ֵ�
		//��Ȼ������ǰ�ڵ���ָ��Ϊ��������һ��û������������ָ��һ��ָ���丸�ڵ㣬�ù��̾������ϻ���
		while (p->rTag == 1 && p->rChild != r) {
			p = p->rChild;
			printf("%c ", p->data);
		}
		//����������������Ȼ��Ҫ�������������б������ʽ��뵽���������ĸ��ڵ�
		p = p->rChild;
	}
}

//����
void PreThreading(BiTree rt, BiTree& pre)
{
	//�����������������Ϊ��������������ԣ�ǰ��һ���Ǹýڵ�ĸ��ڵ㣬��Ϊ�˷��㽫���һ���ڵ��ͷ���������pre��Ȼ��Ϊ���ñ���
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
	//������������������ͬ�����ܻ��ڵݹ�ǰ�޸�rt��ָ���ֵʹ��ָ��rtǰ�����Ӷ���֮��ݹ�����ָ��ʱ�γ���ѭ��
	//����������֮���Բ�������������������Ϊ����ָ��ĵݹ������޸���ָ��֮ǰ���е�
	//����������֮���Բ���Ҫ�ڵݹ���ָ���ʱ���жϣ�����Ϊ�κ�һ���ڵ��ǰ���ڵ㣬Ҫô���������У������ٻ��ݵ�����ҪôΪ�����Ƚڵ��Ҹýڵ�������Ƚڵ��������ϣ����������ѭ��
	//��׼����Ӧ�ڵݹ�ǰ�ж�ָ���������������ӣ���������¿���ʡ�Ը��ж�
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
		//���ڵ�ǰ���������ҵ���û�����ӵĽڵ�
		while (p->lTag == 0) { printf("%c ", p->data); p = p->lChild;}
		printf("%c ", p->data);
		//����û�����ӵĽڵ㣬������������������Ҫ�����������������ޣ�����ָ��ָ����������������Ϊp = p->rChild;
		p = p->rChild;
	}
}

//����
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
		//�ҵ���ǰ���ĺ�������ĵ�һ���ڵ�
		while (p->lTag == 0) p = p->lChild;
		while (p->rTag == 0) p = p->rChild;
		//���ζ�ȡ��̽ڵ�
		while (p->rTag == 1 && p->rChild != r) {
			printf("%c ", p->data);
			p = p->rChild;
		}
		
		BiTree f = p->Parent;
		//����ǰ�ڵ�ʹ�丸�ڵ���Һ��ӣ���������ϻ���
		//����ǰ�ڵ�ĸ��ڵ����ָ������������������ϻ���
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
		//��ǰ�ڵ�Ϊ�丸�ڵ�����ӣ��Ҹ��ڵ����Һ��ӣ��ʴ�ӡ��ǰ�ڵ㲢������������ѭ������
		printf("%c ", p->data);
		if (f == r) break;
		p = f->rChild;
	}
}

/*
���ڸ����ڵ�Ѱ�Ҹýڵ��ǰ��������⣬��ָ��Ϊ��������һ��������ָ��Ϊ���ӣ���ǰ�����һ���ں���Ϊ���������У���΢����һ�¼������
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

	//�ݹ����
	PreOrder1(root); printf("\n");
	InOrder1(root); printf("\n");
	PostOrder1(root); printf("\n");
	printf("\n");

	//�ǵݹ����
	PreOrder2(root); printf("\n");
	InOrder2(root); printf("\n");
	PostOrder2(root); printf("\n");
	printf("\n");

	//������������
	BiTree thr_root = NULL;
	//����
	//nOrderThreading(root, thr_root);
	//InOrderTraverse_Thr(thr_root);
	//PreOrderThreading(root, thr_root);
	//PreOrderTraverse_Thr(thr_root);
	//PostOrderThreading(root, thr_root);
	//PostOrderTraverse_Thr(thr_root);
	printf("\n");

	return 0;
}*/