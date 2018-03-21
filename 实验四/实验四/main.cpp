#include"Graph.h"
#include"Maze.h"
#include<iostream>
#include<stdlib.h>
#include<fstream>
using namespace std;
template<typename iterator>
void Display(iterator first, iterator last) {
	for (; first != last; first++)
		cout << *first;
}
template<typename T>
void Display(const Graph<T>& g, PathData* E, int ne)
{
	T v1, v2;
	for (int i = ne - 1; i > -1; i--)
	{
		g.FindNode(v1, E[i].start);
		g.FindNode(v2, E[i].dest);
		cout << '(' << v1 << ',' << v2 << ',' << E[i].cost << ')' << endl;
	}
}
template<typename T>
void Display(const Graph<T>& G, double *D, int *P, int n)
{
	T v;
	int parent, i, j, *stack = new int[n], size;
	for (i = 0; i<n; i++)
		if (D[i])
		{
			cout << D[i] << ": ";
			size = 0;
			stack[size++] = i;
			parent = P[i];
			while (parent != -1)
			{
				stack[size++] = parent;
				parent = P[parent];
			}
			for (j = size - 1; j > -1; j--)
			{
				G.FindNode(v, stack[j]);
				cout << v;
				if (j > 0)
					cout << "->";
			}
			cout << endl;
		}
	delete[] stack;
}
template<typename T>
void Display(const Graph<T>& G, double* A[], int* P[], int nv)
{
	T v;
	int i, j, k, *stack = new int[nv], size;
	cout << "Floyd:\n";
	for (i = 0; i<nv; i++)
		for (j = 0; j<nv; j++)
			if (i != j&&P[i][j] != -1)
			{
				cout << A[i][j] << ": ";
				size = 0;
				stack[size++] = j;
				k = P[i][j];
				while (i != k)
				{
					stack[size++] = k;
					k = P[i][k];
				}
				stack[size++] = i;
				for (k = size - 1; k > -1; k--)
				{
					G.FindNode(v, stack[k]);
					cout << v;
					if (k > 0)
						cout << "->";
				}
				cout << endl;
			}
	delete[] stack;
}
void PutPath(int* P[], int i, int j)							//输出路径的递归算法
{
	int k = P[i][j];
	if (k == i)
	{
		cout << j;
		return;
	}
	PutPath(P, i, k);
	cout << "->" << j;
}
void Display(double* A[], int* P[], int nv)
{
	int i, j;
	cout << "Floyd:\n";
	for (i = 0; i<nv; i++)
		for (j = 0; j<nv; j++)
			if (i != j&&P[i][j] != -1)
			{
				cout << A[i][j] << ": ";
				cout << i << "->";
				PutPath(P, i, j);
				cout << endl;
			}
}
template<typename T>
void Display(const Graph<T>& G, int P[], const T& sv, const T& dv)
{
	T v;
	int si = G.FindNode(sv), dj = G.FindNode(dv), size = 0;
	if (si == -1 || dj == -1)
		return;
	int *stack = new int[G.SizeV()];
	stack[size++] = dj;
	while (dj != si)
	{
		stack[size++] = P[dj];
		dj = P[dj];
	}
	for (int k = size - 1; k > -1; k--)
	{
		G.FindNode(v, stack[k]);
		cout << v;
		if (k > 0)
			cout << "->";
	}
	cout << endl;
	delete[]stack;
}
template<typename T>
void Display(const Graph<T>& G, const double* VE, const double* VL, int nv)
{
	T vj, vi;
	for (int j = 0; j<nv; j++)
		for (int i = 0; i < nv; i++)
		{
			G.FindNode(vi, i);
			G.FindNode(vj, j);
			if (G.GetCost(vi, vj) != 0)
				cout << '<' << vi << ',' << vj << '>' << "-----" << VL[j] - VE[i] - G.GetCost(vi, vj) << endl;
		}
}

