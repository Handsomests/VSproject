#include"Graph.h"
#include<iostream>
#include<stdlib.h>
using namespace std;
template<typename T>
void Display(const Graph<T>& g, PathData* E, int ne) {
	T v1, v2;
	for (int i = 0; i < ne; i++) {
		g.FindNode(v1, E[i].start);
		g.FindNode(v2, E[i].dest);
		cout << '(' << v1 << ',' << v2 << ',' << E[i].cost << ')' << endl;
	}
}
template<typename T>
void Display(const Graph<T>& G, double *D, int *P, int n) {
	T v;
	int parent, i, j, *stack = new int[n], size;
	for(i=0;i<n;i++)
		if (D[i]) {
			cout << D[i] << ": ";
			size = 0;
			stack[size++] = i;
			parent = P[i];
			while (parent != -1) {
				stack[size++] = parent;
				parent = P[parent];
			}
			for (j = size - 1; j > -1; j--) {
				G.FindNode(v, stack[j]);
				cout << v;
				if (j > 0)
					cout << "->";
			}
			cout << endl;
		}
	delete[]stack;
}
int main() {
	/*Graph<char> G;
	G.ReadGraph("D:\\Graph_in2.txt");
	cout << G;
	PathData *E = new PathData[G.SizeV() - 1];
	if (G.Kruskal(E, G.SizeV() - 1)) {
		cout << "k:\n";
		Display(G, E, G.SizeV() - 1);
	}
	return 0;*/
	Graph<char> G;
	G.ReadGraph("D:\\graphin4.txt");
	cout << G;
	double D[20];
	int P[20];
	if (G.Dijkstra('A', D, P, G.SizeV())) {
		cout << "D:\n";
		Display(G, D, P, G.SizeV());
	}
	return 0;
}
