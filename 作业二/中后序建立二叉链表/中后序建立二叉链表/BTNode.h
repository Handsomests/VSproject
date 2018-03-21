#pragma once
#include<vector>
#include<queue>
#include<stack>
#include<iostream>
using namespace std;
template<typename T>
struct BTNode     //Binary Tree Node
{
	T data;
	BTNode *left, *right;      //指向节点左右孩子的指针
	BTNode(const T& item = T(), BTNode * lptr = NULL, BTNode * rptr = NULL) :data(item), left(lptr), right(rptr) {}
};
template<typename T>
BTNode<T> * GetBTNode(const T& item, BTNode<T> *lp = NULL, BTNode<T> *rp = NULL)   //创建节点
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
BTNode<T> *HZMakeLined(const T* pL, const T* iL, int size) {
	if (size <= 0)
		return (NULL);
	BTNode<T> *t, *left, *right;
	const T*rL; int k;
	for (rL = iL; rL<iL + size; rL++)
		if (*rL == *(pL + size - 1))
			break;
	k = rL - iL;
	left = HZMakeLined(pL, iL, k);
	right = HZMakeLined(pL + k, iL + k + 1, size - k - 1);
	t = GetBTNode(*(pL + size - 1), left, right);
	return t;
}