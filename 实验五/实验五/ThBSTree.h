#pragma once
#include<queue>
#include<iostream>
using namespace std;
template<typename T>
class ThBSTree {
private:
	
	struct ThBTNode {   //�ڵ�ṹ
		T data;
		ThBTNode * left, *right, *ltag, *rtag;
		ThBTNode(const T& item, ThBTNode * lptr = NULL, ThBTNode * rptr = NULL, ThBTNode * ltag = 1, ThBTNode* rtag = 1) :data(item), left(lptr), right(rptr), ltag(ltag), rtag(rtag) {}
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
	ThBTNode* root;      //��ָ��
	int size;          //�ڵ����
	void Clear(ThBTNode * &t);                   //��ն�������Ľڵ�
	void PrintBTree(const ThBTNode * t, int screenwidth)const; //��ֱ�������������
	void CreateTree(ThBTNode * t);               //������
public:
	class const_iterator {
	protected:
		ThBTNode * current;
		T & retrieve()const { return(current->data); }
		const_iterator(ThBTNode* t) { current = GoFarLeft(t); } //���캯��
		
		ThBTNode* GoFarLeft(ThBTNode *t) {  //��������
			if (t == NULL)
				return NULL;
			while (t->ltag == 0)
				t = t->left;
			return t;
		}
		friend class ThBSTree<T>;
	public:
		const_iterator() :current(NULL) {}
		const T&operator* ()const { return(retrieve()); }
		
		const_iterator& operator++(void)   //��������
		{
		if (current->rtag == 0)
		current = GoFarLeft(current->right);
		else
		current = current->right;
		return *this;
		}

		bool operator==(const_iterator& rhs)const { return (current == rhs.current); }
		bool operator!=(const_iterator& rhs)const { return (current != rhs.current); }
	};
	class iterator :public const_iterator {
	protected:
		iterator(ThBTNode* t) :const_iterator(t) {}
		friend class ThBSTree<T>;
	public:
		iterator() {}
		T & operator*() { return(retrieve()); }
		const T&operator*()const { return(const_iterator::operator*()); }
		iterator& operator++()
		{
			const_iterator& operator++(void)   //��������
			{
				if (current->rtag == 0)
					current = GoFarLeft(current->right);
				else
					current = current->right;
				return *this;
			}
		}
	};
	const_iterator begin()const { return(const_iterator(root)); }
	const_iterator end() const { return NULL; }
	iterator begin() { return(iterator(root)); }
	iterator end() { return NULL; }
	ThBSTree() :root(NULL), size(0) {};
	~ThBSTree() { Clear(); }
	bool Find(const T &x)const { return (FindNode(x, root) != NULL); }  //����
	bool Empty()const { return (size == 0); }   //�п�
	int Size() { return size; }            //Ԫ�ظ���
	void PrintBTree(int w)const { PrintBTree(root, w); }  //��ֱ�������������
};

//��ֱ���������
template<typename T>
void ThBSTree<T>::PrintBTree(const ThBTNode *t, int screenwidth) const {
	if (t == NULL)
		return;
	int level = 0, offset = screenwidth / 2;      //��0�㿪ʼ,����������Ļ��ȵ�һ��
	Location floc, cloc;                    //��¼���Ӻ�˫�׵Ľڵ�����λ�õı���
	queue<const ThBTNode *>Q;             //��ȡ�ڵ�ָ��Ķ���
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
void ThBSTree<T>::Clear(ThBTNode* &t) {  //˽�з���.
	if (t == NULL)
		return;
	Clear(t->left);
	Clear(t->right);
	delete t;
	t = NULL;
}
template<typename T>
void ThBSTree<T>::CreateTree(ThBTNode * t) {
	char ch;
	cout << "������ڵ�ֵ" << endl;
	cin << ch;
	if (ch == '#') {
        t = NULL;
	}		
	else {
		t = new ThBSTree(ch);
		CreateTree(t->left);
		if (t->left= NULL) {
			t->right->data = t->data;
		}
		CreateTree(t->right);
	}
	
}