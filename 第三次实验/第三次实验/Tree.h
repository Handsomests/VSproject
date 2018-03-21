#pragma once
#include<list>
#include<queue>
#include<stack>
#include<string>
using namespace std;
template<typename T>
class Tree {
	T * NA;     //节点数组指针
	list<int>* HL;    //孩子链表数组指针
	int root;       //根的下标
	int sizeN, sizeC;   //节点数，孩子节点数
	int maxN;         //节点数组长度即容量
public:
	Tree(int n = 100) :root(-1), sizeN(0), sizeC(0), maxN(n)  //构造函数
	{
		NA = new T[n];
		HL = new list<int>[n];

	}
	~Tree() { delete[]NA; delete[]HL; }   //析构函数
    int Empty()const{return(sizeN==0);}  //判空
	int Full()const { return(sizeN = maxN); }  //判满
	int SizeN()const { return(sizeN); }     //取节点数
	int SizeC()const { return(sizeC); }  //取孩子的下标
	int FindNode(const T& node)const;  //取节点的下标
	bool FindNode(T& node, int pos)const;  //取下标为pos的节点，存储到node中

	bool InsertN(const T& node);         //	插入节点
	bool InsertC(const T& parent, const T& child);   //插入孩子的节点


	void ReadTree(const char* filename);   //从文件读取树的数据
	void WriteTree(const char* filename);  //把树的数据写入到文件

