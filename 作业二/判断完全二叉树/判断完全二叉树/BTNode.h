#pragma once
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