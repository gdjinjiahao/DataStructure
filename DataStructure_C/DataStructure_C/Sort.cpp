#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000
#define MAX_VALUE 0x7fffffff

//���������õ�������ڵ㶨��
typedef struct RSElem {
	int e;
	struct RSElem *next;
}RSElem,*PRSElem;

int e[MAX_SIZE], n;

void Straight_Isertion_Sort(int l, int r)
{
	for (int i = l + 1; i <= r; i++) {
		int x = e[i];
		int j = i - 1;
		while (j >= l&&e[j] > x) {
			e[j + 1] = e[j];
			j--;
		}
		e[j+1] = x;
	}
}

void Binary_Insertion_Sort(int l, int r) 
{
	for (int i = l + 1; i <= r; i++) {
		int x = e[i];
		int low = l, high = i - 1;
		//�˴��Ķ��ֲ���Ŀ���ҵ�high֮�������Ԫ����Ҫ����һλ
		//��x<e[mid]����mid֮���Ԫ�ذ���mid��Ҫ���ƣ�����high=mid-1
		//��x>=e[mid]����mid֮ǰ��Ԫ�ذ���midһ�������ú��ƣ���low=mid-1
		while (low <= high) {
			int mid = (low + high) >> 1;
			if (x < e[mid]) high = mid - 1;
			else low = mid + 1;
		}
		for (int j = i - 1; j > high; j--) e[j + 1] = e[j];
		e[high + 1] = x;
	}
}

void Shell_Sort(int l, int r)
{
	//�������б����ɴ�С������Сֵ����Ϊ1
	int dlta[3] = { 5,3,1 };
	//kö������
	for (int k = 0; k < 3; k++) {
		int dk = dlta[k];
		//���������Ǵ����еڶ���Ԫ�ؿ�ʼ������i��l+dk��ʼ
		for (int i = l + dk; i <= r; i++) {
			int x = e[i];
			int j = i - dk;
			//���Ӧ���в���
			while (j >= l && e[j] > x) {
				e[j + dk] = e[j];
				j -= dk;
			}
			e[j + dk] = x;
		}
	}
}

void swap(int& a, int& b)
{
	int t = a;
	a = b;
	b = t;
}

void Bubble_Sort(int l, int r)
{
	for (int i = r; i >= l + 1; i--)
		for (int j = l + 1; j <= i; j++) if (e[j - 1] > e[j])
			swap(e[j - 1], e[j]);
}

void Quick_Sort(int l, int r)
{
	if (l >= r) return;
	int x = e[l];
	int low = l, high = r;
	while (low < high) {
		while (low < high&&e[high] >= x) high--;
		e[low] = e[high];
		while (low < high&&e[low] < x) low++;
		e[high] = e[low];
	}
	e[low] = x;
	Quick_Sort(l, low - 1);
	Quick_Sort(low + 1, r);
}

void Simple_Selection_Sort(int l, int r)
{
	for (int i = l; i < r; i++) {
		int p = i, t = e[i];
		for (int j = i + 1; j <= r; j++) if (t > e[j]) {
			p = j;
			t = e[j];
		}
		swap(e[i], e[p]);
	}
}

//Tree_Selection_Sort
//���ڵ���������������С��Ԫ�أ�������˼�룬ÿ��ѡ��һ��Ԫ�غ󣬽���Ӧ��Ҷ�ڵ��޸�ΪMAX_VALUE,֮���������ε������ڵ�
int BuildTree(int rt, int l, int r, int tree[], int pos[])
{
	if (l == r) {
		tree[rt] = e[l];
		pos[l] = rt;
		return e[l];
	}

	int mid = (l + r) >> 1;
	int vl = BuildTree(rt << 1, l, mid, tree, pos);
	int vr = BuildTree(rt << 1 | 1, mid + 1, r, tree, pos);
	if (vl > vr) tree[rt] = vr;
	else tree[rt] = vl;
	return tree[rt];
}

int getMin(int l, int r, int tree[], int pos[], int temp[])
{
	int ans = tree[1];
	int p=-1;
	for (int i = l; i <= r; i++) if (temp[i] == ans) {
		temp[i] = MAX_VALUE;
		p = pos[i];
		break;
	}
	tree[p] = MAX_VALUE;
	int f = p >> 1;
	while (f) {
		if (tree[f << 1] > tree[f << 1 | 1]) tree[f] = tree[f << 1 | 1];
		else tree[f] = tree[f << 1];
		f = f >> 1;
	}
	return ans;
}

void Tree_Selection_Sort(int l, int r)
{
	int tree[MAX_SIZE << 2];
	int pos[MAX_SIZE];
	int temp[MAX_SIZE];
	for (int i = l; i <= r; i++) temp[i] = e[i];
	int len = MAX_SIZE << 2;
	for (int i = 0; i < len; i++) tree[i] = MAX_VALUE;
	BuildTree(1, l, r, tree, pos);
	for (int i = l; i <= r; i++) 
		e[i] = getMin(l, r, tree, pos, temp);
}

