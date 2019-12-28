##Graph及相关算法
>无向图的邻接矩阵是对称的，有向图的邻接矩阵可能不对称

##一、图的遍历(Graph Traversal)
为避免重复访问，可设置一个标志顶点是否被访问过的辅助数组Visited[]，初始状态为0，顶点i被访问时就令Visited[i]为1
###深度优先搜索（DFS）

![](https://i.imgur.com/80IBH5Q.jpg)


	//很棒的dfs,bfs例子
	#include<iostream>
	#include<vector>
	#include<fstream>
	#include<queue>
	#define max 1000
	using namespace std;
	
	//DFS解法
	void DFS(vector<vector<int>>m, int k, bool visited[]) {
		visited[k] = true;
		for (int i = 0; i < m.size(); i++) {
			if (m[k][i] == 1 && !visited[i]) {//找邻接的朋友，存在的话找朋友的朋友
				DFS(m, i, visited);
			}
		}
	}
	//BFS解法 
	void BFS(vector<vector<int>>m, queue<int> queue, bool visited[]) {
		while (!queue.empty()) {
			int k = queue.front();
			queue.pop();
			visited[k] = true;
			for (int i = 0; i < m.size(); i++) {
				if (!visited[i] && m[k][i] == 1) {
					queue.push(i);
				}
			}
		}
	}
	
	int findCircleNum(vector<vector<int>>m) {
		int res = 0;
		bool visited[max] = { false };
		queue<int> queue;
		for (int i = 0; i < m.size(); i++) {//遍历所有朋友
			if (!visited[i]) {
				//DFS(m, i, visited);
				queue.push(i);
				BFS(m,queue,visited);
				res++;
			}
		}
		return res;
	}
	int main() {
		int n, num; cin >> n;
		vector<vector<int>> a(n, vector<int>(n, 0));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				cin >> num; a[i][j] = num;
			}
		cout << findCircleNum(a);
		system("pause");
		return 0;
	}
#
	void DFS(){
		int *Visited = new int[VerticesNumber()];
		//创建辅助数组
		for(int i = 0; i < VerticesNumber(); i ++)
			Visited[i] = 0;//辅助数组初始化
		DFS(0, Visted);//从顶点0开始进行深度优先搜索
		delete[]Visited;
	}

	void DFS(int v, int Visited[]){
		//从顶点v出发
		//按深度优先搜索次序访问所有尚未访问过的顶点
		//辅助数组Visited用于对已访问过的顶点作以访问标记
		cout<<v;输出访问顶点信息
		Visited[v] = 1;
		int w = GetFirstNeighbor(v);
		while(w != -1){
			//若邻接顶点存在
			if(!Visited[w])//若该邻接顶点未被访问过
				DFS(w,Visited);//从邻接顶点w开始进行递归访问
			w = GetNextNeighbor(v,w);//寻找v的下一个邻接顶点
		}
	}
###广度优先搜索(BFS)

