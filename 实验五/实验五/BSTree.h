#pragma once
#include<queue>
#include<stack>
#include<iostream>
using namespace std;
template<typename T>
class BSTree {
private:
	struct BTNode {   //�ڵ�ṹ
		T data;
		BTNode * left, *right;
		BTNode(const T& item, BTNode * lptr = NULL, BTNode * rptr = NULL) :data(item), left(lptr), right(rptr) {}
	};
	//struct ThBTNode {   //�ڵ�ṹ
	//	T data;
	//	ThBTNode * left, *right, *ltag, *rtag;
	//	ThBTNode(const T& item, BTNode * lptr = NULL, BTNode * rptr = NULL, BTNode * ltag = 1, BTNode* rtag = 1) :data(item), left(lptr), right(rptr), ltag(ltag), rtag(rtag) {}
	//};
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
	BTNode* root;      //��ָ��
	int size;          //�ڵ����
	void Insert(const T& x, BTNode* & t);    //����Ԫ��
	void Remove(const T& x, BTNode* & t);    //ɾ��Ԫ��
	BTNode* FindMin(BTNode *t)const;       //������СԪ�صĽڵ�ָ��
	BTNode* FindMax(BTNode *t)const;       //�������Ԫ�صĽڵ�ָ��
	BTNode* FindNode(const T&x, BTNode *t)const;//����ĳһԪ�صĽڵ�ָ��
	void Clear(BTNode * &t);                   //��ն�������Ľڵ�
	void PrintBTree(const BTNode * t, int screenwidth)const; //��ֱ�������������
public:
	class const_iterator {
	protected:
		BTNode * current;
		T & retrieve()const { return(current->data); }
		const_iterator(BTNode* t) { current = GoFarLeft(t); } //���캯��
		stack<BTNode* > St;     //����ջ
		BTNode* GoFarLeft(BTNode *t) {
			if (!t)
				return NULL;
			while (t->left) {
				St.push(t); t = t->left;
			}
			return t;
		}
		//BTNode* GoFarLeft(BTNode *t) {  //��������
		//	if (t == NULL)
		//		return NULL;
		//	while (t->ltag == 0)
		//		t = t->left;
		//	return t;
		//}
		friend class BSTree<T>;
	public:
		const_iterator() :current(NULL) {}
		const T&operator* ()const { return(retrieve()); }
		const_iterator& operator++() {     //����ջ
			if (current->right)
				current = GoFarLeft(current->right);
			else if (!St.empty()) {
				current = St.top(); St.pop();
			}				
			else
				current = NULL;
			return *this;
		}
		/*const_iterator& operator++(void) 
		{
			if (current->rtag == 0)
				current = GoFarLeft(current->right);
			else
				current = current->right;
			return *this;
		}*/

		bool operator==(const_iterator& rhs)const { return (current == rhs.current); }
		bool operator!=(const_iterator& rhs)const { return (current != rhs.current); }
	};
	class iterator :public const_iterator {
	protected:
		iterator(BTNode* t) :const_iterator(t){}
		friend class BSTree<T>;
	public:
		iterator() {}
		T & operator*() { return(retrieve()); }
		const T&operator*()const { return(const_iterator::operator*()); }
		iterator& operator++() 
		{
			if (current->right)
				current = GoFarLeft(current->right);
			else if (!St.empty()) {
				current = St.top(); St.pop();
			}				
			else
				current = NULL;
			return *this;
		}
	};
	const_iterator begin()const { return(const_iterator(root)); }
	const_iterator end() const { return NULL; }
	iterator begin() { return(iterator(root)); }
	iterator end() { return NULL; }
	BSTree() :root(NULL), size(0) {};
	~BSTree() { Clear(); }
	T & FindMin() { return (FindMine(root)->data); } //������СԪ��
	T & FindMax() { return (FindMax(root)->data); }  //�������Ԫ��
	bool Find(const T &x)const { return (FindNode(x, root) != NULL); }  //����
	bool Find(T & x)const;       //���Ҳ���ȡ
	bool Empty()const { return (size == 0); }   //�п�
	int Size() { return size; }            //Ԫ�ظ���
	void Clear() { Clear(root); }       //���
	void Update(const T& x);            //�޸�
	void Insert(const T& x) { Insert(x, root); }     //����
	void Remove(const T& x) { Remove(x, root); }    //ɾ��
	void PrintBTree(int w)const { PrintBTree(root, w); }  //��ֱ�������������
};

//��ֱ���������
template<typename T>
void BSTree<T>::PrintBTree(const BTNode *t, int screenwidth) const {
	if (t == NULL)
		return;
	int level = 0, offset = screenwidth / 2;      //��0�㿪ʼ,����������Ļ��ȵ�һ��
	Location floc, cloc;                    //��¼���Ӻ�˫�׵Ľڵ�����λ�õı���
	queue<const BTNode *>Q;             //��ȡ�ڵ�ָ��Ķ���
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
template <typename T>
typename BSTree<T>::BTNode* BSTree<T>::FindMin(BTNode* t)const {  //˽�з���,������СԪ�صĽڵ�ָ��
	if (t != NULL)
		while (t->left != NULL)
			t = t->left;
	return t;
}
template <typename T>
typename BSTree<T>::BTNode* BSTree<T>::FindMax(BTNode* t)const {  //˽�з���,������daԪ�صĽڵ�ָ��
	if (t != NULL)
		while (t->right != NULL)
			t = t->right;
	return t;
}
template <typename T>
typename BSTree<T>::BTNode* BSTree<T>::FindNode(const T&x, BTNode* t)const {  //˽�з���,����ĳԪ�صĽڵ�ָ��
	if (t == NULL)
		return NULL;
	while (t)
		if (x < t->data)           //�������С������߱Ƚ�,������ұ߱Ƚ�
			t = t->left;
		else if (x > t->data)
			t = t->right;
		else
			return t;
	return NULL;
}
template<typename T>
void BSTree<T>::Clear(BTNode* &t) {  //˽�з���.
	if (t == NULL)
		return;
	Clear(t->left);
	Clear(t->right);
	delete t;
	t = NULL;
}
template<typename T>
bool BSTree<T>::Find(T& x)const {   //���з���.���Ҳ���ȡ
	BTNode * p = FindNode(x, root);
	if (p) {
		x = p->data; return 1;
	}
	return 0;
}
template<typename T>
void BSTree<T>::Update(const T& x) { //���з���.�޸�
	BTNode * p = FindNode(x, root);
	if (p)
		p->data = x;
	else
		Insert(x);
}
template<typename T>
void BSTree<T>::Insert(const T& x, BTNode* & t) { //˽�з���,����
	if (t == NULL) {
		t = new BTNode(x); size++;
	}
	else if (x < t->data)
		Insert(x, t->left);//�ݹ�
	else if (x > t->data)
		Insert(x, t->right);
}
template<typename T>
void BSTree<T>::Remove(const T& x, BTNode * &t) {  //˽�з���,ɾ��
	if (t == NULL)
		return;
	if (x < t->data)
		Remove(x, t->left);
	else if (x > t->data)
		Remove(x, t->right);
	else if (t->left != NULL && t->right != NULL) {
		t->data = FindMin(t->right)->data;
		Remove(t->data, t->right);
	}
	else {
		BTNode * old = t;
		t = (t->left != NULL) ? t->left : t->right;
		delete old; size--;
	}
}