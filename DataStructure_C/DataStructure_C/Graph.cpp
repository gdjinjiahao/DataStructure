#include "Graph.h"

//图节点均从1号开始编号
/*
6 10
6 5 1
5 4 5
4 3 5
2 3 4
1 2 5
6 1 3
3 1 8
3 6 9
1 4 7
4 6 6
DAG:
9 11
1 2 6
1 3 4
1 4 5
2 5 1
3 5 1
4 6 2
5 7 9
5 8 7
6 8 4
7 9 2
8 9 4
*/


int addedge(Graph g, int u, int v, int w)
{
	ArcNode* t = (ArcNode *)malloc(sizeof(ArcNode));
	if (t == NULL) return 0;
	t->v = v;
	t->w = w;
	t->next = g.g[u].arc;
	g.g[u].arc = t;
	return 1;
}

int CreateGraph(int n, int m, Graph& g)
{
	g.nv = n;
	g.ne = m;
	g.g = (HeadNode *)malloc((n + 1) * sizeof(HeadNode));
	if (g.g == NULL) return 0;
	for (int i = 1; i <= n; i++) {
		/*int w;
		scanf("%d", &w);
		g.g[i].w = w;*/
		g.g[i].arc = NULL;
		g.g[i].u = i;
	}
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if (!addedge(g, u, v, w)) return 0;
		//if (!addedge(g, v, u, w)) return 0;
	}
	return 1;
}

//遍历
void dfs(Graph g, int u) 
{
	vis[u] = 1;
	printf("%d ", u);
	for (ArcNode *ite = g.g[u].arc; ite != NULL; ite = ite->next) {
		int v = ite->v;
		if (!vis[v]) dfs(g, v);
	}
}

void DFSTraverse(Graph g)
{
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= g.nv; i++) if (!vis[i])
		dfs(g, i);
}

void bfs(Graph g, int u)
{
	queue<int> q;
	q.push(u);
	vis[u] = 1;
	printf("%d ", u);
	while (!q.empty()) {
		int t = q.front();
		q.pop();
		for (ArcNode *ite = g.g[t].arc; ite != NULL; ite = ite->next) {
			int v = ite->v;
			if (!vis[v]) {
				q.push(v);
				vis[v] = 1;
				printf("%d ", v);
			}
		}
	}
}

void BFSTraverse(Graph g)
{
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= g.nv; i++) if (!vis[i])
		bfs(g, i);
}

//最小生成树
void Prim(Graph g)
{
	memset(vis, 0, sizeof(vis));
	int dis[MAX_VERTEX_NUM];
	int from[MAX_VERTEX_NUM];
	for (int i = 1; i <= g.nv; i++) dis[i] = MAX_VALUE;
	dis[1] = 0;

	for (int i = 0; i < g.nv; i++) {
		int p, td = MAX_VALUE;
		for (int j = 1; j <= g.nv; j++) if (!vis[j] && dis[j] < td) {
			p = j; td = dis[j];
		}
		vis[p] = 1;
		if (i > 0) 
			printf("%d %d %d\n", from[p], p, dis[p]);
		for (ArcNode *ite = g.g[p].arc; ite != NULL; ite = ite->next) {
			int v = ite->v, w = ite->w;
			if (vis[v]) continue;
			if (dis[v] > w) {
				dis[v] = w;
				from[v] = p;
			}
		}
	}
}

int getf(int *f, int x)
{
	if (f[x] == x) return x;
	return f[x] = getf(f, f[x]);
}

void sortedges(Triple *e, int l, int r)
{
	if (l >= r) return;
	int tl = l, tr = r;
	Triple x = e[l];
	while (l < r) {
		while (r > l&&e[r].w >= x.w) r--;
		e[l] = e[r];
		while (l < r&&e[l].w <= x.w) l++;
		e[r] = e[l];
	}
	e[l] = x;
	sortedges(e, tl, l - 1);
	sortedges(e, l+1, tr);
}

