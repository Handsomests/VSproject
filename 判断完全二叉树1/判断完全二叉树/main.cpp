#include<iostream>
#include<queue>
#include"BTNode.h"
using namespace std;

template<typename T>
bool Is_complete_binary_tree(const BTNode<T>* t)
{
	bool b=true;
	queue<const BTNode<T>*> Q;
	Q.push(t);
	while (!Q.empty())
	{
		t = Q.front();
		Q.pop();
		if(t == NULL)
		{
			do
			{
				t = Q.front();
				Q.pop();
				if (t != NULL)
				{
					b = false;
					break;
				}
			} while (!Q.empty());
		}
		else if (b)
		{
			Q.push(t->left);
			Q.push(t->right);
		}
		else
		{
			break;
		}
	}
	return b;
}

int main()
{
	BTNode<char> *nullp = NULL;
	BTNode<char>  *gp = GetBTNode('G');
	BTNode<char>  *fp = GetBTNode('F');
	BTNode<char>  *ep = GetBTNode('E');
	BTNode<char>  *dp = GetBTNode('D');
	BTNode<char>  *cp = GetBTNode('C', fp,gp);
	BTNode<char>  *bp = GetBTNode('B', dp,ep);
	BTNode<char>  *ap = GetBTNode('A', bp, cp);
	if (Is_complete_binary_tree(ap))
		cout << "是完全二叉树." << endl;
	else
		cout << "不是完全二叉树." << endl;
	return(0);
}