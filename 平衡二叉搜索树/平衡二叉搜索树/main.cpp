#include"AvlTree.h"
#include<iostream>
using namespace std;
template<typename Iterator>
void Display(Iterator first, Iterator last) {
	for (; first != last; ++first)
		cout << *first;
	cout << endl;
}

int main() {
	AvlTree<int> L;
	for (int i = 1; i <= 12; i++)
		L.Insert(i);
	L.PrintAvlTree(80);
	return 0;

	/*BSTree<int> L;
	int a[8] = { 8,11,10,3,2,6,4,5 };
	for (int i = 0; i < 8; i++)
	L.Insert(a[i]);
	L.PrintBTree(80);
	cout << "after deleting 3:\n" << endl;
	L.Remove('3');
	L.PrintBTree(80);
	cout << "after inserting 3:\n" << endl;
	L.Insert('3');
	L.PrintBTree(80);
	return 0;*/
	/*BSTree<int> L;
	int a[8] = { 8,11,10,3,2,6,4,5 };
	for (int i = 0; i < 8; i++)
	L.Insert(a[i]);
	L.PrintBTree(80);
	Display(L.begin(), L.end());
	return 0;*/
}