int main(){
//Graph<char> G(20);
//cout<<"Input:\n";
//cin>>G;
//cout<<"Ouput:\n";
//cout<<G;
//return 0;
	/*Graph<char> G(20);
	ifstream fin;
	fin.open("D:\\Graph1_in.txt",ios::in|ios::_Nocreate);
	if (!fin) {
		cout << "cannot open this Graph1_in.txt";
		exit(1);
	}
	fin >> G;
	ofstream fout;
	fout.open("D:\\Graph1_out.txt", ios::out);
	if (!fout) {
		cout << "cannot open this Graph1_out.txt";
		exit(1);
	}
	fout << G;
	return 0;*/
	/*Graph<char> G;
	G.ReadGraph("D:\\Graph1_in.txt");
	G.WriteGraph("D:\\out.txt");
	return 0;*/
	/*Graph<char> G(20);
	G.ReadGraph("D:\\Graph1_in.txt");
	cout << G;
	G.DeleteV('C');
	cout << "after deleting 'c':\n";
	G.WriteGraph("D:\\Graph_out2.txt");
	cout << G;
	return 0;*/
	/*Graph<char> G;
	G.ReadGraph("D:\\Graph2_in.txt");
	cout << G;
	list<char> L;
	G.BFS(L,'A');
	Display(L.begin(), L.end());
	L.clear();
	cout << endl;

	G.BFS(L);
	Display(L.begin(), L.end());
	cout << endl;
	L.clear();

	G.DFS(L, 'A');
	Display(L.begin(), L.end());
	L.clear();
	cout << endl;

	G.DFS(L);
	Display(L.begin(), L.end());
	cout << endl;
	return 0;*/
	Graph<char> G;
	G.ReadGraph("D:\\Graph_in2.txt");
	cout << G;
	PathData *E = new PathData[G.SizeV() - 1];
	if (G.Prim('A', E, G.SizeV() - 1))
	{
		cout << "Prim:\n";
		Display(G, E, G.SizeV() - 1);
	}
	return(0);
	/*Graph<char> G;
	G.ReadGraph("D:\\Graph_in2.txt");
	cout << G;
	PathData *E = new PathData[G.SizeV() - 1];
	if (G.Kruskal(E, G.SizeV() - 1))
	{
		cout << "Kruskal:\n";
		Display(G, E, G.SizeV() - 1);
	}
	return(0);*/
	/*Graph<char> G;
	G.ReadGraph("D:\\graphin4.txt");
	cout << G;
	double D[20];
	int P[20];
	if (G.Dijkstra('A', D, P, G.SizeV()))
	{
		cout << "Dijkstra:\n";
		Display(G, D, P, G.SizeV());
	}
	return(0);*/
	//int i;
	//Graph<char> G;
	//G.ReadGraph("D:\\graphin4.txt");
	//cout << G;
	//double **A;
	//int **P;
	//A = new double*[G.SizeV()];
	//P = new int*[G.SizeV()];
	//for (i = 0; i < G.SizeV(); i++)
	//{
	//	A[i] = new double[G.SizeV()];
	//	P[i] = new int[G.SizeV()];
	//}
	//G.Floyd(A, P, G.SizeV());
	//Display(G, A, P, G.SizeV());
	////Display(A, P, G.SizeV());
	//for (i = 0; i < G.SizeV(); i++)
	//{
	//	delete[]A[i];
	//	delete[]P[i];
	//}
	//delete[]A;
	//delete[]P;
	//return(0);
//Graph<char> G;
//G.ReadGraph("D:\\graphin4.txt");
//cout << G;
//int* P = new int[G.SizeV()];
//int n = G.MinPath(P, 'A', 'C');
//if (n == -1)
//{
//	cout << "A或C不存在，或者从A到C的路径不存在。" << endl;
//}
//else
//{
//	cout << "从A到C的最短带权路径为" << n << ':';
//	Display(G, P, 'A', 'C');
//}
//delete[]P;
//return(0);
//Graph<char> G;
//G.ReadGraph("D:\\graphin5.txt");
//cout << G;
//list<char> L;  
//G.TopSort(L);
//cout << "TopSort:\n";
//Display(L.begin(), L.end());
//return(0);
//Graph<char> G;
//G.ReadGraph("D:\\graphin6.txt");
//static double VE[9], VL[9];
//G.CriticalPath(VE, VL, G.SizeV());
//Display(G, VE, VL, G.SizeV());
//return(0);
//char* maze[7] = { "1111111","1000011","1111011","1000001","1011101","1000001","1111111" };
//char** pc = maze;
//Maze M(pc, 7, 7, 1, 1, 5, 5);
//M.AllPath();
//return(0);
}


