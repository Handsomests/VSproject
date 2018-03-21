#pragma
#include<stdlib.h>
template<typename T>
class List {
	struct Node {
		T data;
		Node * prev, *next;
		Node(const T &d = T(), Node * p = NULL, Node * n = NULL) :data(d), prev(p), next(n) {}
	};
	Node *head; //ͷ���ָ��
	Node *tail;  //β�ڵ�ָ��
	int size;   //���ݽڵ�ĸ���
	void Init() { size = 0; head = new Node; tail = new Node; head->next = tail; tail->prev = head; }    //��ʼ������
public:
	class const_iterator {
	protected:
		Node * current;
		T & retrieve()const { return current->data; }
		const_iterator(Node * p) :current(p) {}   //ת�����캯��
		friend class List<T>;
	public:
		const_iterator() :current(NULL) {}
		const T& operator * ()const { return retrieve(); }
		const_iterator& operator++(){                //ǰ++
			current = current->next;
			return *this;
		}
		const_iterator operator++(int) {             //��++
			const_iterator old = *this;
			++(*this);
			return old;
		}
		const_iterator& operator--(){   //ǰ--
			current = current->prev;
			return *this;
		}
		const_iterator operator--(int) {             //��--
			const_iterator old = *this;
			--(*this);
			return old;
		}
		bool operator==(const const_iterator & rhs)const { return current == rhs.current; }
		bool operator!=(const const_iterator & rhs)const { return current != rhs.current; }
	};
	class iterator :public const_iterator {
	protected:
		iterator(Node*p):const_iterator(p){}
		friend class List<T>;
	public:
		iterator():current(NULL){}
		 T& operator * () { return retrieve(); }
		const T&operator *()const { return const_iterator::operator * (); }
		iterator& operator++() {                //ǰ++
			current = current->next;
		}
		iterator operator++(int) {             //��++
			iterator old = *this;
			++(*this);
			return old;
		}
		iterator& operator--() {   //ǰ--
			current = current->prev;
			return *this;
		}
		iterator operator--(int) {             //��--
			iterator old = *this;
			--(*this);
			return old;
		}
	};
	List() { Init(); }//���ɿձ�
	List(const List<T>&l) { Init(); operator=(l); }   //��ֵ���캯��
	~List() { Clear(); delete head; delete tail; }  //��������
	const List& operator=(const List&l);   //���Ƹ�ֵ���������
	iterator Begin() { return iterator(head->next); }
	const_iterator Begin()const { return const_iterator(head->next); }
	iterator End() { return iterator(tail); }
	const_iterator End()const { return const_iterator(tail); }

	T&Front() { return *Begin(); }       //������Ԫ�ص�����
	const T&Front()const { return *Begin(); }
	T&Back() { return *End(); }    //����βԪ��
	const T&Back() const { return *End(); }
	void Push_Front(const T&item) { Insert(Begin(), item); }//�ײ�
	void Push_Back(const T&item) { Insert(End(), item); }//β��
	void Pop_Front() { Erase(Begin()); }     //��ɾ
	void Pop_Back() { Erase(End()); }       //βɾ
	iterator Insert(iterator itr, const T& item);   //��ָʾ����λ�ò���item
	iterator Erase(iterator itr);         //ɾ��ָʾ��λ���ϵĽڵ�
	int Size() const { return size; }
	bool Empty()const { return size == 0; }
	void Clear() { while (!Empty())Pop_Front(); }
};
template<typename T>
const List<T>& List<T>::operator=(const List<T>&l) {
	Clear();
	for (const_iterator itr = l.Begin(); itr != l.End(); ++itr)
		Push_Back(*itr);
	return *this;
}

template<typename T>
typename List<T>::iterator List<T>::Erase(iterator itr) {
	Node * p = itr.current;
	iterator re(p->next);
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	size--;
	return re;
}
template<typename T>
typename List<T>:: iterator List<T>:: Insert(iterator itr, const T&item){
	Node *p = itr.current;
	size++;
	/*return iterator(p->prev = p->prev->next = new Node(item,p->prev, p));*/

	 //p->prev = p->prev->next = new Node(item, p->prev, p);�ȼ�������3����
	p->prev->next = new Node(item, p->prev, p);
	p->prev = p->prev->next;
	return iterator(p->prev);
	/* �ֵȼ�������2����
	* Node *newNode = new Node(item, p->prev, p);
	* p->prev = p->prev->next = newNode;
	*/
}





