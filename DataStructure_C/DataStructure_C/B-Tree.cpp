#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define M 3

/*
ptr[i]指向的子树中所有元素的值大于key[i]且小于key[i+1]
注意数据元素不一定都在叶节点中，非叶节点也保存有数据元素信息
*/

typedef struct BTNode {
	int keynum;						//关键字数量
	struct BTNode *f;				//父节点指针
	int key[M + 1];					//关键字，从1开始，0号不用
	struct BTNode *ptr[M + 1];		//指向子节点的指针，从0号开始
}BTNode,*PBTNode;

typedef struct Result {
	//查找返回的结果数据结构定义
	PBTNode p;						//指向查找到的节点
	int pos;						//若找到指向该元素，若未找到指向插入位置
	int flag;						//找到与否的标志
}Result;

Result SearchBTree(PBTNode r, int key)
{
	//p指向当前节点，f指向p的父节点，若某一时刻p为空，则要么r为空树，要么f指向某一叶节点
	PBTNode f = NULL, p = r;
	int yes = 0, i = 1;
	Result ans;
	while (p) {
		for (i = 1; i <= p->keynum; i++) {
			//先判断关键字是否是要查找的关键字
			if (p->key[i] == key) {
				ans.flag = 1;
				ans.p = p;
				ans.pos = i;
				return ans;
			}
			//不考虑相等的情况下，查找目标是找到p->key[i-1]<key<p->key[i]
			if (key < p->key[i]) 
				break;

		}
		//若找到key<p->key[i],则要进入p->ptr[i-1],若没有找到，则i=p->keynum+1,要进入p->ptr[p->keynum]，同样是i-1
		f = p;
		p = p->ptr[i-1];
	}
	ans.flag = 0;
	ans.p = f;
	ans.pos = i;
	return ans;
}

int InsertBTree(PBTNode& r, int x)
{
	Result t = SearchBTree(r, x);
	//若存在，则插入失败
	if (t.flag == 1) return 0;
	PBTNode p = t.p;
	int i = t.pos;
	//若p为NULL，则此时为空树，构建根节点即可
	if (p == NULL) {
		p = (PBTNode)malloc(sizeof(BTNode));
		p->f = NULL;
		p->key[1] = x;
		//对于每个节点，指向子树的指针数组（即ptr）的初始化很重要，且分裂后的赋值（置为NULL）同样重要
		memset(p->ptr, NULL, sizeof(p->ptr));
		p->keynum = 1;
		//改变根节点指针
		r = p;
		return 1;
	}

	//将关键字插入到查找到的节点的相应位置
	p->keynum++;
	for (int j = p->keynum; j > i; j--)
		p->key[j] = p->key[j - 1];
	p->key[i] = x;

	//判断是否需要分裂
	if (p->keynum == M) {
		PBTNode f;
		//若p为空则显然无需再进行分裂，若到达某一祖先节点后关键字数量小于M，则显然之上的祖先叶不需要分裂处理
		while (p&&p->keynum==M) {
			
			f = p->f;

			int mid = (M + 1) >> 1;
			int vm = p->key[mid];
			
			//分裂分为两种，一种是非根节点，一种是根节点
			if (f == NULL) {
				//需要分裂根节点，此时需要新建两个节点
				f = (PBTNode)malloc(sizeof(BTNode));
				PBTNode temp= (PBTNode)malloc(sizeof(BTNode));

				//设置根节点各项值
				memset(f->ptr, NULL, sizeof(f->ptr));
				f->f = NULL;
				f->keynum = 1;
				f->key[1] = vm;
				f->ptr[0] = p;
				f->ptr[1] = temp;

				temp->f = f;
				temp->keynum = 0;
				memset(temp->ptr, NULL, sizeof(temp->ptr));
				//将p中mid号关键字指向的子树放入temp的ptr[0]中，因为p->key[mid]需要放入p的父节点中
				temp->ptr[0] = p->ptr[mid];
				//这里是一个大坑，一定要修改分裂出去的子树的父节点值
				if (p->ptr[mid]) p->ptr[mid]->f = temp;
				for (int j = mid + 1; j <= p->keynum; j++) {
					temp->keynum++;
					temp->key[temp->keynum] = p->key[j];
					if (p->ptr[j]) {
						temp->ptr[temp->keynum] = p->ptr[j];
						//同理，修改分裂出去的子树的父节点值
						p->ptr[j]->f = temp;
					}
					
				}
				

				p->f = f;
				p->keynum = mid - 1;
				/*
				这里举例说明置NULL的重要性
				例.malloc时节点的ptr没有置NULL
				此时可能存在新申请的叶节点关键字下的指针指向未知空间，导致查找时读写未知位置，因为查找是以遇到NULL为终止条件的

				注：分裂后原始节点是不需要置后半部分的ptr值为NULL的，因为若原始节点为叶节点，则分裂前后ptr值均为NULL，
				若不为叶节点，则查找过程中访问严格被keynum控制，不会访问到后边的ptr中存储的指针，所以下面这条语句可以省略
				*/
				//for (int j = mid; j <= M; j++) p->ptr[j] = NULL;

				r = f;
			}
			else {	
				//分裂的是非根节点，首先将p中的mid号关键字插入f的关键字中
				for (i = 1; i <= f->keynum; i++) if (vm < f->key[i])
					break;
				for (int j = f->keynum; j >= i; j--) {
					f->key[j + 1] = f->key[j];
					f->ptr[j + 1] = f->ptr[j];
				}
				//新建f的一个子节点，开始分裂
				PBTNode temp = (PBTNode)malloc(sizeof(BTNode));

				f->keynum++;
				f->key[i] = vm;
				f->ptr[i] = temp;

				temp->f = f;
				temp->keynum = 0;
				memset(temp->ptr, NULL, sizeof(temp->ptr));
				temp->ptr[0] = p->ptr[mid];
				if (p->ptr[mid]) p->ptr[mid]->f = temp;
				for (int j = mid + 1; j <= p->keynum; j++) {
					temp->keynum++;
					temp->key[temp->keynum] = p->key[j];
					if (p->ptr[j]) {
						temp->ptr[temp->keynum] = p->ptr[j];
						p->ptr[j]->f = temp;
					}
				}
				

				p->keynum = mid - 1;
				//for (int j = mid; j <= M; j++) p->ptr[j] = NULL;
			}
			p = f;
		}
	}
	return 1;
}

int main()
{
	PBTNode rt = NULL;
	Result ans;
	InsertBTree(rt, 5);
	InsertBTree(rt, 10);
	InsertBTree(rt, 15);
	InsertBTree(rt, 1);
	InsertBTree(rt, 2);
	InsertBTree(rt, 3);
	InsertBTree(rt, 4);
	InsertBTree(rt, 9);
	InsertBTree(rt, 17);
	InsertBTree(rt, 20);
	InsertBTree(rt, 13);
	InsertBTree(rt, 7);
	InsertBTree(rt, 19);
	InsertBTree(rt, 6);
	InsertBTree(rt, 22);

	ans = SearchBTree(rt, 5);

	printf("%d\n", ans.flag);

	ans = SearchBTree(rt, 15);

	printf("%d\n", ans.flag);

	ans = SearchBTree(rt, 99);

	printf("%d\n", ans.flag);

	return 0;
}