#include<iostream>
#include<vector>
using namespace std;

template<typename T>
void BuildHeap(vector<T>& vt, int size)
{
	for (int i = size / 2 - 1; i >= 0; i--)
		PercolateDown(vt, i, size);
}
template<typename T>
void PercolateDown(vector<T>& vt, int pos, int size)
{
	int p = pos, c = 2 * p + 1;
	T temp = vt[p];
	while (c<size)
	{
		if (c + 1 < size&&vt[c + 1] > vt[c])
			++c;
		if (temp >= vt[c])
			break;
		else
		{
			vt[p] = vt[c];
			p = c;
			c = 2 * p + 1;
		}
	}
	vt[p] = temp;
}
template<typename T>
void HeapSort(vector<T>& vt, int n)//堆排序
{
	T temp;
	BuildHeap(vt, n);
	for (int i = n - 1; i > 0; i--)
	{
		temp = vt[0];
		vt[0] = vt[i];
		vt[i] = temp;
		PercolateDown(vt, 0, i);
	}
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

int main()
{
	cout << "顺序表" << endl << "输入10个整数：" << endl;
	vector<int> a;
	int item;
	for (int i = 0; i < 10; i++)
	{
		cin >> item;
		a.push_back(item);
	}
	cout << "排序前：";
	for (int i = 0; i < 10; i++)
		cout << a[i] << '\t';
	cout << endl;
	HeapSort(a, 10);
	cout << "排序后：";
	for (int i = 0; i < 10; i++)
		cout << a[i] << '\t';
	cout << endl << endl;

	cout << "数组" << endl << "输入10个整数：" << endl;
	int b[10];
	for (int i = 0; i < 10; i++)
	{
		cin >> item;
		b[i] = item;
	}
	cout << "排序前：";
	for (int i = 0; i < 10; i++)
		cout << b[i] << '\t';
	cout << endl;
	int* p = b;
	HeapSort(p, 10);
	cout << "排序后：";
	for (int i = 0; i < 10; i++)
		cout << b[i] << '\t';
	cout << endl << endl;
	return 0;
}