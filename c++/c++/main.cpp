#include"AddressBook.h"
#include<iostream>
#include<stdio.h>
using namespace std;
int main() {
	AddressBook add;
	int i; int d = -1;
	cout << "ͨѶ¼����ϵͳ"<<endl;
	do {
		cout << "1 ��� 2 ��ʾ 3 �洢 4 װ�� 5 ��ѯ 6 �޸� 0 �˳�" << endl;
		cout << "�������:"; cin >> i; cin.ignore();
		switch (i)
		{
		case 1:
			add.add(); d = 1; break;
		case 2:
			add.display(); d = 2; break;
		case 3:
			if (d == 3 || d == 4) {}  //��ֹ�ظ�����
			else {
				add.save(); d = 3;
			}break;
		case 4:
			if (d == 4 || d == 3) {}//��ֹ�ظ�װ��
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