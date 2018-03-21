#pragma once
#include<fstream>
#include<iostream>
#include<list>
#include<queue>
#include"Heap.h"
using namespace std;
const double MAXCOST = 10000;				//最大权
struct PathData
{
	int start, dest;
	double cost;
	operator double()const { return(cost); }
};
template<typename T>
class Graph
{
	struct EdgeNode                  //边节点数据结构
	{
		int dest;                    //边的终点下标
		double cost;                  //边的权
		operator int() { return dest; }
	};
	T * VA;                           //顶点数组指针
	list<EdgeNode>* HL;               //边链表数组指针
	int sizeV, sizeE;                  //顶点数和边数
	int maxV;                         //顶点数组空间长度
	double GetCost(int si, int dj)const;     //按始点和终点下标读取边的权
											 //void BFS(list<T>& L, int pos, bool * visited)const;    //广度优先遍历
											 //void DFS(list<T>& L, int pos, bool * visited)const;   //深度优先遍历,私有函数												
	void BuildHeap(PathData* E, int size)const;
	void PercolateDown(PathData* E, int pos, int size)const;

	bool TopSort(int* t, int nv)const;													//把拓扑序列的顶点序号存入数组t，参量nv表示图的顶点个数
	int InDegree(int id)const
	{
		int count = 0;
		for (int i = 0; i < sizeV; i++)
			for (list<EdgeNode>::const_iterator first = HL[i].begin(), last = HL[i].end(); first != last; ++first)
				if ((*first).dest == id)
					count++;
		return count;
	}
public:
	Graph(int n = 100) :sizeV(0), sizeE(0), maxV(n) {     //构造函数
		HL = new list<EdgeNode>[n];
		VA = new T[n];
	}
	~Graph() { delete[]VA; delete[]HL; }     //析构函数
	int Empty()const { return(sizeV == 0); }  //判空
	int Full()const { return(sizeV == maxV); } //判满
	int SizeV()const { return(sizeV); }       //取顶点数
	int SizeE()const { return(sizeE); }       //取边数
	double GetCost(const T& v1, const T& v2)const;   //通过边的始点和终点取权
	int FindNode(const T& v)const;              //取顶点的下标
	bool FindNode(T& v, int pos)const;              //将下标为pos的顶点插入v中
	bool InsertV(const T&v);                        //插入顶点
	bool InsertE(const T& v1, const T& v2, double w);  //插入边
	bool DeleteV(const T&v);                             //删除顶点
	bool DeleteE(const T& v1, const T& v2);             //删除边
	void ReadGraph(const char* filename);               //从磁盘文件写入图的数据
	void WriteGraph(const char* filename);              //王磁盘文件写入图的数据 
	void BFS(list<T>& L, const T& v)const;             //广度优先遍历
	void BFS(list<T>& L)const;                         //完善版广度优先遍历
	void DFS(list<T>& L, const T& v)const;               //深度优先遍历
	void DFS(list<T>& L)const;                          //完善版深度优先遍历
	void BFS(list<T>& L, int pos, bool * visited)const;    //广度优先遍历
	void DFS(list<T>& L, int pos, bool * visited)const;   //深度优先遍历,私有函数


	bool Prim(const T& v, PathData* E, int ne)const;							//普里姆算法
	bool Kruskal(PathData* E, int ne)const;										//克鲁斯卡尔算法
	bool Dijkstra(const T& v, double *D, int *P, int nv)const;				//迪克斯特拉算法
	void Floyd(double *A[], int *P[], int nv)const;								//弗洛伊德算法
	double MinPath(int P[], const T& sv, const T& dv)const;				//一顶点对之间的最短带权路径
	bool TopSort(list<T>& L)const;													//把拓扑序列存入表L
	void CriticalPath(double* VE, double* VL, int nv)const;				//把每个事件的最早发生时间和最迟发生时间分别记录在数组VE和VL中，nv表示顶点数

