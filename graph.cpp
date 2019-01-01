#include<iostream>
#include<queue>

#define N 5
#define MAXINT 1000

using namespace std;

int A[N][N];

struct EdgeNode {
	int dest;
	int cost;
	EdgeNode*link;
};

struct VertexNode {
	int data;
	EdgeNode*adj;
}NodeTable[N];

int getweight(int v1, int v2) {
	if (v1 != -1 && v2 != -1) return A[v1][v2];
	else return 0;
}
int GetWight(int v1, int v2) {
	if (v1 != -1 && v2 != -1) {
		EdgeNode*p = NodeTable[v1].adj;
		while (p) {
			if (p->dest == v2) return p->cost;
			else p = p->link;
		}
	}
}
int getfirstneighbor(int v) {
	if (v != -1) {
		for (int col = 0; col < N; col++)
			if (A[v][col] > 0 && A[v][col] < MAXINT)
				return col;
	}
	return-1;
}
int GetFirstNeighbor(int v) {
	if (v != -1) {
		EdgeNode*p = NodeTable[v].adj;
		if (p != NULL) return p->dest;
	}
	return -1;
}
int getnextneighbor(int v1, int v2) {
	if (v1 != -1 && v2 != -1) {
		for (int col = v2 + 1; col < N; col++)
			if (A[v1][col] > 0 && A[v1][col] < MAXINT)
				return col;
	}
	return -1;
}
int GetNeighbor(int v1, int v2) {
	if (v1 != -1) {
		EdgeNode*p = NodeTable[v1].adj;
		while (p) {
			if (p->dest == v2 && p->link != NULL)
				return p->link->dest;
			else p = p->link;
		}
	}
	return -1;
}
void dfs(int v, int visited[]) {
	cout << v;
	visited[v] = 1;
	int w = GetFirstNeighbor(v);
	while (w != -1) {
		if (!visited[w]) dfs(w, visited);
		w = GetNeighbor(v, w);
	}
}
void dfs_(int v, int visited[]) {
	visited[v] = 1;
	for (int i = 0; i < N; i++) {
		if (A[v][i] == 1 && !visited[i])
			dfs_(v, visited);
	}
}
void DFS() {
	int*visited = new int[N];
	for (int i = 0; i < N; i++) visited[i] = 0;
	dfs(0, visited);
	delete[]visited;
}
void bfs(int v) {
	int*visited = new int[N];
	for (int i = 0; i < N; i++) visited[i] = 0;
	cout << v; visited[v] = 1;
	queue<int>q;
	q.push(v);
	while (!q.empty()) {
		v = q.front(); q.pop();
		int w = GetFirstNeighbor(v);
		while (w != -1) {
			cout << w << " ";
			visited[w] = 1;
			q.push(w);
		}
		w = GetNeighbor(v, w);
	}
	delete[]visited;
}
void bfs_(int v) {
	int*visited = new int[N];
	for (int i = 0; i < N; i++) visited[i] = 0;
	queue<int>q;
	while (!q.empty()) {
		int k = q.front();
		q.pop(); visited[k] = 1;
		for (int i = 0; i < N; i++) {
			if (!visited[i] && A[k][i] == 1)
				q.push(i);
		}
	}
}
void Prime(int cost[N][N], int u){
	int Min;
	int*lowcost = new int[N];
	int*nearvex = new int[N];
	int i, j, k;
	for(i = 0; i < N; i ++){
		lowcost[i] = cost[u][i];
		nearvex[i] = u;
	}
	for(i = 0; i < N - 1; i ++){
		Min = 1000;
		for(j = 0; j < N; j ++)
			if(lowcost[j] != 0 && lowcost[j] < Min){
				Min = lowcost[j]; k = j;
			}
		cout << nearvex[k] << " " << k << " " << Min << endl;
		lowcost[k] = 0;
		for(j = 0; j < N; j ++){
			if(cost[k][j] != 0 && cost[k][j] < lowcost[j]){
				lowcost[j] = cost[k][j];
				nearvex[j] = k;
			}
		}
	}	
}
void dijstra(int A[N][N]){
	int *s = new int[N];
	int path[N], dist[N];
	int i, j, k; int w;
	for(i = 0; i < N; i ++){
		dist[i] = A[0][i];
		s[i] = 0;
		if(i != 0 && dist[i] < MAXINT) path[i] = 0;
		else path[i] = -1;
	}
	s[0] = 1; dist[0] = 0;
	for(i = 0; i < N - 1; i ++){
		int min = MAXINT; int u = 0;
		for(j = 0; j < N; j ++)
			if(!s[j] && dist[j] < min){
				u = j; min = dist[j];
			}
		s[u] = 1;
		for(k = 0; k < N; k ++){
			w = A[u][k];
			if(!s[k] && w < MAXINT && dist[u] + w < dist[k]){
				dist[k] = dist[u] + w;
				path[k] = u;
			}
		}
	}
	for(int i = 1; i < N; i ++)
		cout << dist[i] << " ";
	cout << endl;
	for(int i = 1; i < N; i ++)
		cout << path[i] << " ";
}
void floyd(int cost[N][N]){
	int i, j, k;
	int A[i][j], path[i][j];
	for(i = 0;i < N; i ++)
		for(j = 0; j < N; j ++){
			A[i][j] = cost[i][j];
			if(i != j && A[i][j] < MAXINT) path[i][j] = i;
			else path[i][j] = 0;
		}
	for(k = 0; k < N; k ++)
		for(i = 0; i < N; i ++)
			for(j = 0; j < N; j ++)
				if(A[i][k] + A[k][j] < A[i][j]){
					A[i][j] = A[i][k] + A[k][j];
					path[i][j] = k;
				}
}
int main(){
	int A[N][N];
	for(int i = 0; i < N; i ++)
		for(int j = 0; j < N; j ++)
			cin >> A[i][j];
	dijstra(A);
	return 0;
}

