#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;

typedef struct HuffNode {
	int Parent, lChild, rChild;
	double w;
}HNode,*PHNode;

void Select(PHNode& HTree, int l, int r, int& a, int& b)
{
	a = b = -1;
	for (int i = l; i < r; i++) if (HTree[i].Parent == -1) {
		if (a == -1) { a = i; continue; }
		if (HTree[i].w < HTree[a].w) a = i;
	}
	
	for (int i = l; i < r; i++) if (HTree[i].Parent == -1 && i != a) {
		if (b == -1) { b = i; continue; }
		if (HTree[i].w < HTree[b].w) b = i;
	}
}

//构造Huffman树
int HuffmanTree(int n, double *w, PHNode& HTree)
{
	int m = 2 * n - 1;
	HTree = (PHNode)malloc(m * sizeof(HNode));
	if (HTree == NULL) return 0;
	for (int i = 0; i < n; i++) {
		HTree[i].w = w[i];
		HTree[i].Parent = HTree[i].lChild = HTree[i].rChild = -1;
	}
	for (int i = n; i < m; i++) {
		int a, b;
		Select(HTree, 0, i, a, b);
		HTree[a].Parent = HTree[b].Parent = i;
		HTree[i].lChild = a; HTree[i].rChild = b;
		HTree[i].w = HTree[a].w + HTree[b].w;
		HTree[i].Parent = -1;
	}
	return 1;
}

//从叶节点向上求Huffman编码
int HuffmanCoding1(int n, PHNode HTree, char**& code)
{
	code = (char **)malloc(n * sizeof(char*));
	if (code == NULL) return 0;
	char *t;
	t = (char*)malloc(n * sizeof(char));
	if (t == NULL) return 0;
	for (int i = 0; i < n; i++) {
		int p = i, f = HTree[i].Parent;
		int k = 0;
		while (f != -1) {
			if (HTree[f].lChild == p) t[k++] = '0';
			else t[k++] = '1';
			p = f;
			f = HTree[f].Parent;
		}
		code[i] = (char *)malloc((k + 1) * sizeof(char));
		if (code[i] == NULL) return 0;
		code[i][k] = 0;
		for (int j = 0; j < k; j++) code[i][j] = t[k - j - 1];
	}
	return 1;
}

//从根节点向下求Huffman编码
int HuffmanCoding2(int n, PHNode HTree, char**& code)
{
	int m = 2 * n - 1;
	int rt = m - 1;
	//树结构已经构造，故权值信息已经无用，可用来记录访问次数
	for (int i = 0; i < m; i++) HTree[i].w = 0;

	code = (char **)malloc(n * sizeof(char*));
	if (code == NULL) return 0;
	char *t;
	t = (char*)malloc(n * sizeof(char));
	if (t == NULL) return 0;

	int p = rt, k = 0;
	while (HTree[rt].w <= 2) {
		if (p < n) {
			code[p] = (char *)malloc((k + 1) * sizeof(char));
			if (code[p] == NULL) return 0;
			code[p][k] = 0;
			//此处无需反转字符串
			for (int j = 0; j < k; j++) code[p][j] = t[j];
			p = HTree[p].Parent;
			k--;
			continue;
		}
		if (HTree[p].w == 0) {
			t[k++] = '0';
			HTree[p].w = 1;
			p = HTree[p].lChild;
		}
		else if (HTree[p].w == 1) {
			t[k++] = '1';
			HTree[p].w = 2;
			p = HTree[p].rChild;
		}
		else {
			HTree[p].w = 3;
			p = HTree[p].Parent;
			k--;
		}
	}
}

/*int main()
{
	double *w;
	int n;
	scanf("%d", &n);
	w = (double *)malloc(n * sizeof(double));
	if (w == NULL) return 0;
	for (int i = 0; i < n; i++) scanf("%lf", w+i);

	PHNode pht;
	if (!HuffmanTree(n, w, pht)) return 0;
	char **code;
	//HuffmanCoding1(n, pht, code);
	HuffmanCoding2(n, pht, code);

	for (int i = 0; i < n; i++) {
		printf("%.2lf  %s\n", w[i], code[i]);
	}
	return 0;
}*/