#include"BTNode.h"
#include"BTNodeLib.h"
#include<queue>
#include<iostream>
using namespace std;
template<typename T>
bool IsCompleteBinaryTree(const BTNode<T>* t)
{
	bool flag = false;
	queue<const BTNode<T>*>Q;
	Q.push(t);
	while (!Q.empty()) {
		t = Q.front();
		Q.pop();
		if (t == NULL) {
			t = Q.front();
			Q.pop();
			if (t != NULL) {
				break;
			}
		}
		else if (flag) {
			Q.push(t->left);
			Q.push(t->right);
		}
	}
		return flag;
}template<typename T>
void Display(vector<T> &L) {
	vector<T>::iterator first = L.begin(), last = L.end();
	for (; first != last; first++) {
		cout << *first;
			cout << endl;
	}
}
int main() {
	vector<char> L;
	char a[15] = { 'A','B','C','\0','D','\0','E','\0','\0','F' };  //节点的完全层次序列
	for (int i = 0; i < 10; i++)
		L.push_back(a[i]);
//	Display(L);
	BTNode<char>* t = MakeLined(L);                             //生成二叉链表
	PrintBTree(t, 40);   //垂直输出二叉树
	Level(t);
	return 0;
}