typedef int Type;
#include"seqlist.h"
#include<iostream>
using namespace std;
void display_seqlist(Type* first, Type * last);
void bubble_seqlist(SeqList &L);
int main() {
	SeqList L(100);
	int temp;
	cout << "input 10 integers:\n";
	for (int i = 0; i < 10; ++i) {
		cin >> temp;
		Type * p = L.Begin();
		L.Insert(p+i,temp);
	}
	bubble_seqlist(L);
	display_seqlist(L.Begin(), L.End());
	
	return 0;
}
void bubble_seqlist(SeqList &L) {
	int i, j, last, n = L.Size();
	Type temp=0;
	i = 0;
	while (i < n - 1) {
		last = n - 1;
		for (j = n - 1; j > i; j--) 
			if (L[j] < L[j - 1])
			{
			temp = L[j - 1];
			L[j - 1] = L[j];
			L[j] = temp;
			last = j;
			//cout << L[j] << L[j - 1] <<"************"<< endl;
		}
		i = last;
	}
}
void display_seqlist(Type * first, Type * last) {
	for (; first != last; ++first)
		cout << *first << '\t';
	cout << endl;

}