//������
void Adjust_Heap(int *heap, int rt, int n)
{
	//����rtΪ�����Ӷѽ������ǵ������ѵı߽�Ϊn
	int x = heap[rt];
	int p;
	for (p = rt << 1; p <= n; p <<= 1) {
		if (p + 1 <= n&&heap[p + 1] > heap[p]) p++;
		if (heap[p] <= x) break;
		heap[rt] = heap[p];
		//������ֹ������мǱ��浱ǰ����Ľڵ㣬pʹ̽����ӽڵ�
		rt = p;
	}
	//rt��ʾ֮ǰ����Ľڵ㣬p��ʾ̽����ӽڵ㣬��һ���ڷ�Χ��
	heap[rt] = x;
}

void Heap_Sort()
{
	//����󶥶ѣ�ÿ�ν��Ѷ�Ԫ�غͶ���������Ԫ�ؽ��������ǵ�������󼴿ɹ���ǵݼ�����
	for (int i = n >> 1; i >= 1; i--)
		Adjust_Heap(e, i, n);

	for (int i = n; i >= 1; i--) {
		swap(e[1], e[i]);
		Adjust_Heap(e, 1, i-1);
	}
}

//�鲢������Ҫ��������
void Merging_Sort(int temp[], int l, int r) {
	if (l == r) return;

	int mid = (l + r) >> 1;
	Merging_Sort(temp, l, mid);
	Merging_Sort(temp, mid + 1, r);

	for (int i = l; i <= r; i++) temp[i] = e[i];

	int i1 = l, i2 = mid + 1, pos = l;
	while (i1 <= mid&&i2 <= r) {
		if (temp[i1] <= temp[i2]) e[pos++] = temp[i1++];
		else e[pos++] = temp[i2++];
	}
	while(i1<=mid) e[pos++] = temp[i1++];
	while (i2 <= r) e[pos++] = temp[i2++];
}

void RadixSort(int l,int r)
{
	/*
	10
	278 109 63 930 589 184 505 269 8 83
	*/
	RSElem head;
	head.next = NULL;
	PRSElem cur = &head;
	//��ʼ������
	for (int i = l; i <= r; i++) {
		PRSElem t = (PRSElem)malloc(sizeof(RSElem));
		t->e = e[i];
		t->next = cur->next;
		cur->next = t;
		cur = t;
	}

	PRSElem front[10], last[10];

	//3Ϊ�ؼ������������������λ���Ϊ3λ��
	for (int i = 0; i < 3; i++) {
		cur = head.next;
		int a=1;
		for (int j = 0; j < i; j++) a *= 10;
		for (int i = 0; i < 10; i++) front[i] = last[i] = NULL;

		//���䣬�൱����Ԫ�ؽ�����Ӧ����
		while (cur) {
			int id = (cur->e) / a % 10;
			PRSElem temp = cur;
			cur = cur->next;

			if (front[id] == NULL) {
				front[id] = temp;
				last[id] = temp;
				temp->next = NULL;
			}
			else {
				temp->next = NULL;
				last[id]->next = temp;
				last[id] = temp;
			}
		}

		//�ռ�������Ϊ���ؼ��ִ������γ��ӣ����ڶ��б�������ʣ�ֱ���޸Ķ�ͷ�Ͷ�βָ��������Ӽ���
		head.next = NULL;
		cur = &head;
		for (int j = 0; j < 10; j++) if (front[j]) {
			cur->next = front[j];
			cur = last[j];
			cur->next = NULL;
		}
	}

	//��ӡ�������������ռ�
	cur = head.next;
	while (cur) {
		printf("%d ", cur->e);
		PRSElem temp = cur;
		cur = cur->next;
		free(temp);
	}
	printf("\n");
}

/*
8
49 38 65 97 76 13 27 49
10
1 2 3 4 5 6 7 8 9 10
10
10 9 8 7 6 5 4 3 2 1
10
5 9 8 3 10 2 6 1 4 7
5
1 1 1 1 1
5
1 1 1 1 0
5
0 1 1 1 1
1
1
*/

int main()
{
	int temp[MAX_SIZE];
	while (scanf("%d", &n) == 1 && n > 0) {
		for (int i = 1; i <= n; i++) scanf("%d", e + i);

		//Straight_Isertion_Sort(1, n);

		//Binary_Insertion_Sort(1, n);

		//Shell_Sort(1, n);

		//Bubble_Sort(1, n);

		//Quick_Sort(1, n);

		//Simple_Selection_Sort(1, n);

		//Tree_Selection_Sort(1, n);

		//Heap_Sort();

		//Merging_Sort(temp, 1, n);

		//RadixSort(1, n);

		//for (int i = 1; i <= n; i++) printf("%d ", e[i]);
		//printf("\n");
	}

	return 0;
}