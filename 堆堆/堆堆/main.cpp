#include<iostream>
#include<vector>
#include"Heap.h"
using namespace std;
//void main() {
//	vector<int> v;
//	for (int i = 1; i < 100; i++)
//		v.push_back(rand() % 100);
//	Heap<int> h(v);
//	v.clear();
//	int x;
//	while (!h.Empty()) {
//		h.DeleteMin(x);
//		v.push_back(x);
//	}
//	for (int t = 0;t<v.size();t++)
//		cout << v[t] << '\t';
//}
void main() {		
	cout << "ÊäÈë"<<endl;
	int a[6], s;
	for (int i = 0; i < 6; i++) {
		cin >> s;
		a[i] = s;
	}	
	HeapSort(a, 6);	
	for (int t = 0; t < 6; t++)
		cout << a[t] << '\t';
}

//#include"HufmLib.h"    //
//int main() {
//	int a[] = { 7,5,2,4 };
//	BTNode<int>* root;
//	root = MakeHufm(a, 4);
//	PrintBTree(root, 40);
//	cout << endl;
//	return 0;
//}