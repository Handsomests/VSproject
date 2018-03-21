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
	Heap<HufmNode<T> > H(n);   //zhע�⡵��֮��Ҫ�пո�
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
//����ǰ������ݹ鷽�����Ҷ�ӽڵ�
template<typename T>
void Allcode(BTNode<T>*&b, int code[], int pathlen)
{
	if (b != NULL)
	{
		if (b->left == NULL && b->right == NULL)//*bΪҶ�ӽ��
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
				Allcode(b->left, code, pathlen);   //�ݹ�ɨ��������
			}
			if (b->right)
			{
				code[pathlen] = 1;
				Allcode(b->right, code, pathlen);   //�ݹ�ɨ��������
			}
			pathlen - -;
		}
	}
}