void Kruskal(int n,int m)
{
	//Kruscal算法如果有Graph直接计算生成树比较麻烦，故单独实现
	if (n > MAX_VERTEX_NUM) return;
	if (m > MAX_EDGE_NUM) return;
	int f[MAX_VERTEX_NUM];
	for (int i = 1; i <= n; i++) f[i] = i;
	Triple edges[MAX_EDGE_NUM];
	for (int i = 0; i < m; i++) 
		scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
	sortedges(edges, 0, m - 1);

	printf("\n\n");
	for (int i = 0; i < m; i++) {
		int u = edges[i].u, v = edges[i].v, w = edges[i].w;
		int fu = getf(f, u), fv = getf(f, v);
		if (fu == fv) continue;
		f[fu] = fv;
		printf("%d %d %d\n", u, v, w);
	}
}

//拓扑排序
void TopoSort(int n, int m)
{
	if (n > MAX_VERTEX_NUM) return;
	if (m > MAX_EDGE_NUM) return;

	Graph g;
	g.nv = n;
	g.ne = m;
	g.g = (HeadNode *)malloc((n + 1) * sizeof(HeadNode));
	for (int i = 1; i <= n; i++) g.g[i].arc = NULL;
	if (g.g == NULL) return ;

	int in[MAX_VERTEX_NUM];
	int set[MAX_VERTEX_NUM], size = 0;
	memset(in, 0, sizeof(in));
	for (int i = 0; i < m; i++) {
		//w是没必要的，但为了使输入数据和求关键路径兼容，加上无所谓
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		in[v]++;
		addedge(g, u, v, w);
	}

	for (int i = 1; i <= n; i++) if (!in[i])
		set[size++] = i;

	printf("\n\n");
	while (size>0)
	{
		int u = set[size - 1];
		size--;
		printf("%d ", u);
		for (ArcNode *ite = g.g[u].arc; ite != NULL; ite = ite->next) {
			int v = ite->v;
			in[v]--;
			if (in[v] == 0) set[size++] = v;
		}
	}
}

//关键路径
int CriticalPath_TopoSort(Graph g, int *ve, int *st)
{
	int in[MAX_VERTEX_NUM];
	int q[MAX_VERTEX_NUM], size=0;
	memset(in, 0, sizeof(in));
	for (int i = 1; i <= g.nv; i++)
		for (ArcNode *ite = g.g[i].arc; ite != NULL; ite = ite->next)
			in[ite->v]++;
	for (int i = 1; i <= g.nv; i++) ve[i] = 0;
	for (int i = 1; i <= g.nv; i++) if (in[i] == 0)
		q[size++] = i;

	for (int k = 0; k < g.nv; k++) {
		if (size == 0) return 0;
		int u = q[--size];
		st[k] = u;
		for (ArcNode *ite = g.g[u].arc; ite != NULL; ite = ite->next) {
			int v = ite->v, w = ite->w;
			if (ve[v] < ve[u] + w) ve[v] = ve[u] + w;
			in[v]--;
			if (in[v] == 0) q[size++] = v;
		}
	}
}

void CriticalPath(Graph g)
{
	/*
	6 8
	1 2 3
	1 3 2
	2 4 2
	3 4 4
	2 5 3
	4 6 2
	3 6 3
	5 6 1
	*/
	int ve[MAX_VERTEX_NUM], vl[MAX_VERTEX_NUM];
	int st[MAX_VERTEX_NUM];
	CriticalPath_TopoSort(g, ve, st);

	for (int i = 1; i <= g.nv; i++) vl[i] = ve[st[g.nv - 1]];
	
	for (int i = g.nv - 1; i >= 0; i--) {
		int u = st[i];
		for (ArcNode *ite = g.g[u].arc; ite != NULL; ite = ite->next) {
			int v = ite->v, w = ite->w;
			if (vl[u] > vl[v] - w) vl[u] = vl[v] - w;
		}
	}

	for (int i = 0; i < g.nv; i++) {
		int u = st[i];
		for (ArcNode *ite = g.g[u].arc; ite != NULL; ite = ite->next) {
			//u节点最早开始时间ve[u],边权w,后继v节点的最晚开始时间vl[v]
			//即节点v最晚vl[v]时刻就必须要开始了，而其前驱u最早ve[u]才能开始，并且u经过活动消耗w后到达v时，v已经到达最晚开始时刻，必须马上开始，这证明该边是关键活动
			//关键路径可能不止一条，若采用记录最大前驱的方法则只能得到一条关键路径，单单该边该条关键路径上活动的权值不一定会减小最终权值
			int v = ite->v, w = ite->w;
			if (ve[u] + w == vl[v]) printf("%d --> %d %d\n", u, v, w);
		}
	}
}

