#include"BTNode.h"
#include<iostream>
#include<queue>
using namespace std;
template<typename T>
bool IsCompleteBinaryTree(const BTNode<T>* t)
{
	bool flag = true;
	queue<const BTNode<T>*>Q;
	Q.push(t);
	while (!Q.empty()) {
		t = Q.front();
		Q.pop();
		if (t == NULL) {
			t = Q.front();
			Q.pop();
			if (t != NULL) {
				flag = false;
				break;
			}
		}
		else if (t!=NULL) {
			Q.push(t->left);
			Q.push(t->right);
		}
	}
	return flag;
}
template<class T>
void ComBTree(const BTNode<T>* t)// 判断完全二叉树用层次遍历（出队之后访问的模式）
{
	if (t == NULL)
		return;
	queue<const BTNode<T>*> Q;
	Q.push(t);
	while (!Q.empty())
	{
		t = Q.front(); Q.pop();
		if (t == NULL)
			break;
		Q.push(t->left);
		Q.push(t->right);
	}
	while (!Q.empty())
	{
		t = Q.front(); Q.pop();
		if (t != NULL)
		{
			cout << "不是一棵完全二叉树" << endl;
			return;
		}
	}
	cout << "是一棵完全二叉树" << endl;
}


int main()
{
	BTNode<char> *nullp = NULL;
	BTNode<char>  *gp = GetBTNode('G');
	BTNode<char>  *fp = GetBTNode('F');
	BTNode<char>  *ep = GetBTNode('E');
	BTNode<char>  *dp = GetBTNode('D');
	BTNode<char>  *cp = GetBTNode('C', nullp, gp);
	BTNode<char>  *bp = GetBTNode('B', dp, ep);
	BTNode<char>  *ap = GetBTNode('A', bp, cp);
	ComBTree(ap);
	/*if (IsCompleteBinaryTree(ap))
		cout << "是完全二叉树." << endl;
	else
		cout << "不是完全二叉树." << endl;*/
	return(0);
}