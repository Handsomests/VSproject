#pragma once
#include<stdlib.h>//包含exit(1)函数
#include<iostream>
using namespace std;
class SeqList {
private:     //私有
	Type* data;
	int size;
	int max;
	void Error(char * s)const { cout << s; exit(1); }
public:
//构造函数和析构函数
	SeqList(int n = 100);  //默认构造函数
	SeqList(const SeqList& l);//复制构造函数
	SeqList() { delete[]data; }//析构函数
//用于修改的成员函数
	SeqList& SeqList::operator=(const SeqList& l);   //赋值函数
	void InsertRear(const Type& item);      //尾插
	void Insert(Type* itr, const Type& item);  //插入
	void Clear() { size = 0; }//清表
	void Erase(Type * itr);
	Type& operator[](int id);  //下标重载
	const Type& operator[](int id)const;


//用于读取成员函数
	int Size()const { return size; }
	int Empty()const { return size == 0; }
	int Full()const { return size == max; }
	Type* Begin(){ return data; }
    const Type* Begin()const { return data; }//两个const 一个表示函数返回值不能被修改 另一个表示函数类成员不能被修改
	Type* End() { return data + size; }
	const Type* End()const { return data + size; }
};
//下标运算符重载
Type& SeqList::operator[](int id) {
	if (id<0 || id>size - 1)
		Error("id is illegal\n");
	return data[id];
}
//常量型下标运算符重载
const Type& SeqList::operator[](int id)const {
	if (id<0 || id>size - 1)
		Error("id is illeagal");
	return data[id];
}
 //默认构造函数
	SeqList::SeqList(int n) {  
	data = new Type[n];
		if (data == NULL)
			Error("Memory allocation error\n");   //错误类型提示
		size = 0;
		max = n;
	}
//赋值构造函数
SeqList::SeqList(const SeqList&l) {
	data = new Type[l.max];
	if (data == NULL)
		Error("Memory allocation error\n");
	for (int i = 0; i < l.size; i++)
		data[i] = l.data[i];
	size = l.size;
	max = l.max;
}
//定点插入函数
void SeqList::Insert(Type * itr, const Type &item) {
	for (Type *p = data + size, *q = data + size - 1; p != itr; --p, --q)//将itr位置前的数据后移
		*p = *q;
	*itr = item;
	size++;
}
//尾插函数
void SeqList::InsertRear(const Type &item) {
	if (size+1 > max||size<0)
		Error("is no location");
	Type*p = data + size;
	*p = item;
	size++;
}
//删除函数
void SeqList::Erase(Type * itr) {
	for (Type*p = itr, *q = itr + 1; p != data + size; ++p, ++q)
		*p = *q;
	size--;
}
//复制函数
SeqList& SeqList::operator=(const SeqList& l) {
	if (max != l.max) {
		delete[]data;
		data = new Type[l.max];
		if (data = NULL)
			Error("Memory allocation error\n");
	}
	for (int i = 0; i < l.size; ++i)
		data[i] = l.data[i];
	size = l.size;
	max = l.max;
	return *this;
}