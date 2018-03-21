#pragma once
#include<list>
#include<queue>
#include<stack>
#include<string>
using namespace std;
template<typename T>
class Tree {
	T * NA;     //�ڵ�����ָ��
	list<int>* HL;    //������������ָ��
	int root;       //�����±�
	int sizeN, sizeC;   //�ڵ��������ӽڵ���
	int maxN;         //�ڵ����鳤�ȼ�����
public:
	Tree(int n = 100) :root(-1), sizeN(0), sizeC(0), maxN(n)  //���캯��
	{
		NA = new T[n];
		HL = new list<int>[n];

	}
	~Tree() { delete[]NA; delete[]HL; }   //��������
    int Empty()const{return(sizeN==0);}  //�п�
	int Full()const { return(sizeN = maxN); }  //����
	int SizeN()const { return(sizeN); }     //ȡ�ڵ���
	int SizeC()const { return(sizeC); }  //ȡ���ӵ��±�
	int FindNode(const T& node)const;  //ȡ�ڵ���±�
	bool FindNode(T& node, int pos)const;  //ȡ�±�Ϊpos�Ľڵ㣬�洢��node��

	bool InsertN(const T& node);         //	����ڵ�
	bool InsertC(const T& parent, const T& child);   //���뺢�ӵĽڵ�


	void ReadTree(const char* filename);   //���ļ���ȡ��������
	void WriteTree(const char* filename);  //����������д�뵽�ļ�

	void BFS(list<T>& L)const;             //������ȱ���
	void DFS(list<T>& L)const;      //������ȱ���
	void LFS(list<T>& L)const;      //�������
	void SimLFS(list<T>& L)const;      //��������ǵݹ��㷨
	//void SimLFS2(list<T>& L)const;     //
	void SimDFS(list<T>& L)const;     //����������ȱ����ǵݹ��㷨	
	template<typename T>
	void DFS(list<T>& L, int t)const {   //�ȸ�����
		if (t < 0 || t >= sizeN)
			return;
		L.push_back(NA[t]);      //����ڵ���Ϊ����ֵ
		list<int>::const_iterator first, last;
		first = HL[t].begin(); last = HL[t].end();
		for (; first != last; ++first)     //ɨ�躢�ӽڵ�,Ѱ���ֵ�
			DFS(L, *first);
	}
	template<typename T>
	void LFS(list<T>& L, int p)const {   //�������
		if (p < 0 || p >= sizeN)
			return;
		list<int>::const_iterator first, last;
		first = HL[p].begin(); last = HL[p].end();
		for (; first != last; ++first)     //ɨ�躢�ӽڵ�,Ѱ���ֵ�
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
template<typename T>//���ļ��ж�ȡ��������
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
template<typename T>//����������д�뵽�ļ�����ȥ
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
template<typename T>       //������ȱ���
void Tree<T>::BFS(list<T>& L)const {
	if (sizeN == 0)
		return;
	queue<int> Q;
	Q.push(root);          //���±����
	list<int>::const_iterator first, last;//�������������
	while (!Q.empty()) {
		int pos = Q.front();               //�Ӷ�����ȥ�ڵ���±�
		Q.pop();
		L.push_back(NA[pos]);             //�洢�ڵ���Ϊ����ֵ
		first = HL[pos].begin();
		last = HL[pos].end();
		for (; first != last; ++first)          //ɨ�躢������
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
template<typename T>//��������ǵݹ��㷨
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
//template<typename T>//����������ȱ����ǵݹ��㷨
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


