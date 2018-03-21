#pragma
#include<stdlib.h>
template<typename T>
class List {
	struct Node {
		T data;
		Node * prev, *next;
		Node(const T &d = T(), Node * p = NULL, Node * n = NULL) :data(d), prev(p), next(n) {}
	};
	Node *head; //头结点指针
	Node *tail;  //尾节点指针
	int size;   //数据节点的个数
	void Init() { size = 0; head = new Node; tail = new Node; head->next = tail; tail->prev = head; }    //初始化函数
public:
	class const_iterator {
	protected:
		Node * current;
		T & retrieve()const { return current->data; }
		const_iterator(Node * p) :current(p) {}   //转换构造函数
		friend class List<T>;
	public:
		const_iterator() :current(NULL) {}
		const T& operator * ()const { return retrieve(); }
		const_iterator& operator++(){                //前++
			current = current->next;
			return *this;
		}
		const_iterator operator++(int) {             //后++
			const_iterator old = *this;
			++(*this);
			return old;
		}
		const_iterator& operator--(){   //前--
			current = current->prev;
			return *this;
		}
		const_iterator operator--(int) {             //后--
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
		iterator& operator++() {                //前++
			current = current->next;
		}
		iterator operator++(int) {             //后++
			iterator old = *this;
			++(*this);
			return old;
		}
		iterator& operator--() {   //前--
			current = current->prev;
			return *this;
		}
		iterator operator--(int) {             //后--
			iterator old = *this;
			--(*this);
			return old;
		}
	};
	List() { Init(); }//生成空表
	List(const List<T>&l) { Init(); operator=(l); }   //赋值构造函数
	~List() { Clear(); delete head; delete tail; }  //析构函数
	const List& operator=(const List&l);   //复制赋值运算符函数
	iterator Begin() { return iterator(head->next); }
	const_iterator Begin()const { return const_iterator(head->next); }
	iterator End() { return iterator(tail); }
	const_iterator End()const { return const_iterator(tail); }

	T&Front() { return *Begin(); }       //返回首元素的引用
	const T&Front()const { return *Begin(); }
	T&Back() { return *End(); }    //返回尾元素
	const T&Back() const { return *End(); }
	void Push_Front(const T&item) { Insert(Begin(), item); }//首插
	void Push_Back(const T&item) { Insert(End(), item); }//尾插
	void Pop_Front() { Erase(Begin()); }     //首删
	void Pop_Back() { Erase(End()); }       //尾删
	iterator Insert(iterator itr, const T& item);   //在指示器的位置插入item
	iterator Erase(iterator itr);         //删除指示器位置上的节点
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

	 //p->prev = p->prev->next = new Node(item, p->prev, p);等价于以下3步：
	p->prev->next = new Node(item, p->prev, p);
	p->prev = p->prev->next;
	return iterator(p->prev);
	/* 又等价于以下2步：
	* Node *newNode = new Node(item, p->prev, p);
	* p->prev = p->prev->next = newNode;
	*/
}





