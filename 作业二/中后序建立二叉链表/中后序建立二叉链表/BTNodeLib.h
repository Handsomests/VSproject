#pragma once
#include<vector>
#include<queue>
#include<iostream>
using namespace std;
#include"BTNode.h"
struct Location {
	int xindent, ylevel;     // �ڵ������λ��
};
void Gotxy(int x, int y) {
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
//��ֱ���������
template<typename T>
void PrintBTree(const BTNode<T>*t, int screenwidth) {
	if (t == NULL)
		return;
	int level = 0, offset = screenwidth / 2;      //��0�㿪ʼ,����������Ļ��ȵ�һ��
	Location floc, cloc;                    //��¼���Ӻ�˫�׵Ľڵ�����λ�õı���
	queue<const BTNode<T> *>Q;             //��ȡ�ڵ�ָ��Ķ���
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
//�ݼ��ݹ��㷨
//template<typename T>
//void Power(vector<vector<T> >& outL,vector<T> &sL,vector<T> &pL,int pos){
//  if(sL.size()==0)
//  return;
//  if(pos==sL.size()){
//  outL.push_back(pL);
//  return;
//  }
//  pL.push_back(sL[pos]);
//  Power(outL,sL,pL,pos+1����
//  pL.pop_back();
//  Power(outL,sL,pL,pos+1);
//  }