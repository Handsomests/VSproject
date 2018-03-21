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
		T data;      //����
		int num;   //���ʳ��ֵĴ���
		int height;
		StringCount *left, *right;
		StringCount(const T& item, int n = 1, StringCount * lptr = NULL, StringCount * rptr = NULL,  int h = 0) :data(item), num(n), left(lptr), right(rptr), height(h) {}
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
		StringCount* root;
		int size;
		int Height(StringCount* t)const { return(t == NULL ? -1 : t->height); }
		int Num(StringCount* t)const { return(t == NULL ? 0 : t->num); }
		void PrintAvlTree(const StringCount* t, int screenwidth)const;
		int Max(int x1, int x2) { return x1 < x2 ? x2 : x1; }
		void RLR(StringCount* &t);
		void RR(StringCount* &t);     //�ҵ���ת
		void RL(StringCount* &t);     //����ת
		void RRL(StringCount* &t);
	    void Clear(StringCount* &t);

		void Insert(const T& x,int s,StringCount* &t);  //����
		void Update(StringCount* &s);  //����
		StringCount* FindNode(const T& x, StringCount* s)const;    //�ڵ��ʱ�(����)�в��Ҹõ����Ƿ����	,���ھͷ��ظýڵ�
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
typename AvlTree<T>::StringCount*  AvlTree<T>::FindNode(const T& x,StringCount* s)const {     ////���Ҹõ���
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
		return NULL;      //δ�ҵ�,��Insert
	}
	//template<typename T>     //����tΪFindNode�ķ���ֵ
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
		int level = 0, offset = screenwidth / 2;      //��0�㿪ʼ,����������Ļ��ȵ�һ��
		Location floc, cloc;                    //��¼���Ӻ�˫�׵Ľڵ�����λ�õı���
		queue<const StringCount *>Q;             //��ȡ�ڵ�ָ��Ķ���
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
	void AvlTree<T>::Clear(StringCount* &t) {  //˽�з���.
		if (t == NULL)
			return;
		Clear(t->left);
		Clear(t->right);
		delete t;
		t = NULL;
	}
	template<typename T>
	void AvlTree<T>::RL(StringCount* &t) {   //����ת
		StringCount* c = t->right;
		t->right = c->left;
		c->left = t;
		t->height = Max(Height(t->right), Height(t->left)) + 1;
		c->height = Max(Height(c->right), t->height) + 1;
		t = c;
	}
	template<typename T>
	void AvlTree<T>::RR(StringCount* &t) {    //�ҵ���ת    
		StringCount* c = t->left;
		t->left = c->right;
		c->right = t;
		t->height = Max(Height(t->left), Height(t->right)) + 1;
		c->height = Max(Height(c->right), t->height) + 1;
		t = c;
	}
	template<typename T>
	void AvlTree<T>::RLR(StringCount* &t) {    //�������
		RL(t->left);
		RR(t);
	}
	template<typename T>
	void AvlTree<T>::RRL(StringCount* &t) {    //���Һ���
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
	