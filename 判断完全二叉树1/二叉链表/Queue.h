#pragma once
#include"list.h"
template<typename T>
class Queue {
	List<T>queueL;
public:
	Queue(){}
	~Queue(){}
	int Size()const { return queueL.Size(); }
	bool Empty()const { return queueL.Empty(); }
	const T&Front()const { return queueL.Begin(); }//ȡ�ӵ�ͷԪ��
	const T& Back()const { return queueL.End(); }
	void Push(const T&item) { queueL.Push_Back(item); }  //���
	T Pop() { T item = queueL.Front(); queueL.Pop_Front(); return item;}  //����
	void Clear() { queueL.Clear(); }    //�ÿն�
};