![](https://i.imgur.com/MPDQfz4.jpg)
>为了实现逐层访问, 算法中使用了一个队
列，以记忆正在访问的这一层和上一层
的顶点，以便于向下一层访问。

	(1) 把队列置空。
	(2) 打印出发顶点，置该顶点已被访问的标志。
	(3) 让出发顶点进队。
	(4) 若队列不空，则
	(a) 取出队首中的顶点v。
	(b) 在邻接表中，依次取得与顶点v邻接的各个
	顶点。
	   (i) 若当前取得的邻接顶点未被访问，则
		 ① 输出该顶点，置该顶点已被访问的标志。
	     ② 该顶点进队。
	   (ii) 取得下一个邻接顶点。
	(c) 转(4)。
	(5) 若队列空，则处理过程结束。

#
	void BFS(int v){
		//从顶点v出发，按广度优先次序进行搜索
		//其中使用队列作为辅助存储结构
		int*Visited = new int[VerticesNumber()];//创建辅助数组
		for(int i = 0; i < VerticesNumber(); i ++）
			Visited[i] = 0;//辅助数组初始化
		cout<<v;输出访问顶点信息
		Visited[v] = 1;
		Queue<int>q; q.EnQueue(v);//顶点v进队
		while(!q.IsEmpty()){
			v = q.Dequeue();//从队列中退出顶点v
			int w = GetFirstNeighbor(v);//寻找v的第一个邻接顶点w
			while(w != -1){
				if(!Visited[w]){
					//w未被访问过
					cout<<w<<' ';
					Visited[w] = 1;
					q.EnQueue(w);
				}
				w = GetNextNeighbor(v,w);
			}
		delete[]Visited;
	}
##二、最小生成树
>####构造最小生成树的准则
>- 必须使用且仅使用该网络中的n-1条边来联结网络中的n个顶点；
- 不能使用产生回路的边；
-  各边上的权值总和达到最小。

###1、Prime算法
![](https://i.imgur.com/s36rUeZ.jpg)
![](https://i.imgur.com/9m7FeRk.jpg)
>在构造过程中，设置了两个辅助数组

>- lowcost[] 存放生成树顶点集合内顶点到生成树外各顶点的各边上的当前最小权值
>- nearvex[] 记录生成树顶点集合外各顶点距离集合内哪个顶点最近(即权值最小)。

例：

![](https://i.imgur.com/D4ZS0np.jpg)

- 若选择从顶点0出发，即u0=0，则两个辅助
数组的初始状态为：

lowcost|  0 |28| ∞| ∞| ∞| 10| ∞
----|---|---|--|--|--|--|--|
nearvex| -1|  0| 0| 0| 0 | 0| 0
v|0|1|2|3|4|5|6|

选v=5

lowcost|  0 |28| ∞| ∞| 25| 10| ∞
----|---|---|--|--|--|--|--|
nearvex| -1|  0| 0| 0| 5| -1| 0
v|0|1|2|3|4|5|6|

选v=4

lowcost|  0 |28| ∞| 22|25| 10| 24
----|---|---|--|--|--|--|--|
nearvex| -1|  0| 0| 4| -1 | -1| 4
v|0|1|2|3|4|5|6|
....
###利用普里姆算法建立最小生成树
	void Prim(Graph<string>&G,MinSpanTree&T){
		int i,j,n=G.NumberOfVertices( ); //顶点数float *lowcost=new float[n];
		int *nearvex=new int[n];
		for (i=1;i<n;i++) {
			lowcost[i]=G.GetWeight(0,i);
			nearvex[i]=0;
		}  //顶点0到各边代价及最短带权路径
		nearvex[0]=-1; //加到生成树顶点集合MSTEdgeNode e; //最小生成树结点单元
		for (i=1;i<n;i++) {
		//循环n-1次，加入n-1条边
			float min=MaxValue; int v=0; 
			for (j=0;j<n;j++)
				if (nearvex[j]!=-1 && lowcost[j]<min)
					{v=j; min=lowcost[j]; }
				//求生成树外顶点到生成树内顶点
				 //具有最小权值的边
			if (v){ //v=0表示再也找不到要求顶点
				e.tail=nearvex[v];   e.head=v;
				e.cost=lowcost[v];
				T.Insert(e); //选出的边加入生成树nearvex[v]=-1; //该边加入生成树标记for (j=1;j<n;j++)
					if (nearvex[j]!=-1 &&G.GetWeight(v,j)<lowcost[j]) { 
						lowcost[j]=G.GetWeight(v,j); nearvex[j]=v;   
					}
				}
		} //循环n-1次，加入n-1条边
	}

#
	#include<iostream>
	#include<vector>
	
	#define n 7
	#define MAXINT 100
	using namespace std;
	
	void Prim(int Cost[n][n], int u){
		int Min;
		int *LowCost = new int[n];
		int *CloseSet = new int[n];
		int i, j, k;
		for(i = 0; i< n; i ++){
			LowCost[i] = Cost[u][i];
			CloseSet[i] = u;
		}
		for(i = 0; i < n - 1; i ++){
			Min = MAXINT;
			for(j = 0; j < n; j ++)
				if(LowCost[j] != 0 && LowCost[j] < Min){
					Min = LowCost[j];
					k = j;
				} 
			cout << CloseSet[k] << " " << k << " " << Min << endl;
			LowCost[k] = 0;
			for(j = 0; j < n; j ++)
				if(Cost[k][j] != 0 && Cost[k][j] < LowCost[j]){
					LowCost[j] = Cost[k][j];
					CloseSet[j] = k;
				} 
		}
	}
	int main(){
		int a[n][n];
		for(int i = 0; i < n; i ++)
			for(int j = 0; j < n; j ++)
				cin >> a[i][j];
		Prim(a, 0);
		return 0;
	}

###2、Kruskal算法
![](https://i.imgur.com/V0ShCnM.jpg)
##由于算法涉及到并查集的知识，仅作了解


##三、最短路径
>最短路径问题：如果从图中某一顶点（称为源点）到达另一顶点（称为终点）的路径可能不止一条，如何找到一条路径使得沿此路径上各边上的权值总和达到最小。
#
>###问题解法
>- 边上权值非负情形的单源最短路径问题——Dijkstra算法
>- 边上权值为任意值的单源最短路径问题——Bellman和Ford算法
>- 所有顶点间的最短路径——Floyd算法

###1、Dijkstra算法
![](https://i.imgur.com/v97BGMk.jpg)
>###基本思想是：把图中顶点集合V分为两组，令S表示已求出最短路径的顶点集合为一组，其余尚未确定最短路径的顶点集合为第二组

>- 按最短路径长度的递增顺序逐个地把第二组的顶点加入S中，直至从v出发可以到达的所有顶点都在S中
>- 在这过程中，总保持从v到S中各顶点的最短路径长度都不大于v到第二组的任何顶点的最短路径长度。
>- 另外，每个顶点对应一个距离，S中的顶点的距离就是从v到此顶点的最短路径长度，第二组顶点的距离是从v到此顶点的只包括S中的顶点为中间顶点的当前最短路径长度。
#
>###具体做法
>- 初始时，S={v}，即S中只包含源点v，v的距离为零
>- 第二组包含其他的顶点，而这一组的顶点的距离为：若图中有边<v,w>，则w的距离就是这条边上的权；否则w的距离为一个很大的数（即算法中的9999表示）。
>- 然后，每次从第二组的顶点中选取一个距离最小的顶点k，把k加入S中，每次加入一个顶点到S中后，就要对第二组的各个顶点的距离进行一次修改。
>- 若加进顶点k做中间顶点，从v到顶点j（j∈V-S）的距离比原来不经过顶点k的距离短，则要修改顶点j的距离值。修改后，再选距离最小的顶点加入S中，并对V-S中的顶点的距离进行修改。
>- 这样的过程连续进行下去，直到G中所有顶点都包含在S中，或再也没有可加入S的顶点存在
#
>###具体实现
>- 使用一个存放各顶点的当前距离的数组Dist，一旦从源点v到顶点k的最短路径已求出，则Dist[k]就是从源点到顶点k的最短路径长度。
>- 使用数组Pre，数组元素Pre[j]存放从源点v到顶点j的最短路径中j前面的顶点。有了Pre数组，就能很容易的求得从源点v到其他各个顶点的路径。下面给出的算法只求出从源点v到图中各个顶点的最短路径长度，同时求得Pre数组各元素的值，但没有求得从v到各个顶点的最短路径。
>- 用9999表示邻接矩阵的无穷值。


![](https://i.imgur.com/Y3okki4.jpg)
>###Dijkstra算法可描述如下
>1. 初始化：S←{v0}; dist[j]←Edge[0][j],  j=1, 2, …, n-1;//n为图中顶点个数
>2. 求出最短路径长度：dist[k]←min{dist[i]},  i∈V- S; S←SU{k};
>3. 修改：dist[i]←min{dist[i], dist[k]+Edge[k][i]},对于每一个i∈V-S;
>4. 判断：若S=V，则算法结束，否则转2 

	void ShortestPath(Graph <float> &G,intv,float dist[ ], int path[ ]) { 
	//Graph是一个带权有向图
	//各边上的权值由Edge[i][j]
	//给出本算法建立一个数组dist[j], 0≤j<n
	//是当前求到的从顶点v到顶点j的最短路径长度 
	//同时用数组path[j], 0≤j<n，存放求到的最短路径
		int n = G.NumberOfVertices();
		int *S = new int[n];//最短路径顶点集
		int i, j, k; float w;
		for(int i = 0; i < n; i ++){
			dist[i] = G.GetWeight(v,i);//数组初始化
			S[i] = 0;
			if(i != v && dist[i] < MaxValue)
				path[i] = v;
			else path[i] = -1;
		}
		S[v] = 1; dist[v] = 0;//顶点v加入到顶点集合
		//选当前不在集合S中具有最短路径的顶点u 
		for (i=0;i<n-1;i++) {
			float min=MaxValue; int u=v;
			for (j=0;j<n;j++)
				if (!S[j]&&dist[j]<min) 
				{u=j; min=dist[j]; }
			S[u]=1;  //将顶点u加入集合S 
			for (k=0;k<n;k++) { //修改
				w=G.GetWeight(u,k);
				if (!S[k]&&w<MaxValue&& dist[u]+w<dist[k]) {
				//顶点k未加入S，且绕过u可以缩短路径
					dist[k]=dist[u]+w;
					path[k]=u;  //修改到k的最短路径
				}
			}
		}
	}
#
	void ShortestPath(int n, int v){
	//G是一个具有n个顶点的带权有向图
	//各边上的权值由Cost[i][j]给出
	//建立一个数组Dist[j], 0≤j<n
	//是当前求到的从顶点v到顶点j的最短路径长度 
	//建立数组path[j] , 0≤j<n，存放求到的最短路径
		int i, j, k; 
		float Min;
		for (i=1; i<=n; i++)
		{ //Dist、Pre和S数组初始化
			Dist[i]=Cost[v][i];  //邻接矩阵第v行复制到Dist中S[i]=0;
			if (Dist[i]<MAXINT)
				Pre[i]=v;
			else Pre[i]=0;
		}
		S[v] = 1;//顶点v加入S集合中
		Pre[v] = 0;
		for (i=1; i<=n; i++)
		{  //从顶点v确定n-1条路径
			Min=MAXINT;
			k=0;
			for (j=1; j<=n; j++)
			//选择当前不在集合S中具有最短路径的顶点u
				if (S[j]==0)
					if (Dist[j]!=0 && Dist[j]<Min){
						Min = Dist[j]; k = j;
					}
			if (k==0) continue;
			S[k]=1;
			//将顶点u加入S集合，表示它已在最短路径上
			for (j=1; j<=n; j++)
				if (S[j]==0 && Cost[k][j]<MAXINT)  //修改
					if (Dist[k]+Cost[k][j]<Dist[j]){
						Dist[j]=Dist[k]+Cost[k][j]; Pre[j]=k;
					}
		}
	}

###2、Floyd算法（所有顶点之间的最短路径）
>已知一个各边权值均大于0的带权有向图，对每一对顶点vi≠vj，要求求出vi与vj之间的最短路径和最短路径长度。
#
>###Floyd算法的基本思想
>定义一个n阶方阵序列：A(-1),A(0),...,A(n-1)

>其中，A(-1)[i][j] = Edge[i][j]; A(k)[i][j] = min{A(k-1)[i][k] + A(k-1)[k][j]},k = 0, 1,..., n-1
>
>A(0)[i][j]是从顶点vi到vj，中间顶点是v0的最短路径的长度;
>
>A(k)[i][j]是从顶点vi到vj，中间顶点的序号不大于k的最短路径的长度
>
>A(n-1)[i][j]是从顶点vi到vj的最短路径长度。
#
>###具体思想
>- 递推的产生一个矩阵序列A(0),A(1),A(2),…, A(k),…,A(n)，其中A(0)为给定的代价邻接矩阵，A(k)(i, j) (1≤i, j≤n)表示从顶点i到顶点j的中间顶点序号不大于k的最短路径的长度。
>- 若从i到j 的路径没有中间顶点，则对于1≤k≤n，有A(k)(i, j)=A(0)(i, j)=Cost(i, j)。
>- 递推地产生A(0),A(1),A(2),…,A(k),…,A(n)的过程就是逐步允许越来越多的顶点作为路径的中间顶点，直至找到所有允许作为中间顶点的顶点，算法结束而求出最短路径。
#
>###假设已求出A(k-1)(i,j)(1≤i,j≤n),怎么求出A(k-1)(i,j)
>
>- 如果从顶点i到j的最短路径不经过k,则由A(k)(i, j)的定义可知，从i到j的中间顶点序号不大于k的最短路径长度就是A(k-1)(i, j)，即A(k)(i, j)=A(k-1)(i, j)。
>- 如果从顶点i到顶点j的最短路径经过顶点k，则这样的一条路径是由i到k和由k到j的两条路径所组成。由于A(k-1)(i, k)+A(k-1)(k, j)<A(k-1)(i, j)，则A(k)(i, j)=A(k-1)(i, k)+A(k-1)(k, j)。 
![](https://i.imgur.com/4i42ozD.jpg)

	void Floyd(int n){
		//Cost[n][n]是一个具有n个顶点的图的邻接矩阵
		//A[i][j]是顶点i和j之间的最短路径长度
		//Path[i][j]是相应路径上顶点j前一顶点的顶点号
		int i, j, k;
		for (i=1; i<=n; i++)
			for (j=1; j<=n; j++)  //矩阵A与数组Path初始化
			{ A[i][j]=Cost[i][j];
			  if (i!=j && A[i][j]<MAXINT)  //i和j之间有路径
			  Path[i][j]=i;
			  else Path[i][j]=0;  //i和j之间没有路径
			}
		for(k=1; k≤n; k ++)
			for(i=1; i≤n; i++)
				for(j=1; j≤n; j++）//产生A(k)及相应的Path(k)
					if (A[i][k]+A[k][j]<A[i][j]){  //缩短路径长度，绕过k到j
						A[i][j]=A[i][k]+A[k][j]; Path[i][j]=k;
					}
	}			
![](https://i.imgur.com/CU1A2xF.jpg)
>Floyd算法允许图中有带负权值的边，但不许有包含带负权值的边组成的回路。

##四、拓扑排序
>进行拓扑排序的方法
>
>1. 输入AOV网络，令n为顶点个数。
>2. 在AOV网络中选一个没有直接前驱的顶点，并输出之；
>3. 从图中删去该顶点，同时删去所有它发出的有向边；
>4. 重复以上②、③步，直到
  - 全部顶点均已输出，拓扑有序序列形成，拓扑排序完成；
  - 或图中还有未输出的顶点，但已跳出处理循环。说明图中还剩下一些顶点，它们都有直接前驱，这时网络中必存在有向环。


####AOV网络及其邻接表表示

![](https://i.imgur.com/G05DON2.jpg)

	void Toppol_Order(){
		//对n各顶点的AOV网络进行拓扑排序
		//其中top是入度为零顶点栈的栈顶指针
		int top = -1;//建立空栈
		for(int i = 0; i < n; i ++)//建立入度为零顶点的链接栈
			if(count[i] == 0){
				//入度为零的顶点依次进栈
				count[i] = top; top = i;
			}
		for(int i = 0; i < n; i ++)
			if(top == -1){
			//存在有向环，未能形成拓扑序列，直接返回
				cout<<“Network has a cycle!”<<endl; return;
			}
		 else{
			int j = top;
			top = count[top];//入度为零的顶点出栈
			cout<<j<<endl;//输出入度为零的顶点信息
			EdgeNode<float>*l = NodeTable[j].adj;
			//顶点j的边链表的头指针
			while (l){  //l≠0，存在出边
				int k = l.dest;
				//取该边的终止顶点k，该顶点的入度减1 
				if (--count[k]==0){  //入度减1为零的顶点进栈
					count[k] = top;
					top = k;
				}
				l = l->link;//取顶点j的下一条边出栈
			}
		}
	}
##非常好的拓扑排序的例子
	#include<stdio.h>
	#include<stdlib.h>
	#define N 7//顶点个数
	 
	typedef struct 
	{
		char vexs[N];//顶点数组
		int arcs[N][N];//邻接矩阵
	}graph;
	 
	void TopoSort_matrix(graph g)
	{
		int row[N]={0};//按照列来设置标志，为1表示已经输出（不再考虑），为0表示未输出。
		int v=1;//标志符，1表示已经输出（不再考虑），为0表示未输出，赋给row数组
		int i,j,k,t,m;
		for(k=0;k<N;k++)
		{
			for(j=0;j<N;j++)
			{
				if(row[j]==0)//活动j还未输出
				{
					t=1;//标识符
					for(i=0;i<N;i++)
						if(g.arcs[i][j]==1)//当前活动有入度（活动i必须在活动j之前）
						{
							t=0;
							break;
						}
					if(t==1)//活动j没有入度
					{
						m=j;
						break;
					}
				}
			}
			if(j!=N)
			{
				row[m]=v;
				printf("%c",g.vexs[m]);
				for(i=0;i<N;i++)
					g.arcs[m][i]=0;//将已经输出的活动所到达的下个活动的入度置为0
				v++;
			}
			else 
				break;
			}
			if(v-1<N)//当row中不是所有的元素都被赋予新值v时，说明有环存在
				printf("\n该有向图有环存在！");
		
	}
	 
	void main()
	{
		graph g;
		int matrix[N][N]={{0,1,1,0,0,0,0},
						  {0,0,0,0,0,1,1},
				    	  {0,0,0,0,0,0,1},
						  {0,0,1,0,1,0,0},
						  {0,0,0,0,0,0,1},
						  {0,0,0,0,0,0,0},
						  {0,0,0,0,0,0,0}};
		char vertex[N]={'A','B','C','D','E','F','G'};//初始化
			for(int i=0;i<N;i++)
			{
				g.vexs[i]=vertex[i];
				for(int j=0;j<N;j++)
					g.arcs[i][j]=matrix[i][j];
			}
		TopoSort_matrix(g);
		printf("\n");
	}

>分析此拓扑排序算法可知，如果AOV网络有n个顶点，e条边，在拓扑排序的过程中，搜索入度为零的顶点，建立链式栈所需要的时间是O(n)。在正常的情况下，有向图有n个顶点，每个顶点进一次栈，出一次栈，共输出n次。顶点入度减一的运算共执行e次。所以总的时间复杂度为O(n+e)。

##五、关键路径
>定义几个与计算关键活动有关的量：
>
>1. 事件Vi的最早可能开始时间ee(i):是从源点V1到顶点Vi的最长路径长度。
>2. 事件Vi的最迟允许开始时间le[i]:是在保证汇点在ee[n]时刻完成的前提下，事件Vi的允许的最迟开始时间。le[i]等于ee[n]减去顶点i到顶点n的最长路径长度。
>3. 活动ai的最早可能开始时间e[k]：设活动ai在边<Vj,Vk>上，则e[i]是从源点V1到顶点Vj的最长路径长度。因此,e[i]=ee[j]
>4. 活动ai的最迟允许开始时间 l[i]：l[i]是在不会引起时间延误的前提下，该活动允许的最迟开始时间。l[i] =le[k]-dur(<j, k>)其中，dur(<j, k>)是完成ai所需的时间。
>5. 时间余量l[i]-e[i]：表示活动ai的最早可能开始时间和最迟允许开始
时间的时间余量，l[i]==e[i]表示活动ai是没有时间
余量的关键活动。
>6. 为找出关键活动，需要求各个活动的e[i]与l[i]，以判别是否l[i]==e[i]。

#
>求ee[k]的递推公式: 从ee[1]=0开始，向前递推ee[k] = max{ ee[j]+ dur(<Vj , Vk>)} <Vj,Vk>∈S2, j=1, 2,...,n-1
S2是所有指向Vk的有向边<Vj,Vk>的集合。
#
>从le[n]=ee[n]开始，反向递推le[k] = min{le[j] - dur(<Vj , Vk>)} <Vj,Vk>∈S1,k=n-2,n-3,...,0 ; S1是所有源自Vk的有向边<Vk,Vj>的集合。

![](https://i.imgur.com/PMAbJSe.jpg)
![](https://i.imgur.com/ujoImg1.jpg)
![](https://i.imgur.com/wBWeISZ.jpg)
![](https://i.imgur.com/EP03FS4.jpg)

	//利用关键路径法求AOE网的各关键活动
	void CriticalPath(Graph <Type> &G) {
	//在此算法中需要在邻接表中单链表的结点内 //增加一个int型cost域，记录该边上的权值
		int i,j,k; float e,l,w;
		int n=G.NumberOfVertices( ); float *ee=new float [n];
		float *le=new float [n];
		for (i=0;i<n; i++) ee[i]=0;
		for (i=0;i<n;i++) {  //顺向计算ee[]
			j=G.GetFirstNeighbor(i); 
			while (j!=-1){
				w=G.GetWeight(i,j);
				if (ee[i]+w>ee[j]) ee[j]=ee[i]+w; j=G.GetNextNeighbor(i,j);
			}
		}
		e[n-1]=ee[n-1];
		for (j=n-2;j>0;j--){  //逆向计算le[]
			k=G.GetFirstNrighbor(j); 
			while (k!=-1){
				w=G.GetWeight(j,k);
				if (le[k]-w<le[j]) le[j]=le[k]-w; k=G.GetNextNeighbor(j,k);
			}
		}
		for (i=0;i<n;i++) {  //求各活动的e、l
			j=G.GetFirstNeighbor(i); 
			while (j!=-1) {
				e=ee[i]; l=le[j]-G.GetWeight(i,j); 
				if (l==e)
					cout<<“<”<<i<<“,”<< j <<“>”<<“是关键活动”<<endl; j=G.GetNextNeighbor(i,j);
			}
		}
	}