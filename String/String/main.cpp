#include"String.h"
#include<iostream>
using namespace std;
int main() {
	String s="file";
	s = "working";
	String s1 = "www";
	String d = s;
	cout<<s.Insert(2, s1);//不能插入s自身
	
	cout <<d<<s<<s.Erase(2,3);
	return 0;
}