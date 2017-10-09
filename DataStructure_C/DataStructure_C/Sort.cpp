#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000
#define MAX_VALUE 0x7fffffff

//基数排序用到的链表节点定义
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
		//此处的二分查找目的找到high之后的所有元素需要后移一位
		//若x<e[mid]，则mid之后的元素包括mid都要后移，所以high=mid-1
		//若x>=e[mid]，则mid之前的元素包括mid一定都不用后移，故low=mid-1
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
	//增量序列必须由大到小，且最小值必须为1
	int dlta[3] = { 5,3,1 };
	//k枚举增量
	for (int k = 0; k < 3; k++) {
		int dk = dlta[k];
		//插入排序都是从序列第二个元素开始，所以i从l+dk开始
		for (int i = l + dk; i <= r; i++) {
			int x = e[i];
			int j = i - dk;
			//向对应序列插入
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
//根节点是左右子树中最小的元素，锦标赛思想，每次选择一个元素后，将对应的叶节点修改为MAX_VALUE,之后向上依次调整父节点
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

//堆排序
void Adjust_Heap(int *heap, int rt, int n)
{
	//将以rt为根的子堆进行下虑调整，堆的边界为n
	int x = heap[rt];
	int p;
	for (p = rt << 1; p <= n; p <<= 1) {
		if (p + 1 <= n&&heap[p + 1] > heap[p]) p++;
		if (heap[p] <= x) break;
		heap[rt] = heap[p];
		//这里出现过错误，切记保存当前处理的节点，p使探测的子节点
		rt = p;
	}
	//rt表示之前到达的节点，p表示探测的子节点，不一定在范围内
	heap[rt] = x;
}

void Heap_Sort()
{
	//构造大顶堆，每次将堆顶元素和堆数组最右元素交换，下虑调整，最后即可构造非递减序列
	for (int i = n >> 1; i >= 1; i--)
		Adjust_Heap(e, i, n);

	for (int i = n; i >= 1; i--) {
		swap(e[1], e[i]);
		Adjust_Heap(e, 1, i-1);
	}
}

//归并排序，需要辅助数组
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
	//初始化链表
	for (int i = l; i <= r; i++) {
		PRSElem t = (PRSElem)malloc(sizeof(RSElem));
		t->e = e[i];
		t->next = cur->next;
		cur->next = t;
		cur = t;
	}

	PRSElem front[10], last[10];

	//3为关键字数量，这里测试数位最大为3位数
	for (int i = 0; i < 3; i++) {
		cur = head.next;
		int a=1;
		for (int j = 0; j < i; j++) a *= 10;
		for (int i = 0; i < 10; i++) front[i] = last[i] = NULL;

		//分配，相当于令元素进入相应队列
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

		//收集，本质为按关键字次序依次出队，鉴于队列本身的性质，直接修改队头和队尾指针进行连接即可
		head.next = NULL;
		cur = &head;
		for (int j = 0; j < 10; j++) if (front[j]) {
			cur->next = front[j];
			cur = last[j];
			cur->next = NULL;
		}
	}

	//打印输出结果，返还空间
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