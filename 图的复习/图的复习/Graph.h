#pragma once
#include<fstream>
#include<iostream>
#include<list>
#include<queue>
#include"Heap.h"
using namespace std;
const double MAXCOST = 10000;				//���Ȩ
struct PathData
{
	int start, dest;
	double cost;
	operator double()const { return(cost); }
};
template<typename T>
class Graph
{
	struct EdgeNode                  //�߽ڵ����ݽṹ
	{
		int dest;                    //�ߵ��յ��±�
		double cost;                  //�ߵ�Ȩ
		operator int() { return dest; }
	};
	T * VA;                           //��������ָ��
	list<EdgeNode>* HL;               //����������ָ��
	int sizeV, sizeE;                  //�������ͱ���
	int maxV;                         //��������ռ䳤��
	double GetCost(int si, int dj)const;     //��ʼ����յ��±��ȡ�ߵ�Ȩ
											 //void BFS(list<T>& L, int pos, bool * visited)const;    //������ȱ���
											 //void DFS(list<T>& L, int pos, bool * visited)const;   //������ȱ���,˽�к���												
	void BuildHeap(PathData* E, int size)const;
	void PercolateDown(PathData* E, int pos, int size)const;

	bool TopSort(int* t, int nv)const;													//���������еĶ�����Ŵ�������t������nv��ʾͼ�Ķ������
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
	Graph(int n = 100) :sizeV(0), sizeE(0), maxV(n) {     //���캯��
		HL = new list<EdgeNode>[n];
		VA = new T[n];
	}
	~Graph() { delete[]VA; delete[]HL; }     //��������
	int Empty()const { return(sizeV == 0); }  //�п�
	int Full()const { return(sizeV == maxV); } //����
	int SizeV()const { return(sizeV); }       //ȡ������
	int SizeE()const { return(sizeE); }       //ȡ����
	double GetCost(const T& v1, const T& v2)const;   //ͨ���ߵ�ʼ����յ�ȡȨ
	int FindNode(const T& v)const;              //ȡ������±�
	bool FindNode(T& v, int pos)const;              //���±�Ϊpos�Ķ������v��
	bool InsertV(const T&v);                        //���붥��
	bool InsertE(const T& v1, const T& v2, double w);  //�����
	bool DeleteV(const T&v);                             //ɾ������
	bool DeleteE(const T& v1, const T& v2);             //ɾ����
	void ReadGraph(const char* filename);               //�Ӵ����ļ�д��ͼ������
	void WriteGraph(const char* filename);              //�������ļ�д��ͼ������ 
	void BFS(list<T>& L, const T& v)const;             //������ȱ���
	void BFS(list<T>& L)const;                         //���ư������ȱ���
	void DFS(list<T>& L, const T& v)const;               //������ȱ���
	void DFS(list<T>& L)const;                          //���ư�������ȱ���
	void BFS(list<T>& L, int pos, bool * visited)const;    //������ȱ���
	void DFS(list<T>& L, int pos, bool * visited)const;   //������ȱ���,˽�к���


	bool Prim(const T& v, PathData* E, int ne)const;							//����ķ�㷨
	bool Kruskal(PathData* E, int ne)const;										//��³˹�����㷨
	bool Dijkstra(const T& v, double *D, int *P, int nv)const;				//�Ͽ�˹�����㷨
	void Floyd(double *A[], int *P[], int nv)const;								//���������㷨
	double MinPath(int P[], const T& sv, const T& dv)const;				//һ�����֮�����̴�Ȩ·��
	bool TopSort(list<T>& L)const;													//���������д����L
	void CriticalPath(double* VE, double* VL, int nv)const;				//��ÿ���¼������緢��ʱ�����ٷ���ʱ��ֱ��¼������VE��VL�У�nv��ʾ������

