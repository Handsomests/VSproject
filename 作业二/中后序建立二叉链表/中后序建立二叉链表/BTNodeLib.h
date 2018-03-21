#pragma once
#include<vector>
#include<queue>
#include<iostream>
using namespace std;
#include"BTNode.h"
struct Location {
	int xindent, ylevel;     // 节点坐标的位置
};
void Gotxy(int x, int y) {
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
//垂直输出二叉树
template<typename T>
void PrintBTree(const BTNode<T>*t, int screenwidth) {
	if (t == NULL)
		return;
	int level = 0, offset = screenwidth / 2;      //从0层开始,缩进量是屏幕宽度的一半
	Location floc, cloc;                    //记录孩子和双亲的节点的输出位置的变量
	queue<const BTNode<T> *>Q;             //存取节点指针的队列
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
			//cout << t->left->data;
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
//幂集递归算法
//template<typename T>
//void Power(vector<vector<T> >& outL,vector<T> &sL,vector<T> &pL,int pos){
//  if(sL.size()==0)
//  return;
//  if(pos==sL.size()){
//  outL.push_back(pL);
//  return;
//  }
//  pL.push_back(sL[pos]);
//  Power(outL,sL,pL,pos+1）；
//  pL.pop_back();
//  Power(outL,sL,pL,pos+1);
//  }