#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define M 3

/*
ptr[i]ָ�������������Ԫ�ص�ֵ����key[i]��С��key[i+1]
ע������Ԫ�ز�һ������Ҷ�ڵ��У���Ҷ�ڵ�Ҳ����������Ԫ����Ϣ
*/

typedef struct BTNode {
	int keynum;						//�ؼ�������
	struct BTNode *f;				//���ڵ�ָ��
	int key[M + 1];					//�ؼ��֣���1��ʼ��0�Ų���
	struct BTNode *ptr[M + 1];		//ָ���ӽڵ��ָ�룬��0�ſ�ʼ
}BTNode,*PBTNode;

typedef struct Result {
	//���ҷ��صĽ�����ݽṹ����
	PBTNode p;						//ָ����ҵ��Ľڵ�
	int pos;						//���ҵ�ָ���Ԫ�أ���δ�ҵ�ָ�����λ��
	int flag;						//�ҵ����ı�־
}Result;

Result SearchBTree(PBTNode r, int key)
{
	//pָ��ǰ�ڵ㣬fָ��p�ĸ��ڵ㣬��ĳһʱ��pΪ�գ���ҪôrΪ������Ҫôfָ��ĳһҶ�ڵ�
	PBTNode f = NULL, p = r;
	int yes = 0, i = 1;
	Result ans;
	while (p) {
		for (i = 1; i <= p->keynum; i++) {
			//���жϹؼ����Ƿ���Ҫ���ҵĹؼ���
			if (p->key[i] == key) {
				ans.flag = 1;
				ans.p = p;
				ans.pos = i;
				return ans;
			}
			//��������ȵ�����£�����Ŀ�����ҵ�p->key[i-1]<key<p->key[i]
			if (key < p->key[i]) 
				break;

		}
		//���ҵ�key<p->key[i],��Ҫ����p->ptr[i-1],��û���ҵ�����i=p->keynum+1,Ҫ����p->ptr[p->keynum]��ͬ����i-1
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
	//�����ڣ������ʧ��
	if (t.flag == 1) return 0;
	PBTNode p = t.p;
	int i = t.pos;
	//��pΪNULL�����ʱΪ�������������ڵ㼴��
	if (p == NULL) {
		p = (PBTNode)malloc(sizeof(BTNode));
		p->f = NULL;
		p->key[1] = x;
		//����ÿ���ڵ㣬ָ��������ָ�����飨��ptr���ĳ�ʼ������Ҫ���ҷ��Ѻ�ĸ�ֵ����ΪNULL��ͬ����Ҫ
		memset(p->ptr, NULL, sizeof(p->ptr));
		p->keynum = 1;
		//�ı���ڵ�ָ��
		r = p;
		return 1;
	}

	//���ؼ��ֲ��뵽���ҵ��Ľڵ����Ӧλ��
	p->keynum++;
	for (int j = p->keynum; j > i; j--)
		p->key[j] = p->key[j - 1];
	p->key[i] = x;

	//�ж��Ƿ���Ҫ����
	if (p->keynum == M) {
		PBTNode f;
		//��pΪ������Ȼ�����ٽ��з��ѣ�������ĳһ���Ƚڵ��ؼ�������С��M������Ȼ֮�ϵ�����Ҷ����Ҫ���Ѵ���
		while (p&&p->keynum==M) {
			
			f = p->f;

			int mid = (M + 1) >> 1;
			int vm = p->key[mid];
			
			//���ѷ�Ϊ���֣�һ���ǷǸ��ڵ㣬һ���Ǹ��ڵ�
			if (f == NULL) {
				//��Ҫ���Ѹ��ڵ㣬��ʱ��Ҫ�½������ڵ�
				f = (PBTNode)malloc(sizeof(BTNode));
				PBTNode temp= (PBTNode)malloc(sizeof(BTNode));

				//���ø��ڵ����ֵ
				memset(f->ptr, NULL, sizeof(f->ptr));
				f->f = NULL;
				f->keynum = 1;
				f->key[1] = vm;
				f->ptr[0] = p;
				f->ptr[1] = temp;

				temp->f = f;
				temp->keynum = 0;
				memset(temp->ptr, NULL, sizeof(temp->ptr));
				//��p��mid�Źؼ���ָ�����������temp��ptr[0]�У���Ϊp->key[mid]��Ҫ����p�ĸ��ڵ���
				temp->ptr[0] = p->ptr[mid];
				//������һ����ӣ�һ��Ҫ�޸ķ��ѳ�ȥ�������ĸ��ڵ�ֵ
				if (p->ptr[mid]) p->ptr[mid]->f = temp;
				for (int j = mid + 1; j <= p->keynum; j++) {
					temp->keynum++;
					temp->key[temp->keynum] = p->key[j];
					if (p->ptr[j]) {
						temp->ptr[temp->keynum] = p->ptr[j];
						//ͬ���޸ķ��ѳ�ȥ�������ĸ��ڵ�ֵ
						p->ptr[j]->f = temp;
					}
					
				}
				

				p->f = f;
				p->keynum = mid - 1;
				/*
				�������˵����NULL����Ҫ��
				��.mallocʱ�ڵ��ptrû����NULL
				��ʱ���ܴ����������Ҷ�ڵ�ؼ����µ�ָ��ָ��δ֪�ռ䣬���²���ʱ��дδ֪λ�ã���Ϊ������������NULLΪ��ֹ������

				ע�����Ѻ�ԭʼ�ڵ��ǲ���Ҫ�ú�벿�ֵ�ptrֵΪNULL�ģ���Ϊ��ԭʼ�ڵ�ΪҶ�ڵ㣬�����ǰ��ptrֵ��ΪNULL��
				����ΪҶ�ڵ㣬����ҹ����з����ϸ�keynum���ƣ�������ʵ���ߵ�ptr�д洢��ָ�룬������������������ʡ��
				*/
				//for (int j = mid; j <= M; j++) p->ptr[j] = NULL;

				r = f;
			}
			else {	
				//���ѵ��ǷǸ��ڵ㣬���Ƚ�p�е�mid�Źؼ��ֲ���f�Ĺؼ�����
				for (i = 1; i <= f->keynum; i++) if (vm < f->key[i])
					break;
				for (int j = f->keynum; j >= i; j--) {
					f->key[j + 1] = f->key[j];
					f->ptr[j + 1] = f->ptr[j];
				}
				//�½�f��һ���ӽڵ㣬��ʼ����
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