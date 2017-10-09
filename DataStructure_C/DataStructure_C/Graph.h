#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_VERTEX_NUM 100
#define MAX_EDGE_NUM 10000
#define MAX_VALUE 0x7fffffff

int vis[MAX_VERTEX_NUM];

typedef struct ArcNode {
	int v, w;
	struct ArcNode *next;
}ArcNode;

typedef struct HeadNode {
	int u, w;
	ArcNode *arc;
}HeadNode;

typedef struct Graph {
	int nv;//�ڵ���
	int ne;//����
	HeadNode *g;
}Graph;

typedef struct Triple {
	int u, v, w;
}Triple;

int addedge(Graph g, int u, int v, int w);

int CreateGraph(int n, int m, Graph& g);

//����
void dfs(Graph g, int u);

void DFSTraverse(Graph g);

void bfs(Graph g, int u);

void BFSTraverse(Graph g);

//��С������
void Prim(Graph g);

int getf(int *f, int x);

void sortedges(Triple *e, int l, int r);

void Kruskal(int n, int m);

//��������
void TopoSort(int n, int m);

//�ؼ�·��
int CriticalPath_TopoSort(Graph g, int *ve, int *st);

void CriticalPath(Graph g);

//Dijkstra
void Dijkstra(Graph g, int ss);

//Floyd
void getPath(int p[][MAX_VERTEX_NUM], int s, int e);

void PrintPath(int p[][MAX_VERTEX_NUM], int s, int e);

void Floyd(int n, int m);