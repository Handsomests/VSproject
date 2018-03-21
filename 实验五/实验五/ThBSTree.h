#pragma once
#include<queue>
#include<iostream>
using namespace std;
template<typename T>
class ThBSTree {
private:
	
	struct ThBTNode {   //节点结构
		T data;
		ThBTNode * left, *right, *ltag, *rtag;
		ThBTNode(const T& item, ThBTNode * lptr = NULL, ThBTNode * rptr = NULL, ThBTNode * ltag = 1, ThBTNode* rtag = 1) :data(item), left(lptr), right(rptr), ltag(ltag), rtag(rtag) {}
	};
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
	ThBTNode* root;      //根指针
	int size;          //节点个数
	void Clear(ThBTNode * &t);                   //情空二叉链表的节点
	void PrintBTree(const ThBTNode * t, int screenwidth)const; //垂直输出二叉搜索树
	void CreateTree(ThBTNode * t);               //创建树
public:
	class const_iterator {
	protected:
		ThBTNode * current;
		T & retrieve()const { return(current->data); }
		const_iterator(ThBTNode* t) { current = GoFarLeft(t); } //构造函数
		
		ThBTNode* GoFarLeft(ThBTNode *t) {  //基于线索
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
		
		const_iterator& operator++(void)   //基于线索
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
			const_iterator& operator++(void)   //基于线索
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
	bool Find(const T &x)const { return (FindNode(x, root) != NULL); }  //查找
	bool Empty()const { return (size == 0); }   //判空
	int Size() { return size; }            //元素个数
	void PrintBTree(int w)const { PrintBTree(root, w); }  //垂直输出二叉搜索树
};

//垂直输出二叉树
template<typename T>
void ThBSTree<T>::PrintBTree(const ThBTNode *t, int screenwidth) const {
	if (t == NULL)
		return;
	int level = 0, offset = screenwidth / 2;      //从0层开始,缩进量是屏幕宽度的一半
	Location floc, cloc;                    //记录孩子和双亲的节点的输出位置的变量
	queue<const ThBTNode *>Q;             //存取节点指针的队列
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
template<typename T>
void ThBSTree<T>::Clear(ThBTNode* &t) {  //私有方法.
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
	cout << "请输入节点值" << endl;
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