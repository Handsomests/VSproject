#include"Tree.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
template<typename Iterator>
void Display(Iterator first, Iterator last) {
	for (; first != last; ++first)
		cout << *first;
}
int main()
{
	//Tree<char> T(20);
	//ifstream fin;
	//fin.open("D:\\treein.txt", ios::in | ios::_Nocreate);  //磁盘文件
	//if (!fin)
	//{
	//	cout << "cannot open D:\\treein.txt";
	//	exit(1);
	//}
	//fin >> T;
	//ofstream fout;
	//fout.open("D:\\treeout.txt", ios::out);
	//if (!fout)
	//{
	//	cout << "cannot open D:\\treeout.txt";
	//	exit(1);
	//}
	//fout << T;    
	///*cout << "you hava succeed!";*///树的数据被写入磁盘文件treeout
	//return 0;

	/*Tree<char> T(40);
	cin >> T;
	cout << T;
	return 0;*/
	/*Tree<char> s;
	char *a = "D:\\treein.txt";
	 char *a1 = "D:\\treeout.txt";	 
	s.ReadTree(a);
	cout << "you hava succeed ReadTree!";
	s.WriteTree(a1);
	cout << "you hava succeed WriteTree!";*/


	Tree<char>T(20);
	ifstream fin;
	fin.open("D:\\treein.txt", ios::in | ios::_Nocreate);  //打开已存在的磁盘文件
	if (!fin) {
		cout << "cannot open D:\\treein.txt\n";
		exit(1);
	}
	fin >> T;
	cout << T;
	cout << endl;
	list<char> L;
	T.DFS(L);
	cout << "after DFS:\n";
	Display(L.begin(), L.end());
	cout << endl;
	
	L.clear();
	T.BFS(L);
	cout << "after BFS:\n";
	Display(L.begin(), L.end());
	cout << endl;
	L.clear();
	T.LFS(L);
	cout << "after LFS:\n";
	Display(L.begin(), L.end());
	cout << endl;
	L.clear();
	T.SimLFS(L);
	cout << "(非递归)after SimLFS:\n";
	Display(L.begin(), L.end());
	cout << endl;
	/*L.clear();
	T.SimLFS2(L);
	cout << "(非递归)after SimLFS2:\n";
	Display(L.begin(), L.end());
	cout << endl;*/
	L.clear();
	T.SimDFS(L);
	cout << "(非递归)after SimDFS:\n";
	Display(L.begin(), L.end());
	cout << endl;
	return 0;
}
