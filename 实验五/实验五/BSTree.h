#pragma once
#include<queue>
#include<stack>
#include<iostream>
using namespace std;
template<typename T>
class BSTree {
private:
	struct BTNode {   //节点结构
		T data;
		BTNode * left, *right;
		BTNode(const T& item, BTNode * lptr = NULL, BTNode * rptr = NULL) :data(item), left(lptr), right(rptr) {}
	};
	//struct ThBTNode {   //节点结构
	//	T data;
	//	ThBTNode * left, *right, *ltag, *rtag;
	//	ThBTNode(const T& item, BTNode * lptr = NULL, BTNode * rptr = NULL, BTNode * ltag = 1, BTNode* rtag = 1) :data(item), left(lptr), right(rptr), ltag(ltag), rtag(rtag) {}
	//};
	struct Location {
		int xindent, ylevel;     // 节点坐标的位置
	};
	void Gotxy(int x, int y)const {
		static int level = 0, indent = 0;
		if (y == 0) {            //重新输出二叉树要重新赋值
			indent = 0; level = 0;
		}
		if (level != y) {//若层数增加,则缩进量从0开始
			cout << endl;
			indent = 0; level++;
		}
		cout.width(x - indent);   //根据已有缩进量确定当前缩进量
		indent = x;           //记录当前的缩进量
	}
	BTNode* root;      //根指针
	int size;          //节点个数
	void Insert(const T& x, BTNode* & t);    //插入元素
	void Remove(const T& x, BTNode* & t);    //删除元素
	BTNode* FindMin(BTNode *t)const;       //返回最小元素的节点指针
	BTNode* FindMax(BTNode *t)const;       //返回最大元素的节点指针
	BTNode* FindNode(const T&x, BTNode *t)const;//返回某一元素的节点指针
	void Clear(BTNode * &t);                   //情空二叉链表的节点
	void PrintBTree(const BTNode * t, int screenwidth)const; //垂直输出二叉搜索树
public:
	class const_iterator {
	protected:
		BTNode * current;
		T & retrieve()const { return(current->data); }
		const_iterator(BTNode* t) { current = GoFarLeft(t); } //构造函数
		stack<BTNode* > St;     //基于栈
		BTNode* GoFarLeft(BTNode *t) {
			if (!t)
				return NULL;
			while (t->left) {
				St.push(t); t = t->left;
			}
			return t;
		}
		//BTNode* GoFarLeft(BTNode *t) {  //基于线索
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
		const_iterator& operator++() {     //基于栈
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
	T & FindMin() { return (FindMine(root)->data); } //返回最小元素
	T & FindMax() { return (FindMax(root)->data); }  //返回最大元素
	bool Find(const T &x)const { return (FindNode(x, root) != NULL); }  //查找
	bool Find(T & x)const;       //查找并提取
	bool Empty()const { return (size == 0); }   //判空
	int Size() { return size; }            //元素个数
	void Clear() { Clear(root); }       //清空
	void Update(const T& x);            //修改
	void Insert(const T& x) { Insert(x, root); }     //插入
	void Remove(const T& x) { Remove(x, root); }    //删除
	void PrintBTree(int w)const { PrintBTree(root, w); }  //垂直输出二叉搜索树
};

//垂直输出二叉树
template<typename T>
void BSTree<T>::PrintBTree(const BTNode *t, int screenwidth) const {
	if (t == NULL)
		return;
	int level = 0, offset = screenwidth / 2;      //从0层开始,缩进量是屏幕宽度的一半
	Location floc, cloc;                    //记录孩子和双亲的节点的输出位置的变量
	queue<const BTNode *>Q;             //存取节点指针的队列
	queue<Location> LQ;                  //存取结点输出位置的队列
	floc.xindent = offset;              //存取结点的输出位置
	floc.ylevel = level;
	Q.push(t);                    //根指针入队列
	LQ.push(floc);                //根结点位置数据入队
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
typename BSTree<T>::BTNode* BSTree<T>::FindMin(BTNode* t)const {  //私有方法,返回最小元素的节点指针
	if (t != NULL)
		while (t->left != NULL)
			t = t->left;
	return t;
}
template <typename T>
typename BSTree<T>::BTNode* BSTree<T>::FindMax(BTNode* t)const {  //私有方法,返回最da元素的节点指针
	if (t != NULL)
		while (t->right != NULL)
			t = t->right;
	return t;
}
template <typename T>
typename BSTree<T>::BTNode* BSTree<T>::FindNode(const T&x, BTNode* t)const {  //私有方法,返回某元素的节点指针
	if (t == NULL)
		return NULL;
	while (t)
		if (x < t->data)           //比这个数小就往左边比较,大就往右边比较
			t = t->left;
		else if (x > t->data)
			t = t->right;
		else
			return t;
	return NULL;
}
template<typename T>
void BSTree<T>::Clear(BTNode* &t) {  //私有方法.
	if (t == NULL)
		return;
	Clear(t->left);
	Clear(t->right);
	delete t;
	t = NULL;
}
template<typename T>
bool BSTree<T>::Find(T& x)const {   //共有方法.查找并提取
	BTNode * p = FindNode(x, root);
	if (p) {
		x = p->data; return 1;
	}
	return 0;
}
template<typename T>
void BSTree<T>::Update(const T& x) { //共有方法.修改
	BTNode * p = FindNode(x, root);
	if (p)
		p->data = x;
	else
		Insert(x);
}
template<typename T>
void BSTree<T>::Insert(const T& x, BTNode* & t) { //私有方法,插入
	if (t == NULL) {
		t = new BTNode(x); size++;
	}
	else if (x < t->data)
		Insert(x, t->left);//递归
	else if (x > t->data)
		Insert(x, t->right);
}
template<typename T>
void BSTree<T>::Remove(const T& x, BTNode * &t) {  //私有方法,删除
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