//Dijkstra
void Dijkstra(Graph g, int ss)
{
	/*
	6 8
	1 6 100
	5 6 60
	5 4 20
	3 4 50
	2 3 5
	1 3 10
	1 5 30
	4 6 10
	*/
	int dis[MAX_VERTEX_NUM];
	//int vis[MAX_VERTEX_NUM];
	int pre[MAX_VERTEX_NUM];
	memset(dis, -1, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	memset(pre, -1, sizeof(pre));
	dis[ss] = 0;
	for (int i = 0; i < g.nv; i++) {
		int u = -1, tdis = -1;
		for (int j = 1; j <= g.nv; j++) if (!vis[j] && dis[j] != -1) {
			if (tdis == -1|| tdis > dis[j]) {
				tdis = dis[j];
				u = j;
			}
		}
		//因为图不一定连通，故并非一定能得到nv个点的最短距离
		if (u == -1) break;
		vis[u] = 1;
		for (ArcNode *ite = g.g[u].arc; ite != NULL; ite=ite->next) {
			int v = ite->v, w = ite->w;
			if (dis[v] == -1 || dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				pre[v] = u;
			}
		}
	}

	for (int i = 1; i <= g.nv; i++) {
		printf("%d  %d  :  ", i, dis[i]);
		if (dis[i] == -1) {
			printf("NONE\n");
			continue;
		}
		int p = i;
		while (p != -1) {
			printf("%d", p);
			if (p != ss) printf(" <-- ");
			p = pre[p];
		}
		printf("\n");
	}
}

//Floyd
void getPath(int p[][MAX_VERTEX_NUM], int s, int e)
{
	if (p[s][e] == 0) {
		printf(" -> %d", e);
		return;
	}
	getPath(p, s, p[s][e]);
	getPath(p, p[s][e], e);
}

void PrintPath(int p[][MAX_VERTEX_NUM], int s, int e)
{
	if (p[s][e] == -1) {
		printf("NONE\n");
		return;
	}
	printf("%d", s);
	getPath(p, s, e);
	printf("\n");
}

void Floyd(int n, int m)
{
	if (n > MAX_VERTEX_NUM) return;
	if (m > MAX_EDGE_NUM) return;
	
	int f[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int p[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	memset(f, -1, sizeof(f));
	memset(p, -1, sizeof(p));

	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		f[u][v] = w;
		p[u][v] = 0;
	}

	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for (int j = 1; j <= n; j++) if (f[i][k] != -1 && f[k][j] != -1) {
				if (f[i][j] == -1 || f[i][j] > f[i][k] + f[k][j]) {
					f[i][j] = f[i][k] + f[k][j];
					p[i][j] = k;
				}
			}

	for(int i=1;i<=n;i++)
		for (int j = 1; j <= n; j++) if(i != j){
			printf("%d --> %d  %d\n", i, j, f[i][j]);
			PrintPath(p, i, j);
			printf("\n");
		}
}

/*int main()
{
	//通用操作，输入顶点数和边数
	int n, m;
	scanf("%d%d", &n, &m);

	Graph g;
	if (!CreateGraph(n, m, g)) return 0;
	printf("\n");

	DFSTraverse(g);
	printf("\n\n");

	BFSTraverse(g);
	printf("\n\n");

	Prim(g);
	printf("\n\n");

	CriticalPath(g);
	printf("\n");

	Dijkstra(g, 1);
	printf("\n");



	//Kruakal算法输入独立于上述操作
	//Kruskal(n, m);

	//TopoSort(n, m);

	//Floyd(n, m);

	return 0;
}*/