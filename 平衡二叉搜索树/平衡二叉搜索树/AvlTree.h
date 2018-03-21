#pragma once
#include<queue>
#include<stack>
#include<stdio.h>
#include<iostream>
using namespace std;

template<typename T>
class AvlTree 
{
private:
	struct AvlNode
	{
		T data;
		AvlNode * left, *right;
		int height;           //��¼�������ĸ߶�
		AvlNode(const T& item, AvlNode * lptr = 0, AvlNode * rptr = 0, int h = 0):data(item), left(lptr), right(rptr), height(h) {}
	};
	struct Location {
		int xindent, ylevel;     // �ڵ������λ��
	};
	void Gotxy(int x, int y)const {
		static int level = 0, indent = 0;
		if (y == 0) {            //�������������Ҫ���¸�ֵ
			indent = 0; level = 0;
		}
		if (level != y) {//����������,����������0��ʼ
			cout << endl;
			indent = 0; level++;
		}
		cout.width(x - indent);   //��������������ȷ����ǰ������
		indent = x;           //��¼��ǰ��������
	}
	AvlNode* root;
	int size;
	int Height(AvlNode* t)const { return(t == NULL ? -1 : t->height); }
	void Insert(const T& x, AvlNode* &t);

	int Max(int x1, int x2) { return x1 < x2 ? x2 : x1; }
	void RLR(AvlNode* &t);
	void RR(AvlNode* &t);     //�ҵ���ת
	void RL(AvlNode* &t);     //����ת
	void RRL(AvlNode* &t);

	void Clear(AvlNode* &t);
	void PrintAvlTree(const AvlNode* t, int screenwidth)const;
public:
	AvlTree(void) :root(NULL), size(0) {};
	~AvlTree(void) { Clear(root); }
	bool Empty()const { return size == 0; }
	int Size()const { return size; }
	void Clear(void) { Clear(root); size = 0; }
	void Insert(const T& x) { Insert(x, root); }
	void PrintAvlTree(int screenwidth)const { PrintAvlTree(root, screenwidth); }
};
template<typename T>
void AvlTree<T>::Clear(AvlNode* &t) {  //˽�з���.
	if (t == NULL)
		return;
	Clear(t->left);
	Clear(t->right);
	delete t;
	t = NULL;
}
template<typename T>
void AvlTree<T>::PrintAvlTree(const AvlNode *t, int screenwidth) const {
	if (t == NULL)
		return;
	int level = 0, offset = screenwidth / 2;      //��0�㿪ʼ,����������Ļ��ȵ�һ��
	Location floc, cloc;                    //��¼���Ӻ�˫�׵Ľڵ�����λ�õı���
	queue<const AvlNode *>Q;             //��ȡ�ڵ�ָ��Ķ���
	queue<Location> LQ;                  //��ȡ������λ�õĶ���
	floc.xindent = offset;              //��ȡ�������λ��
	floc.ylevel = level;
	Q.push(t);                    //��ָ�������
	LQ.push(floc);                //�����λ���������
	while (!Q.empty()) {
		t = Q.front(); Q.pop();
		floc = LQ.front(); LQ.pop();
		Gotxy(floc.xindent, floc.ylevel);
		cout << t->data;
		if (floc.ylevel != level) {
			level++; offset = offset / 2;
		}
		if (t->left) {
			Q.push(t->left);
			cloc.ylevel = floc.ylevel + 1;
			cloc.xindent = floc.xindent - offset / 2;
			LQ.push(cloc);
		}
		if (t->right) {
			Q.push(t->right);
			cloc.ylevel = floc.ylevel + 1;
			cloc.xindent = floc.xindent + offset / 2;
			LQ.push(cloc);
		}
	}
	cout << endl;
}
template<typename T>
void AvlTree<T>::RL(AvlNode* &t) {   //����ת
	AvlNode* c = t->right;
	t->right = c->left;
	c->left = t;
	t->height = Max(Height(t->right), Height(t->left)) + 1;
	c->height = Max(Height(c->right), t->height) + 1;
	t = c;
}
template<typename T>
void AvlTree<T>::RR(AvlNode* &t) {    //�ҵ���ת    
	AvlNode* c = t->left;
	t->left = c->right;
	c->right = t;
	t->height = Max(Height(t->left), Height(t->right)) + 1;
	c->height = Max(Height(c ->right), t->height) + 1;
	t = c;
}
template<typename T>
void AvlTree<T>::RLR(AvlNode* &t) {    //�������
	RL(t->left);
	RR(t);
}
template<typename T>
void AvlTree<T>::RRL(AvlNode* &t) {    //���Һ���
	RR(t->right);
	RL(t);
}
template<typename T>
void AvlTree<T>::Insert(const T& x, AvlNode* &t) {
	if (t == NULL)
	{
		t = new AvlNode(x);
		size++;
	}
	else if (x < t->data)
	{
		Insert(x, t->left);
		if (Height(t->left) - Height(t->right) == 2)
			if (x < t->left->data)
				RR(t);
			else
				RLR(t);
	}
	else if (x > t->data) {
		Insert(x, t->right);
		if (Height(t->right) - Height(t->left) == 2)
			if (t->right->data < x)
				RL(t);
			else
				RRL(t);
	}
	t->height = Max(Height(t->left), Height(t->right)) + 1;
}