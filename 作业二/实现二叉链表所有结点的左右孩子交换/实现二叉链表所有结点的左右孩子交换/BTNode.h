#pragma once
#include<queue>
template<typename T>
struct BTNode
{
	T data;
	BTNode *left, *right;
	BTNode(const T& item = T(), BTNode* lptr = NULL, BTNode* rptr = NULL) :data(item), left(lptr), right(rptr) {}
	void swap_child()
	{
		BTNode * temp = left;
		left = right;
		right = temp;
	}
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
void Level(const BTNode<T>* t)
{
	if (t == NULL)
		return;
	queue<const BTNode<T>*> Q;
	Q.push(t);
	while (!Q.empty())
	{
		t = Q.front();
		Q.pop();
		cout << t->data;
		if (t->left)
			Q.push(t->left);
		if (t->right)
			Q.push(t->right);
	}
}
template<typename T>
void Swap_child(BTNode<T>* t)
{
	if (t == NULL)
		return;
	queue<BTNode<T>*> Q;
	Q.push(t);
	while (!Q.empty())
	{
		t = Q.front();
		Q.pop();
		t->swap_child();
		if (t->left)
			Q.push(t->left);
		if (t->right)
			Q.push(t->right);
	}
}