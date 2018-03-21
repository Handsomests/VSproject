#include<iostream>
#include"BTNode.h"
using namespace std;

int main()
{
	BTNode<char> *nullp = NULL;
	BTNode<char>  *gp = GetBTNode('G');
	BTNode<char>  *fp = GetBTNode('F');
	BTNode<char>  *ep = GetBTNode('E');
	BTNode<char>  *dp = GetBTNode('D');
	BTNode<char>  *cp = GetBTNode('C', fp, gp);
	BTNode<char>  *bp = GetBTNode('B', dp, ep);
	BTNode<char>  *ap = GetBTNode('A', bp, cp);
	/*Level(ap);*/
	/*cout << endl;*/
	/*Swap_child(ap);*/
	//Level(ap);
	/*cout << endl;*/
	Swap_child(ap);
	Level(ap);
	/*cout << endl;*/
	return(0);
}