	template<typename T>
	friend ostream& operator<<(ostream& ostr, const Graph<T>& g) {  //������������
		for (int i = 0; i < g.sizeV; i++) {
			ostr << i << '-' << g.VA[i] << ':';          // ��������±�Ͷ���
			list<Graph<T>::EdgeNode>::iterator first = g.HL[i].begin(), last = g.HL[i].end();
			for (; first != last; first++)
				ostr << '(' << (*first).dest << ',' << (*first).cost << ')' << ' ';
			ostr << endl;
		}
		return ostr;
	}
	template<typename T>
	friend istream& operator >> (istream& istr, Graph<T>& g) {//�������������   ��ȡ���ݽ����ڽӱ�
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
int Graph<T>::FindNode(const T & v)const             //ȡ������±�
{
	for (int i = 0; i < sizeV; i++)
		if (VA[i] == v)
			return(i);
	return(-1);
}
template<typename T>
bool Graph<T>::FindNode(T& v, int pos)const         //���±�Ϊpos�Ķ���浽v��
{
	if (pos < 0 || pos >= sizeV)                            //posֵ�Ƿ�
		return 0;
	v = VA[pos];
	return 1;
}
template<typename T>
bool Graph<T>::InsertV(const T& v)               //���붥��
{
	if (sizeV == maxV)
		return 0;
	VA[sizeV] = v;
	sizeV++;
	return 1;
}
template<typename T>
bool Graph<T>::InsertE(const T& v1, const T& v2, double w)     //�����
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
void Graph<T>::ReadGraph(const char * filename) {     //���ļ��ж�ȡͼ������
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
void Graph<T>::WriteGraph(const char*filename)    //�������ļ�������ͼ������
{
	ofstream fout;
	fout.open(filename, ios::out);
	if (!fout) {
		cout << "cannot open" << filename << endl;
		exit(1);
	}
	for (int i = 0; i < sizeV; i++) {
		fout << i << '-' << VA[i] << ':';          // ��������±�Ͷ���
		list<Graph<T>::EdgeNode>::iterator first = HL[i].begin(), last = HL[i].end();
		for (; first != last; first++)
			fout << '(' << (*first).dest << ',' << (*first).cost << ')' << ' ';
		fout << endl;
	}
}
template<typename T>
bool Graph<T>::DeleteE(const T& v1, const T& v2)       //ɾ����
{
	int si = FindNode(v1), dj = FindNode(v2)             ////ȷ���ߵ�ʼ����յ���±�
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
template<typename T>                 //ɾ������
bool Graph<T>::DeleteV(const T& v)
{
	int si = FindNode(v);
	if (si == -1)
		return 0;
	int size = HL[si].size();
	for (int i = size; i < sizeV - 1; i++)
	{
		VA[i] = VA[i + 1];             //ͨ���ƶ���ֵ,Ҫɾ���Ķ��㱻ɾ��
		HL[i] = HL[i + 1];             //��ɾ���Ķ���ı�����ɾ��
	}
	HL[sizeV - 1].clear();            //���ԭ���������βԪ��
	sizeV--;
	sizeE = sizeE - size;              //���ڵı���

	list<EdgeNode>::iterator first, last;
	for (int i = 0; i < sizeV; i++)
	{
		first = HL[i].begin(); last = HL[i].end();
		for (; first != last; first++)
		{
			if ((*first).dest == si)
			{
				HL[i].erase(first);           //ɾ���߽��
				sizeE--; break;
			}
		}
	}
	for (int i = 0; i < sizeV; i++)           //�޸ı߽��
	{
		first = HL[i].begin(); last = HL[i].end();
		for (; first != last; first++)
			if ((*first).dest > si)
				(*first).dest--;              //������dest��һ
	}
	return 1;
}
//��ȡ�ߵ�Ȩ
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
double Graph<T>::GetCost(const T& v1, const T& v2)const    //���к���
{
	return (GetCost(FindNode(v1), FindNode(v2)));
}
//��һ�����㿪ʼ������ȱ���,�����ʵĶ��㰴�շ���˳��洢������L��
template<typename T>
void Graph<T>::BFS(list<T>& L, const T & v)const {
	int pos = FindNode(v);      //ȡ������±�
	if (pos == -1)
		return;
	bool * visited = new bool[sizeV];      //�������
	for (int i = 0; i < sizeV; i++)        //��ʼֵΪ0
		visited[i] = 0;
	queue<int>Q;
	Q.push(pos);
	visited[pos] = 1;
	list<EdgeNode>::const_iterator first, last;
	while (!Q.empty()) {
		pos = Q.front();
		Q.pop();
		L.push_back(VA[pos]);          //���������������ȥ
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
//��һ�����㿪ʼ������ȱ���,��ɨ���־����,�۲��Ƿ����û�з��ʵĶ���,���ھ��Դ˶��㿪ʼ������ȱ���
template<typename T>
void Graph<T>::BFS(list<T>& L)const {      //����ͼ�����ж���
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
		L.push_back(VA[pos]);          //���������������ȥ
		first = HL[pos].begin();
		last = HL[pos].end();
		for (; first != last; ++first)
			if (visited[(*first).dest] == 0) {
				Q.push((*first).dest);
				visited[(*first).dest] = 1;
			}
	}
}
//������ȱ���
template<typename T>
void Graph<T>::DFS(list<T>& L, const T& v)const
{      //��ĳһ���㿪ʼ������ȱ���.���к��� 
	int pos = FindNode(v);
	if (pos == -1)
		return;
	bool *visited = new bool[sizeV];
	for (int i = 0; i < sizeV; i++)
		visited[i] = 0;
	DFS(L, pos, visited);

}
template<typename T>
void Graph<T>::DFS(list<T>& L, int pos, bool *visited)const    //��ʼ����ȱ���.˽�к�����Ϊ�ڲ����� 
{
	if (pos < 0 || pos >= sizeV)
		return;
	L.push_back(VA[pos]); //����ʼ��
	visited[pos] = 1;     //���ʱ��
	list<EdgeNode>::const_iterator first, last;   //�����������
	first = HL[pos].begin();
	last = HL[pos].end();
	for (; first != last; first++)
		if (visited[(*first).dest] == 0)                 //���δ������
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
template<typename T>   //��³˹�����㷨
bool Graph<T>::Kruskal(PathData * E, int ne)const {
	Heap<PathData> H;
	int nv = ne + 1;             //��С�������Ķ�������Ǳߵ�������1
	int i, j, id, *DS = new int[nv];
	for (i = 0; i < nv; i++)
		DS[i] = -1;
	double cost;             //��Ȩֵ��С������뵽С������ȥ
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
		while (DS[j] >= 0)     //Ѱ���յ�����ͨ�����ĸ�
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
	int i, j, s, ns, ne = nv - 1;   //ne����С�������ı���
	PathData item, *E = new PathData[ne];
	double cost;
	s = FindNode(v);
	if (s == -1)
		return 0;
	D[s] = 0;     //D�����¼��Ȩ����,P�����¼����Ӧ��ǰ�����
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