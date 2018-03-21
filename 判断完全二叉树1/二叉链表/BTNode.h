#pragma once
#include<vector>
#include<queue>
using namespace std;
template<typename T>
struct BTNode     //Binary Tree Node
{
	T data;
	BTNode *left, *right;      //ָ��ڵ����Һ��ӵ�ָ��
	BTNode(const T& item = T(), BTNode * lptr = NULL, BTNode * rptr = NULL) :data(item), left(lptr), right(rptr) {}
};
template<typename T>
BTNode<T> * GetBTNode(const T& item, BTNode<T> *lp = NULL, BTNode<T> *rp = NULL)
{
	BTNode<T> *p;
	p = new BTNode<T>(item, lp, rp);
	if (p == NULL)
	{
		cout << "Memory allocation failure!" << endl;
		exit(1);
	}
	return(p);
}
template<typename T>
void Level(const BTNode<T>* t) {
	if (t == NULL)
		return;
	queue<const BTNode<T>* >Q;
	cout << t->data;
	Q.push(t);
	while (!Q.empty()) {
		t = Q.front();
		Q.pop();
		if (t->left) {
			cout << t->left->data;
			Q.push(t->left);
		}
		if (t->right) {
			cout << t->right->data;
			Q.push(t->right);
		}

	}
}
template<typename T>
BTNode<T> * MakeLined(const vector<T>& L) {
	if (L.size() == 0)
		return NULL;
	queue<BTNode<T>* > Q;
	BTNode<T> *t = GetBTNode(L[0]);
	BTNode<T> *parent, *child;
	Q.push(t);
	int i = 0, n = L.size();
	while (!Q.empty()) {
		parent = Q.front();Q.pop();
			
		if (2 * i + 1 < n && L[2 * i + 1] != T()) {    //���Ӵ���
			child = GetBTNode(L[2 * i + 1]);        //��������
			parent->left = child;
			Q.push(child);
		}
		if (2 * i + 2 < n&&L[2 * i + 2] != T()) {     //���Ӵ���
			child = GetBTNode(L[2 * i + 2]);   //�����Һ���
			parent->right = child;
			Q.push(child);
		}
		i++;
		while (i < n&&L[i] == T())           //i�Ƿ�0Ԫ�ص��±�
			i++;
	}
	return (t);
}