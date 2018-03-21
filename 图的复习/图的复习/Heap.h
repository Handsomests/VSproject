#pragma once
#include<vector>
#include<iostream>
using namespace std;

template<typename T>
class Heap
{
	vector<T> vec;
	int size;
	void BuildHeap(void);
	void PercolateDown(int h);
	void PercolateUp();
public:
	explicit Heap(int max = 100) :vec(max), size(0) {}
	explicit Heap(const vector<T>& vt);
	bool Empty(void)const { return(size == 0); }
	int Size(void) { return(size); }

	void Insert(const T& item);
	const T& Top(void)const { return(vec[0]); }
	void DeleteMin(void);
	void DeleteMin(T& item);
	void Clear(void) { size = 0; }
};
template<typename T>
Heap<T>::Heap(const vector<T>& vt) :vec(vt.size() + 10), size(vt.size())	//构造函数，用向量类对象创建堆类对象
{
	for (int i = 0; i < size; ++i)
		vec[i] = vt[i];
	BuildHeap();
}
template<typename T>
void Heap<T>::BuildHeap(void)	//把向量类对象调整为堆
{
	for (int i = size / 2 - 1; i >= 0; i--)
		PercolateDown(i);
}
template<typename T>
void Heap<T>::PercolateDown(int h)	//向下调整为堆，h表示根的下标
{
	int p = h, c = 2 * p + 1;
	T temp = vec[p];
	while (c < size)
	{
		if (c + 1 < size&&vec[c + 1] < vec[c])
			++c;
		if (temp <= vec[c])
			break;
		else {
			vec[p] = vec[c];
			p = c;
			c = 2 * p + 1;
		}
	}
	vec[p] = temp;
}
template<typename T>
void Heap<T>::PercolateUp()	//向上调整为堆
{
	int c = size - 1, p = (c - 1) / 2;
	T temp = vec[c];
	while (c > 0)
		if (vec[p] <= temp)
			break;
		else
		{
			vec[c] = vec[p];
			c = p;
			p = (c - 1) / 2;
		}
	vec[c] = temp;
}
template<typename T>
void Heap<T>::Insert(const T& item)	//堆插入
{
	if (size == vec.size())
		vec.resize(vec.size() * 2);
	vec[size] = item;
	size++;
	PercolateUp();
}
template<typename T>
void Heap<T>::DeleteMin()	//删除堆的首元素
{
	if (size == 0)
	{
		cout << "Heap empty!";
		exit(1);
	}
	vec[0] = vec[size - 1];
	size--;
	PercolateDown(0);
}
template<typename T>
void Heap<T>::DeleteMin(T& item)	//删除堆的首元素，并通过参数返回删除元素值
{
	if (size == 0)
	{
		cout << "Heap empty!";
		exit(1);
	}
	item = vec[0];
	vec[0] = vec[size - 1];
	size--;
	PercolateDown(0);
}

template<typename T>
void BuildHeap(T* pa, int size)
{
	for (int i = size / 2 - 1; i >= 0; i--)
		PercolateDown(pa, i, size);
}
template<typename T>
void PercolateDown(T* pa, int pos, int size)
{
	int p = pos, c = 2 * p + 1;
	T temp = pa[p];
	while (c<size)
	{
		if (c + 1 < size&&pa[c + 1] > pa[c])
			++c;
		if (temp >= pa[c])
			break;
		else
		{
			pa[p] = pa[c];
			p = c;
			c = 2 * p + 1;
		}
	}
	pa[p] = temp;
}
template<typename T>
void HeapSort(T* pa, int n)//堆排序
{
	T temp;
	BuildHeap(pa, n);
	for (int i = n - 1; i > 0; i--)
	{
		temp = pa[0];
		pa[0] = pa[i];
		pa[i] = temp;
		PercolateDown(pa, 0, i);
	}
}
