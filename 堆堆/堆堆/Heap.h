#pragma once
#include<vector>
#include<iostream>
#include<stdlib.h>
using namespace std;
template<typename T>
class Heap {
	vector<T> vec;       //�������� ���������
	int size;            //��ʾ���ݵĸ���
	void BuildHeap(void);    //�������������е����ݵ���Ϊ��
	void PercolateDown(int h);  //���µ���Ϊ��,��Ҫ����ɾ������
	void PercolateUp();         //���ϵ���Ϊ��,���ڲ������
public:
	explicit Heap(int max = 100) :vec(max), size(0) {}   //���ն�
	explicit Heap(const vector<T>& vt);               //���������󴴽��Ѷ���
	bool Empty(void)const { return(size == 0); }       //�ж϶��Ƿ�Ϊ��
	int Size()const { return size; }                 //ȡ�ѵ�����Ԫ�صĸ���

	void Insert(const T&item);                               //�Ѳ���
	const T& top(void)const { return(vec[0]); }           //ȡ�ѵ���Ԫ��
	void DeleteMin();                                  //ɾ������Ԫ��
	void DeleteMin(T& item);                       //��ɾ����Ԫ����Ϊ��������
	void Clear() { size = 0; }               //�����
};
template<typename T>
void Heap<T>::PercolateDown(int n) {             //���� ����Ϊ��.h��ʾ�����±�
	int p = n, c = 2 * p + 1;                  //p��c��ʾ˫�׺ͺ��ӵ��±�
	T temp = vec[p];
	while (c < size) {                         //!!c���±�
		if (c + 1 < size&&vec[c + 1] < vec[c])    //ȡ���Һ����е���С��
			++c;
		if (temp <= vec[c])
			break;
		else {                              //˫�״������Һ���
			vec[p] = vec[c];                 //�����Һ��ӵ���Сֵ�ƶ���˫�׵�λ��
			p = c;
			c = 2 * p + 1;
		}
	}
	vec[p] = temp;
}
template<typename T>
void Heap<T>::DeleteMin() {                    //ɾ���ѵ���Ԫ��
	if (size == 0) {
		cout << "Heap empty!"; exit(1);
	}
	vec[0] = vec[size - 1];
	size--;
	PercolateDown(0);                      //���µ���Ϊ��
}
template<typename T>
void Heap<T>::DeleteMin(T &item) {            //ɾ���ѵ���Ԫ��,������ɾ����Ԫ��ֵ
	if (size == 0) {
		cout << "Heap empty"; exit(1);
	}
	item = vec[0];
	vec[0] = vec[size - 1];
	size--;
	PercolateDown(0);
}
template<typename T>
void Heap<T>::PercolateUp() {               //���ϵ���Ϊ��
	int c = size - 1, p = (c - 1) / 2;      //c��p�ֱ��ʾ���Ӻ�˫�׵�����
	T temp = vec[c];
	while (c > 0)
		if (vec[p] <= temp)
			break;
		else {
			vec[c] = vec[p];
			c = p;
			p = (c - 1) / 2;
		}
		vec[c] = temp;
}
template<typename T>                        //�Ѳ���
void Heap<T>::Insert(const T&item) {
	if (size == vec.size())
		vec.resize(vec.size() * 2);
	vec[size] = item;;
	size++;
	PercolateUp();
}
template<typename T>                       //���캯��.����������󴴽��������
Heap<T>::Heap(const vector<T>& vt) :vec(vt.size() + 10), size(vt.size()) {
	for (int i = 0; i < size; ++i)
		vec[i] = vt[i];
	BuildHeap();
}

template<typename T>                    //��������������Ϊջ
void Heap<T>::BuildHeap(void) {
	for (int i = size / 2 - 1; i >= 0; i--)
		PercolateDown(i);
}
//������
template<typename T>
void BuildHeap(T pa[], int size) {              //������h����Ϊ��
	for (int i = (size / 2) - 1; i >= 0; i--)      //���±�[i,size)��Χ�ڵ�����Ԫ�����µ���Ϊ��
		PercolateDown(pa, i, size);              //���±�[pos,size)��Χ�ڵ�����Ԫ�����µ���Ϊ��
}
template<typename T>
void PercolateDown(T pa[], int pos, int size) {
	int p = pos, c = 2 * p + 1;
	T temp = pa[p];
	while (c < size) {
		if (c + 1 < size&&pa[c + 1] > pa[c])
			++c;
		if (temp >= pa[c])
			break;
		else
		{
			pa[p] = pa[c];
			p = c; c = p * 2 + 1;
		}
	}
	pa[p] = temp;
}
template<typename T>
void HeapSort(T pa[], int n) {                     //������
	T temp;
	BuildHeap(pa, n);
	for (int i = n - 1; i > 0; i--) {
		temp = pa[0];
		pa[0] = pa[i];
		pa[i] = temp;
		PercolateDown(pa, 0, i);
	}
}
////������2
//template<typename T>
//void PercolateUp(T *pa, int pos) {
//	int c = pos, p = (c - 1) / 2;
//	T temp = pa[c];
//	while (c > 0) {
//		if (pa[p] > temp)
//			break;
//		else {
//			pa[c] = pa[p];
//			c = p; p = (c - 1) / 2;
//		}
//		pa[c] = temp;
//	}
//}
//template<typename T>  //���±�[0,size)��Χ�ڵ�����Ԫ�����µ���Ϊ��
//void PercolateDown(T *pa, int size) {
//	int p = 0, c = 2 * p + 1;
//	T temp = pa[p];
//	while (c < size) {
//		if (c + 1 < size&&pa[c + 1] > pa[c])
//			++c;
//		if (temp > pa[c])
//			break;
//		else {
//			pa[p] = pa[c];
//			p = c; c = 2 * p + 1;
//		}
//	}
//	pa[p] = temp;
//}
//template<typename T>
//void BuildHeap(T*pa, int size) {
//	for (int i = 1; i < size; i++)
//		PercolateUp(pa, i);
//}
//template<typename T>
//void HeapSort2(T * pa, int n) {
//	BuildHeap(pa, n);
//	T temp;
//	for (int i = n - 1; i > 0; i--) {
//		temp = pa[0];
//		pa[0] = pa[i];
//		pa[i] = temp;
//		PercolateDown(pa, i);
//	}
//}