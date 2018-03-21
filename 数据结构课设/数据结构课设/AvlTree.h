#pragma once
#include<string.h>
#include<queue>
#include<fstream>
template<typename T>
class AvlTree 
{
private:
	struct StringCount
	{
		T data;      //单词
		int num;   //单词出现的次数
		int height;
		StringCount *left, *right;
		StringCount(const T& item, int n = 1, StringCount * lptr = NULL, StringCount * rptr = NULL,  int h = 0) :data(item), num(n), left(lptr), right(rptr), height(h) {}
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
		StringCount* root;
		int size;
		int Height(StringCount* t)const { return(t == NULL ? -1 : t->height); }
		int Num(StringCount* t)const { return(t == NULL ? 0 : t->num); }
		void PrintAvlTree(const StringCount* t, int screenwidth)const;
		int Max(int x1, int x2) { return x1 < x2 ? x2 : x1; }
		void RLR(StringCount* &t);
		void RR(StringCount* &t);     //右单旋转
		void RL(StringCount* &t);     //左单旋转
		void RRL(StringCount* &t);
	    void Clear(StringCount* &t);

		void Insert(const T& x,int s,StringCount* &t);  //插入
		void Update(StringCount* &s);  //更新
		StringCount* FindNode(const T& x, StringCount* s)const;    //在单词表(数组)中查找该单词是否存在	,存在就返回该节点
	public:
		AvlTree(int n=500) :root(NULL), size(0) { /*word = new T[n]; num = new int[50]; */}
		~AvlTree() { Clear(root); }
		bool Empty()const { return size == 0; }
		int Size()const { return size; }
		void Clear(void) { Clear(root); size = 0; }
		void PrintAvlTree(int screenwidth)const { PrintAvlTree(root, screenwidth); }
	
		void Insert(const T& x) { Insert(x,1,root); }
		bool FindNode(const T& x) const{ return(FindNode(x, root) != NULL); }
		void ReadTxt(const char *filename);
};
    template<typename T>
typename AvlTree<T>::StringCount*  AvlTree<T>::FindNode(const T& x,StringCount* s)const {     ////查找该单词
		if (s == NULL)
			return NULL;
		while (s) 
		{
			if (strcmp(x,s->data)==0)
				return s;
			else {
				FindNode(x, s->left);
				FindNode(x, s->right);
			}
		}
		return NULL;      //未找到,即Insert
	}
	//template<typename T>     //更新t为FindNode的返回值
	//void AvlTree<T>::Update(StringCount* &t)
	//{
	//	if (t == NULL)
	//		return;
	//	(t->num)++;
	//	if (t->righgt) {
	//		if (t->num > t->right->num) {
	//			StringCount* temp = t;
	//			t = t->right;
	//			t->right = t;
	//		}
	//	}	
	//}
	//template<typename T>
	//void AvlTree<T>::Get(StringCount* &t) {
	//	if (t == NULL)
	//		return;
	//	(t->num)++;

	//}
	template<typename T>
	void AvlTree<T>::PrintAvlTree(const StringCount *t, int screenwidth) const {
		if (t == NULL)
			return;
		int level = 0, offset = screenwidth / 2;      //从0层开始,缩进量是屏幕宽度的一半
		Location floc, cloc;                    //记录孩子和双亲的节点的输出位置的变量
		queue<const StringCount *>Q;             //存取节点指针的队列
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
	void AvlTree<T>::Clear(StringCount* &t) {  //私有方法.
		if (t == NULL)
			return;
		Clear(t->left);
		Clear(t->right);
		delete t;
		t = NULL;
	}
	template<typename T>
	void AvlTree<T>::RL(StringCount* &t) {   //左单旋转
		StringCount* c = t->right;
		t->right = c->left;
		c->left = t;
		t->height = Max(Height(t->right), Height(t->left)) + 1;
		c->height = Max(Height(c->right), t->height) + 1;
		t = c;
	}
	template<typename T>
	void AvlTree<T>::RR(StringCount* &t) {    //右单旋转    
		StringCount* c = t->left;
		t->left = c->right;
		c->right = t;
		t->height = Max(Height(t->left), Height(t->right)) + 1;
		c->height = Max(Height(c->right), t->height) + 1;
		t = c;
	}
	template<typename T>
	void AvlTree<T>::RLR(StringCount* &t) {    //先左后右
		RL(t->left);
		RR(t);
	}
	template<typename T>
	void AvlTree<T>::RRL(StringCount* &t) {    //先右后左
		RR(t->right);
		RL(t);
	}
	template<typename T>
	void AvlTree<T>::Insert(const T& x, int s, StringCount* &t) {		 
		if (t == NULL)
		{
			t = new StringCount(x,s);
			size++;
		}
		else if (s <=t->num)
		{
			Insert(x, s,t->left);
			if (Height(t->left) - Height(t->right) == 2)
				if (s <=t->left->num)
					RR(t);
				else
					RLR(t);
		}
		else if (s >t->num) 
		{
			Insert(x,s,t->right);
			if (Height(t->right) - Height(t->left) == 2)
				if (t->right->num < s)
					RL(t);
				else
					RRL(t);
		}		
		t->height = Max(Height(t->left), Height(t->right)) + 1;
	}
	template<typename T>
	void AvlTree<T>::ReadTxt(const char *filename) 
	{
		ifstream fin;
		fin.open(filename, ios::in | ios::_Nocreate);
		if (!fin) {
			cout << "cannot open this txt" << endl;
			exit(1);
		}
	}
	