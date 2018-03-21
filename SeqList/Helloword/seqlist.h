#pragma once
#include<stdlib.h>//����exit(1)����
#include<iostream>
using namespace std;
class SeqList {
private:     //˽��
	Type* data;
	int size;
	int max;
	void Error(char * s)const { cout << s; exit(1); }
public:
//���캯������������
	SeqList(int n = 100);  //Ĭ�Ϲ��캯��
	SeqList(const SeqList& l);//���ƹ��캯��
	SeqList() { delete[]data; }//��������
//�����޸ĵĳ�Ա����
	SeqList& SeqList::operator=(const SeqList& l);   //��ֵ����
	void InsertRear(const Type& item);      //β��
	void Insert(Type* itr, const Type& item);  //����
	void Clear() { size = 0; }//���
	void Erase(Type * itr);
	Type& operator[](int id);  //�±�����
	const Type& operator[](int id)const;


//���ڶ�ȡ��Ա����
	int Size()const { return size; }
	int Empty()const { return size == 0; }
	int Full()const { return size == max; }
	Type* Begin(){ return data; }
    const Type* Begin()const { return data; }//����const һ����ʾ��������ֵ���ܱ��޸� ��һ����ʾ�������Ա���ܱ��޸�
	Type* End() { return data + size; }
	const Type* End()const { return data + size; }
};
//�±����������
Type& SeqList::operator[](int id) {
	if (id<0 || id>size - 1)
		Error("id is illegal\n");
	return data[id];
}
//�������±����������
const Type& SeqList::operator[](int id)const {
	if (id<0 || id>size - 1)
		Error("id is illeagal");
	return data[id];
}
 //Ĭ�Ϲ��캯��
	SeqList::SeqList(int n) {  
	data = new Type[n];
		if (data == NULL)
			Error("Memory allocation error\n");   //����������ʾ
		size = 0;
		max = n;
	}
//��ֵ���캯��
SeqList::SeqList(const SeqList&l) {
	data = new Type[l.max];
	if (data == NULL)
		Error("Memory allocation error\n");
	for (int i = 0; i < l.size; i++)
		data[i] = l.data[i];
	size = l.size;
	max = l.max;
}
//������뺯��
void SeqList::Insert(Type * itr, const Type &item) {
	for (Type *p = data + size, *q = data + size - 1; p != itr; --p, --q)//��itrλ��ǰ�����ݺ���
		*p = *q;
	*itr = item;
	size++;
}
//β�庯��
void SeqList::InsertRear(const Type &item) {
	if (size+1 > max||size<0)
		Error("is no location");
	Type*p = data + size;
	*p = item;
	size++;
}
//ɾ������
void SeqList::Erase(Type * itr) {
	for (Type*p = itr, *q = itr + 1; p != data + size; ++p, ++q)
		*p = *q;
	size--;
}
//���ƺ���
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