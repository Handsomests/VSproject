#pragma once
#include"BTNode.h"
#include"BTNodeLib.h"
#include"Heap.h"

template<typename T>
struct HufmNode {
	BTNode<T>* t;
	int operator<(const HufmNode & h) { return (t->data < h.t->data); }
	int operator<=(const HufmNode & h) { return (t->data <= h.t->data); }
};
template<typename T>
BTNode<T>* MakeHufm(const T* pa, int n) {
	HufmNode<T> hf;
	Heap<HufmNode<T> > H(n);   //zh注意〉〉之间要有空格
	BTNode<T> *t, *left, *right;
	for (int i = 0; i < n; i++) {
		t = GetBTNode(pa[i]);
		hf.t = t;
		H.Insert(hf);
	}
	for (int i = 1; i < n; i++) {
		H.DeleteMin(hf);
		left = hf.t;
		H.DeleteMin(hf);
		right = hf.t;
		t = GetBTNode(left->data + right->data, left, right);
		hf.t = t;
		H.Insert(hf);
	}
	H.DeleteMin(hf);
	t = hf.t;
	return(t);
}
//利用前序遍历递归方法求出叶子节点
template<typename T>
void Allcode(BTNode<T>*&b, int code[], int pathlen)
{
	if (b != NULL)
	{
		if (b->left == NULL && b->right == NULL)//*b为叶子结点
		{
			for (int i = 1; i <= pathlen; i++)
				b->code.Push_back(code[i]);
		}
		else
		{
			pathlen++;
			if (b->left)
			{
				code[pathlen] = 0;
				Allcode(b->left, code, pathlen);   //递归扫描左子树
			}
			if (b->right)
			{
				code[pathlen] = 1;
				Allcode(b->right, code, pathlen);   //递归扫描右子树
			}
			pathlen - -;
		}
	}
}