	void BFS(list<T>& L)const;             //广度优先遍历
	void DFS(list<T>& L)const;      //深度优先遍历
	void LFS(list<T>& L)const;      //后根遍历
	void SimLFS(list<T>& L)const;      //后根遍历非递归算法
	//void SimLFS2(list<T>& L)const;     //
	void SimDFS(list<T>& L)const;     //树的深度优先遍历非递归算法	
	template<typename T>
	void DFS(list<T>& L, int t)const {   //先根遍历
		if (t < 0 || t >= sizeN)
			return;
		L.push_back(NA[t]);      //储存节点作为返回值
		list<int>::const_iterator first, last;
		first = HL[t].begin(); last = HL[t].end();
		for (; first != last; ++first)     //扫描孩子节点,寻找兄弟
			DFS(L, *first);
	}
	template<typename T>
	void LFS(list<T>& L, int p)const {   //后根遍历
		if (p < 0 || p >= sizeN)
			return;
		list<int>::const_iterator first, last;
		first = HL[p].begin(); last = HL[p].end();
		for (; first != last; ++first)     //扫描孩子节点,寻找兄弟
			LFS(L, *first);
		L.push_back(NA[p]);
	}
	template<typename T>
	friend ostream& operator<<(ostream& ostr, const Tree<T>& t)
	{
		for (int i = 0; i < t.sizeN; i++)
		{
			ostr << i << '-' << t.NA[i] << ':';
			list<int>::iterator first = t.HL[i].begin(), last = t.HL[i].end();
			for (; first != last; ++first)
				ostr << '(' << *first << ')' << ' ';
			ostr << endl;
		}
		return(ostr);
	}
	template<typename T>
	friend istream& operator >> (istream& istr, Tree<T>& t)
	{
		char str[50];
		int n;
		T parent, child;
		istr >> str >> n;
		istr >> str >> parent;
		t.InsertN(parent);
		t.root = t.sizeN - 1;
		istr >> str;
		for (int i = 1; i <= n - 1; ++i)
		{
			istr >> child;
			t.InsertN(child);

		}
		istr >> str >> n;
		for (int i = 1; i <= n; ++i)
		{
			istr >> parent >> child;
			t.InsertC(parent, child);
		}
		return(istr);
	}
	
};
template<typename T>
void Tree<T>::SimDFS(list<T>& L)const {
	int t = root;
	if (t < 0 || t >= sizeN)
		return;
	stack<int>q;
	if (sizeN <= 0)
		return;
	for (int i = 0; i < sizeN; i++) {
		L.push_back(NA[t]);		
		if (!HL[t].empty()) 
		{
			list<int>::const_iterator first, last;
			first = HL[t].begin(); last = HL[t].end();						
			if (HL[t].size()>=1) {
				for (last--;last!=first;last--)
					q.push(*last);
				t = *first;
			}							
		}
		else{
			if (!q.empty()) {
               t = q.top();q.pop();
			}						
		}
	}
}
template<typename T>
int Tree<T>::FindNode(const T& node)const
{
	for (int i = 0; i < sizeN; i++)
		if (NA[i] == node)
			return(i);
	return(-1);

}
template<typename T>
bool Tree<T>::FindNode(T& node, int pos)const
{
	if (pos < 0 || pos >= sizeN)
		return(0);
	node = NA[pos];
	return(1);
}
template<typename T>
bool Tree<T>::InsertN(const T& node)
{
	if (sizeN == maxN)
		return(0);
	NA[sizeN] = node;
	sizeN++;
	return(1);
}
template<typename T>
bool Tree<T>::InsertC(const T& parent, const T& child)
{
	int pi = FindNode(parent), cj = FindNode(child);
	if (pi == -1 || cj == -1 || pi == cj)
		return(0);
	HL[pi].insert(HL[pi].end(), cj);
	sizeC++;
	return(1);
}              
template<typename T>//从文件中读取树的数据
void  Tree<T>::ReadTree(const char * filename)
{
	Tree<char> T(20);
    ifstream fin;
	fin.open(filename,ios::in | ios::_Nocreate);
	if (!fin) {
		cout << "cannot open " << filename << endl;
		exit(1);
	}	
	fin >>T;
	cout << T;
}
template<typename T>//将树的数据写入到文件当中去
void Tree<T>::WriteTree(const char * filename)
{
	Tree<char> T(20);
	ofstream fout;
	fout.open(filename, ios::out);
	if (!fout) {
		cout << "cannot open " << filename << endl;
		exit(1);
	}
	cin >> T;
	fout << T;
}
template<typename T>       //广度优先遍历
void Tree<T>::BFS(list<T>& L)const {
	if (sizeN == 0)
		return;
	queue<int> Q;
	Q.push(root);          //根下标入队
	list<int>::const_iterator first, last;//孩子链表迭代器
	while (!Q.empty()) {
		int pos = Q.front();               //从队列中去节点的下标
		Q.pop();
		L.push_back(NA[pos]);             //存储节点作为返回值
		first = HL[pos].begin();
		last = HL[pos].end();
		for (; first != last; ++first)          //扫描孩子链表
			Q.push(*first);
	}
}
template<typename T>
void Tree<T>::DFS(list<T>& L)const {
	DFS(L,root);
}
template<typename T>
void Tree<T>::LFS(list<T>& L)const {
	LFS(L, root);
}
//template<typename T>
//void Tree<T>::SimLFS2(list<T>& L)const {
//	int t = root;
//	if (t < 0 || t >= sizeN)
//		return;
//	stack<int>s;
//	int flag = 0,p=0;
//	list<int>::const_iterator first, last;
//	for (int i = 0; i < sizeN; i++) 
//	{			
//		if (!HL[t].empty())
//		{			
//			while(flag>0) 		
//			{
//				L.push_back(NA[t]);
//				flag=0;				
//				t = s.top();												
//			}
//				first = HL[t].begin(); last = HL[t].end();
//				for (last--; last != first; last--)
//				{
//					s.push(*last);
//				}
//				t = *first; s.push(*first);	
//		}
//		else 
//		{
//			if (!s.empty()) {
//				L.push_back(NA[t]); t = s.top(); s.pop(); /*p = s.top();*/flag++;
//			}
//		}
//		
//	}
//	L.push_back(NA[0]);
//}
template<typename T>//后根遍历非递归算法
void Tree<T>::SimLFS(list<T>& L) const
{
	int t = root;
	if (t < 0 || t >= sizeN)
		return;
	stack<int> S, P;
	S.push(t);
	while (!S.empty())
	{
		t = S.top();
		if (!HL[t].empty())
		{
			if (!P.empty())
			{
				if (t == P.top())
				{
					L.push_back(NA[t]);
					S.pop();
					P.pop();
				}
				else
				{
					P.push(t);
					for (list<int>::const_iterator first = HL[t].begin(), last = HL[t].end(); last != first;)
						S.push(*(--last));
				}
			}
			else
			{
				P.push(t);
				for (list<int>::const_iterator first = HL[t].begin(), last = HL[t].end(); last != first;)
					S.push(*(--last));
			}
		}
		else
		{
			L.push_back(NA[t]);
			S.pop();
		}
	}

}
//template<typename T>//树的深度优先遍历非递归算法
//void Tree<T>::SimDFS(list<T>& L)const {
//		int t = root;
//		if (t < 0 || t >= sizeN)
//			return;
//		stack<int> S;
//		for (int i = 0; i < sizeN; i++)
//		{
//			L.push_back(NA[t]);
//			if (HL[t].size() != 0)
//			{
//				list<int>::const_iterator first = HL[t].begin();
//				if (HL[t].size() > 1)
//					for (list<int>::const_iterator last = --HL[t].end(); last != first; last--)
//						S.push(*last);
//				t = *first;
//			}
//			else
//			{
//				if (!S.empty())
//				{
//					t = S.top();
//					S.pop();
//				}
//			}
//		}
//		
//}