	template<typename T>
	friend ostream& operator<<(ostream& ostr, const Graph<T>& g) {  //重载输出运算符
		for (int i = 0; i < g.sizeV; i++) {
			ostr << i << '-' << g.VA[i] << ':';          // 输出顶点下标和顶点
			list<Graph<T>::EdgeNode>::iterator first = g.HL[i].begin(), last = g.HL[i].end();
			for (; first != last; first++)
				ostr << '(' << (*first).dest << ',' << (*first).cost << ')' << ' ';
			ostr << endl;
		}
		return ostr;
	}
	template<typename T>
	friend istream& operator >> (istream& istr, Graph<T>& g) {//重载输入运算符   读取数据建立邻接表
		char s[500]; int n; double w;
		T v1, v2;
		istr >> s >> n;
		for (int i = 1; i <= n; ++i) {
			istr >> v1;
			g.InsertV(v1);
		}
		istr >> s >> n;
		for (int i = 1; i <= n; i++)
		{
			istr >> v1 >> v2 >> w;
			g.InsertE(v1, v2, w);
		}
		return (istr);
	}
};
template<typename T>
int Graph<T>::FindNode(const T & v)const             //取顶点的下标
{
	for (int i = 0; i < sizeV; i++)
		if (VA[i] == v)
			return(i);
	return(-1);
}
template<typename T>
bool Graph<T>::FindNode(T& v, int pos)const         //将下标为pos的顶点存到v中
{
	if (pos < 0 || pos >= sizeV)                            //pos值非法
		return 0;
	v = VA[pos];
	return 1;
}
template<typename T>
bool Graph<T>::InsertV(const T& v)               //插入顶点
{
	if (sizeV == maxV)
		return 0;
	VA[sizeV] = v;
	sizeV++;
	return 1;
}
template<typename T>
bool Graph<T>::InsertE(const T& v1, const T& v2, double w)     //插入边
{
	int si = FindNode(v1), dj = FindNode(v2);
	if (si == -1 || dj == -1 || si == dj)
		return 0;
	EdgeNode en;
	en.dest = dj;
	en.cost = w;
	HL[si].insert(HL[si].end(), en);
	sizeE++;
	return 1;
}
template<typename T>
void Graph<T>::ReadGraph(const char * filename) {     //从文件中读取图的数据
	char str[50];
	int n;
	double w;
	T v1, v2;
	ifstream fin;
	fin.open(filename, ios::in | ios::_Nocreate);
	if (!fin) {
		cout << "cannot open this txt\n";
		exit(1);
	}
	fin >> str >> n;
	for (int i = 1; i <= n; ++i) {
		fin >> v1;
		InsertV(v1);
	}
	fin >> str >> n;
	for (int i = 1; i <= n; ++i) {
		fin >> v1 >> v2 >> w;
		InsertE(v1, v2, w);
	}
}
template<typename T>
void Graph<T>::WriteGraph(const char*filename)    //往磁盘文件中输入图的数据
{
	ofstream fout;
	fout.open(filename, ios::out);
	if (!fout) {
		cout << "cannot open" << filename << endl;
		exit(1);
	}
	for (int i = 0; i < sizeV; i++) {
		fout << i << '-' << VA[i] << ':';          // 输出顶点下标和顶点
		list<Graph<T>::EdgeNode>::iterator first = HL[i].begin(), last = HL[i].end();
		for (; first != last; first++)
			fout << '(' << (*first).dest << ',' << (*first).cost << ')' << ' ';
		fout << endl;
	}
}
template<typename T>
bool Graph<T>::DeleteE(const T& v1, const T& v2)       //删除边
{
	int si = FindNode(v1), dj = FindNode(v2)             ////确定边的始点和终点的下标
		if (si == -1 || dj == -1 || dj == si)
			return 0;
	list<EdgeNode>::iterator first = HL[si].begin(), last = HL[si].end();
	for (; first != last; first++)
		if ((*first).dest == dj) {
			HL[si].erase(first);
			SizeE--;
			return 1;
		}
	return 0;
}
template<typename T>                 //删除顶点
bool Graph<T>::DeleteV(const T& v)
{
	int si = FindNode(v);
	if (si == -1)
		return 0;
	int size = HL[si].size();
	for (int i = size; i < sizeV - 1; i++)
	{
		VA[i] = VA[i + 1];             //通过移动赋值,要删除的顶点被删除
		HL[i] = HL[i + 1];             //所删除的顶点的边链表被删除
	}
	HL[sizeV - 1].clear();            //清空原来边链表的尾元素
	sizeV--;
	sizeE = sizeE - size;              //现在的边数

	list<EdgeNode>::iterator first, last;
	for (int i = 0; i < sizeV; i++)
	{
		first = HL[i].begin(); last = HL[i].end();
		for (; first != last; first++)
		{
			if ((*first).dest == si)
			{
				HL[i].erase(first);           //删除边结点
				sizeE--; break;
			}
		}
	}
	for (int i = 0; i < sizeV; i++)           //修改边结点
	{
		first = HL[i].begin(); last = HL[i].end();
		for (; first != last; first++)
			if ((*first).dest > si)
				(*first).dest--;              //数据项dest减一
	}
	return 1;
}
//读取边的权
template<typename T>
double Graph<T>::GetCost(int si, int dj)const
{
	if (si < 0 || si >= sizeV || dj < 0 || dj >= sizeV || si == dj)
		return(0);
	list<EdgeNode>::const_iterator first = HL[si].begin(), last = HL[si].end();
	for (; first != last; ++first)
		if ((*first).dest == dj)
			return((*first).cost);
	return(0);
}
template<typename T>
double Graph<T>::GetCost(const T& v1, const T& v2)const    //共有函数
{
	return (GetCost(FindNode(v1), FindNode(v2)));
}
//从一个顶点开始广度优先遍历,将访问的顶点按照访问顺序存储到链表L中
template<typename T>
void Graph<T>::BFS(list<T>& L, const T & v)const {
	int pos = FindNode(v);      //取顶点的下标
	if (pos == -1)
		return;
	bool * visited = new bool[sizeV];      //标记数组
	for (int i = 0; i < sizeV; i++)        //初始值为0
		visited[i] = 0;
	queue<int>Q;
	Q.push(pos);
	visited[pos] = 1;
	list<EdgeNode>::const_iterator first, last;
	while (!Q.empty()) {
		pos = Q.front();
		Q.pop();
		L.push_back(VA[pos]);          //将顶点放入链表中去
		first = HL[pos].begin();
		last = HL[pos].end();
		for (; first != last; ++first)
			if (visited[(*first).dest] == 0) {
				Q.push((*first).dest);
				visited[(*first).dest] = 1;
			}
	}
	delete[] visited;
}
//从一个顶点开始广度优先遍历,在扫描标志数组,观察是否存在没有访问的顶点,存在就以此顶点开始广度优先遍历
template<typename T>
void Graph<T>::BFS(list<T>& L)const {      //遍历图的所有顶点
	bool *visited = new bool[sizeV];
	for (int i = 0; i < sizeV; i++)
		visited[i] = 0;
	for (int i = 0; i < sizeV; i++)
		if (visited[i] == 0)
			BFS(L, i, visited);
	delete[] visited;
}
template<typename T>
void Graph<T>::BFS(list<T>& L, int pos, bool *visited)const {
	if (pos < 0 || pos >= sizeV)
		return;
	queue<int> Q;
	Q.push(pos);
	visited[pos] = 1;
	list<EdgeNode>::const_iterator first, last;
	while (!Q.empty()) {
		pos = Q.front();
		Q.pop();
		L.push_back(VA[pos]);          //将顶点放入链表中去
		first = HL[pos].begin();
		last = HL[pos].end();
		for (; first != last; ++first)
			if (visited[(*first).dest] == 0) {
				Q.push((*first).dest);
				visited[(*first).dest] = 1;
			}
	}
}
//深度优先遍历
template<typename T>
void Graph<T>::DFS(list<T>& L, const T& v)const
{      //从某一顶点开始深度优先遍历.公有函数 
	int pos = FindNode(v);
	if (pos == -1)
		return;
	bool *visited = new bool[sizeV];
	for (int i = 0; i < sizeV; i++)
		visited[i] = 0;
	DFS(L, pos, visited);

}
template<typename T>
void Graph<T>::DFS(list<T>& L, int pos, bool *visited)const    //从始点深度遍历.私有函数作为内部方法 
{
	if (pos < 0 || pos >= sizeV)
		return;
	L.push_back(VA[pos]); //访问始点
	visited[pos] = 1;     //访问标记
	list<EdgeNode>::const_iterator first, last;   //边链表迭代器
	first = HL[pos].begin();
	last = HL[pos].end();
	for (; first != last; first++)
		if (visited[(*first).dest] == 0)                 //如果未被访问
			DFS(L, (*first).dest, visited);
}
template<typename T>
void Graph<T>::DFS(list<T>& L)const {
	bool *visited = new bool[sizeV];
	for (int i = 0; i < sizeV; i++)
		visited[i] = 0;
	for (int i = 0; i < sizeV; i++)
		if (visited[i] == 0)
			DFS(L, i, visited);
	delete[]visited;
}
template<typename T>
void Graph<T>::BuildHeap(PathData* E, int size)const
{
	for (int i = size / 2 - 1; i >= 0; i--)
		PercolateDown(E, i, size);
}
template<typename T>
void Graph<T>::PercolateDown(PathData* E, int pos, int size)const
{
	int p = pos, c = 2 * p + 1;
	PathData temp = E[p];
	while (c < size)
	{
		if (c + 1 < size&&E[c + 1] < E[c])
			++c;
		if (temp < E[c])
			break;
		else
		{
			E[p] = E[c];
			p = c;
			c = 2 * p + 1;
		}
	}
	E[p] = temp;
}
template<typename T>
bool Graph<T>::Prim(const T& v, PathData* E, int ne)const
{
	int i, j, s, ns;
	PathData item;
	double cost;
	s = FindNode(v);
	if (s == -1)
		return(0);
	int id = 0;
	for (i = 0; i <= ne; i++)
		if (i != s)
		{
			item.start = s;
			item.dest = i;
			cost = GetCost(s, i);
			item.cost = (cost == 0 ? MAXCOST : cost);
			E[id++] = item;
		}
	int count = 0;
	BuildHeap(E, ne);
	for (i = 0; i < ne; i++)
	{
		if (E[0] < MAXCOST)
			count++;
		ns = E[0].dest;
		for (j = 1; j < ne - i; j++)
		{
			cost = GetCost(ns, E[j].dest);
			cost = (cost == 0 ? MAXCOST : cost);
			if (E[j] > cost)
			{
				E[j].cost = cost;
				E[j].start = ns;
			}
		}
		item = E[0];
		E[0] = E[ne - 1 - i];
		E[ne - 1 - i] = item;
		PercolateDown(E, 0, ne - 1 - i);
	}
	return(count == ne ? 1 : 0);
}
template<typename T>   //克鲁斯卡尔算法
bool Graph<T>::Kruskal(PathData * E, int ne)const {
	Heap<PathData> H;
	int nv = ne + 1;             //最小生成树的顶点个数是边的数量加1
	int i, j, id, *DS = new int[nv];
	for (i = 0; i < nv; i++)
		DS[i] = -1;
	double cost;             //按权值大小将其插入到小根堆中去
	PathData e;
	for(i=0;i<nv;i++)
		for (j = i + 1; j < nv; j++) {
			cost = GetCost(i, j);
			if (cost != 0) {
				e.start = i;
				e.dest = j;
				e.cost = cost;
				H.Insert(e);
			}
		}
	id = 0;    
	while (!H.Empty()) {
		H.DeleteMin(e);
		i = e.start;
		while (DS[i] >= 0)
			i = DS[i];
		j = e.dest;
		while (DS[j] >= 0)     //寻找终点在连通子网的根
			j = DS[j];
		if (i != j) {
			if (i < j) {
				DS[i] = DS[i] + DS[j];
				DS[j] = i;
			}
			else {
				DS[j] += DS[i];
				DS[i] = j;
			}
			E[id++] = e;
		}
	}
	delete []DS;
	return(id == ne ? 1 : 0);
}
template<typename T>
bool Graph<T>::Dijkstra(const T& v, double *D, int *P, int nv)const {
	int i, j, s, ns, ne = nv - 1;   //ne是最小生成树的边数
	PathData item, *E = new PathData[ne];
	double cost;
	s = FindNode(v);
	if (s == -1)
		return 0;
	D[s] = 0;     //D数组记录带权长度,P数组记录顶对应的前驱序号
	P[s] = -1;
	int id = 0;
	for (i = 0; i <= ne; i++) 
		if (i != s) {
			item.start = s;
			item.dest = i;
			cost = GetCost(s, i);
			item.cost = (cost == 0 ? MAXCOST : cost);
			E[id++] = item;
			D[i] = item.cost;
			P[i] = (cost == 0 ? -1 : s);
		}
	int count = 0;
	BuildHeap(E, ne);
	for (i = 0; i < ne; i++) {
		if (E[0] < MAXCOST)
			count++;
		ns = E[0].dest;
		for (j = 1; j < ne - i; j++) {
			cost = GetCost(ns, E[j].dest);
			cost = (cost == 0 ? MAXCOST : cost);
			if (E[j] > E[0] + cost) {
				E[j].cost = E[0].cost + cost;
				E[j].start = ns;
				D[E[j].dest] = E[j].cost;
				P[E[j].dest] = ns;
			}
		}
		item = E[0];
		E[0] = E[ne - 1 - i];
		E[ne - 1 - i] = item;
		PercolateDown(E, 0, ne - 1 - i);
	}
	delete[]E;
	return(count == ne ? 1 : 0);
}