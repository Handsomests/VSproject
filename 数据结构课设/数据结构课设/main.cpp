#include"AvlTree.h"
#include<iostream>
#include<list>
#include<fstream>
#include<string>
using namespace std;
int main() {
	AvlTree<char *> L;
	L.Insert("happy");
	L.Insert("no");
	L.Insert("non");
	L.Insert("nob");
	L.PrintAvlTree(80);
	cout<<L.FindNode("no");
	return 0;
}