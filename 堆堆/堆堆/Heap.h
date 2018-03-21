#pragma once
#include<vector>
#include<iostream>
#include<stdlib.h>
using namespace std;
template<typename T>
class Heap {
	vector<T> vec;       //向量容器 用来储存堆
	int size;            //表示数据的个数
	void BuildHeap(void);    //把向量容器类中的数据调整为堆
	void PercolateDown(int h);  //向下调整为堆,主要用于删除操作
	void PercolateUp();         //向上调整为堆,用于插入操作
public:
	explicit Heap(int max = 100) :vec(max), size(0) {}   //建空堆
	explicit Heap(const vector<T>& vt);               //用向量对象创建堆对象
	bool Empty(void)const { return(size == 0); }       //判断堆是否为空
	int Size()const { return size; }                 //取堆的数据元素的个数

	void Insert(const T&item);                               //堆插入
	const T& top(void)const { return(vec[0]); }           //取堆的首元素
	void DeleteMin();                                  //删除堆首元素
	void DeleteMin(T& item);                       //把删除的元素作为参数返回
	void Clear() { size = 0; }               //堆清空
};
template<typename T>
void Heap<T>::PercolateDown(int n) {             //向下 调整为堆.h表示根的下标
	int p = n, c = 2 * p + 1;                  //p和c表示双亲和孩子的下标
	T temp = vec[p];
	while (c < size) {                         //!!c是下标
		if (c + 1 < size&&vec[c + 1] < vec[c])    //取左右孩子中的最小者
			++c;
		if (temp <= vec[c])
			break;
		else {                              //双亲大于左右孩子
			vec[p] = vec[c];                 //把左右孩子的最小值移动到双亲的位置
			p = c;
			c = 2 * p + 1;
		}
	}
	vec[p] = temp;
}
template<typename T>
void Heap<T>::DeleteMin() {                    //删除堆的首元素
	if (size == 0) {
		cout << "Heap empty!"; exit(1);
	}
	vec[0] = vec[size - 1];
	size--;
	PercolateDown(0);                      //向下调整为堆
}
template<typename T>
void Heap<T>::DeleteMin(T &item) {            //删除堆的首元素,并返回删除的元素值
	if (size == 0) {
		cout << "Heap empty"; exit(1);
	}
	item = vec[0];
	vec[0] = vec[size - 1];
	size--;
	PercolateDown(0);
}
template<typename T>
void Heap<T>::PercolateUp() {               //向上调整为堆
	int c = size - 1, p = (c - 1) / 2;      //c和p分别表示孩子和双亲的坐标
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
template<typename T>                        //堆插入
void Heap<T>::Insert(const T&item) {
	if (size == vec.size())
		vec.resize(vec.size() * 2);
	vec[size] = item;;
	size++;
	PercolateUp();
}
template<typename T>                       //构造函数.用向量类对象创建堆类对象
Heap<T>::Heap(const vector<T>& vt) :vec(vt.size() + 10), size(vt.size()) {
	for (int i = 0; i < size; ++i)
		vec[i] = vt[i];
	BuildHeap();
}

template<typename T>                    //把向量类对象调整为栈
void Heap<T>::BuildHeap(void) {
	for (int i = size / 2 - 1; i >= 0; i--)
		PercolateDown(i);
}
//堆排序
template<typename T>
void BuildHeap(T pa[], int size) {              //将数组h调整为堆
	for (int i = (size / 2) - 1; i >= 0; i--)      //将下标[i,size)范围内的数据元素向下调整为堆
		PercolateDown(pa, i, size);              //将下标[pos,size)范围内的数据元素向下调整为堆
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
void HeapSort(T pa[], int n) {                     //堆排序
	T temp;
	BuildHeap(pa, n);
	for (int i = n - 1; i > 0; i--) {
		temp = pa[0];
		pa[0] = pa[i];
		pa[i] = temp;
		PercolateDown(pa, 0, i);
	}
}
////堆排序法2
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
//template<typename T>  //将下标[0,size)范围内的数组元素向下调整为堆
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