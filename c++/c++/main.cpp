#include"AddressBook.h"
#include<iostream>
#include<stdio.h>
using namespace std;
int main() {
	AddressBook add;
	int i; int d = -1;
	cout << "通讯录管理系统"<<endl;
	do {
		cout << "1 添加 2 显示 3 存储 4 装入 5 查询 6 修改 0 退出" << endl;
		cout << "输入序号:"; cin >> i; cin.ignore();
		switch (i)
		{
		case 1:
			add.add(); d = 1; break;
		case 2:
			add.display(); d = 2; break;
		case 3:
			if (d == 3 || d == 4) {}  //防止重复保存
			else {
				add.save(); d = 3;
			}break;
		case 4:
			if (d == 4 || d == 3) {}//防止重复装入
			else {
				add.load(); d = 4;
			}break;
		case 5:
			add.query(); d = 5; break;
		case 6:
			add.update(); d = 6; break;
		case 0:
			if (d != 5) {
				add.save();
				exit(1);
			}
			else
				exit(1);
		default:
			break;
		}
	} while (i != 0);
	return 0;
}