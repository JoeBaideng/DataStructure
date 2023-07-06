//#include "linkedlist.h"
#include<iostream>
using namespace std;


/*
* 这是一个基于模板的双向链表（LinkedList）的实现。
* 它包括头节点指针、链表大小和一些基本的操作函数，如插入、移除、判断包含、获取大小、清空链表等。
* 该链表支持数据元素的任意类型，并可以使用下标操作符进行访问和修改。
* 此外，还重载了输出流操作符，可以将链表中的元素输出到流中。
* 主要特点包括：节点结构体包含数据成员和前后指针，支持初始化列表构造函数，支持复制构造函数和赋值重载操作符。
* --ChatGPT
*/
template <typename T>
class LinkedList
{
private:
	struct Node
	{
		Node() {
			prev = nullptr;
			next = nullptr;
		}
		T data;
		Node* prev;  // 指向前一个节点的指针
		Node* next;  // 指向后一个节点的指针
	};

	Node* _head;  // 头节点指针
	int _size;    // 链表大小
	void _copy(const LinkedList<T>& other);
public:
	LinkedList();//默认构造函数
	~LinkedList();//析构函数
	LinkedList(const LinkedList<T>& other);//复制构造函数
	LinkedList(std::initializer_list<T> initList);//用初始化列表构造，使得可以用大括号初始化
	LinkedList<T>& operator=(const LinkedList<T>other);//赋值重载
	void insert(const T& ele);//头插值
	void remove(const T& ele);//移除一个元素
	bool contains(const T& ele) const;//是否包含
	int size() const;//大小
	void clear();//清空并重新初始化
	T& get(const int index)const;
	T& operator[](const int index);//重载[]，使得可以用下标修改并访问
	T operator[](const int index) const;  //重载[]，使得可以只读时用下标访问
	friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& lst)
	{
		// 在这里实现输出流操作符的重载
		// 可以使用os输出链表中的元素
		os << "[";
		typename LinkedList<T>::Node* current = lst._head->next;
		while (current != nullptr) {
			os << current->data;
			if (current->next != nullptr)
				os  << ",";
			current = current->next;
		}
		os << "]";
		return os;
	}//重载输出
};


int main() {
	LinkedList<int>lst;
	lst.insert(1);
	lst.insert(2);
	lst.insert(3);
	LinkedList<LinkedList<int>>lst2={lst,lst,lst};

	cout << lst2;
}

template<typename T>
void LinkedList<T>::_copy(const LinkedList<T>& other)
{
	Node* tmp = other._head->next; // 跳过头节点
	Node* last = _head; // 保存前一个节点的指针

	while (tmp != nullptr)
	{
		Node* newNode = new Node;
		newNode->data = tmp->data;
		newNode->prev = last;
		last->next = newNode;
		last = newNode;
		tmp = tmp->next;
	}
	_size = other._size;
}

template <typename T>
LinkedList<T>::LinkedList()
{
	//创建头节点
	_head = new Node;
	//初始化指针和大小
	_head->prev = nullptr;
	_head->next = nullptr;
	_size = 0;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	Node* tmp;
	while (_head->next != NULL)
	{
		tmp = _head;
		_head = _head->next;
		delete tmp;
	}
	delete _head;
	_size = 0;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
	_head = new Node; // 创建头节点
	_head->prev = nullptr;
	_head->next = nullptr;
	_size = 0;
	_copy(other);

}

template<typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> initList)
{
	//创建头节点
	_head = new Node;
	//初始化指针和大小
	_head->prev = nullptr;
	_head->next = nullptr;
	_size = initList.size();
	for (auto ele : initList)
	{
		insert(ele);
	}
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> other)
{
	clear();
	_copy(other);
	return *this;
	// TODO: 在此处插入 return 语句
}

//头插
template<typename T>
void LinkedList<T>::insert(const T& ele)
{
	if (_head == nullptr)
	{
		cout << "List not initiated!\n";
		return;
	}
	Node *tmp_head = _head;//创建临时头指针节点
	if (tmp_head->next == nullptr)//只有一个头节点
	{
		Node* add = new Node;
		add->data = ele;//数据赋值
		add->next = tmp_head->next;//新增节点后向指针连接
		tmp_head->next = add;
		add->prev = tmp_head;//新增节点前向指针连接
		
	}
	else//多于一个节点
	{
		Node* add = new Node;
		add->data = ele;//数据赋值
		tmp_head->next->prev = add;//头节点之后原本节点的前一个改为新增节点
		add->prev = tmp_head;//新增节点前向指针连接
		add->next = tmp_head->next;//新增节点后向指针连接
		tmp_head->next = add;//头节点的后一节点指向新增节点
	}
	_size++;
}

template<typename T>
void LinkedList<T>::remove(const T& ele)
{
	if (_head == nullptr)
	{
		cout << "List not initiated!\n";
		return;
	}
	Node* tmp_head = _head;//创建临时头指针节点
	while (tmp_head->next!=NULL)
	{
		tmp_head = tmp_head->next;
		if (tmp_head->data == ele)//删除第一个符合条件的值
		{
			tmp_head->front->next = tmp_head->next;
			tmp_head->next->front = tmp_head->front;
			_size--;
			break;
		}
	}
}

template<typename T>
bool LinkedList<T>::contains(const T& ele) const
{
	if (_head == nullptr)
	{
		cout << "List not initiated!\n";
		return false;
	}
	Node* tmp_head = _head;//创建临时头指针节点
	while (tmp_head->next != NULL)
	{
		tmp_head = tmp_head->next;
		if (tmp_head->data == ele)//删除第一个符合条件的值
		{
			return true;
		}
	}
	return false;
}

template<typename T>
int LinkedList<T>::size() const
{
	return _size;
}

template<typename T>
void LinkedList<T>::clear()
{
	Node* tmp;
	while (_head->next != NULL)
	{
		tmp = _head;
		_head = _head->next;
		delete tmp;
	}
	delete _head;
	//创建头节点
	_head = new Node;
	//初始化指针和大小
	_head->prev = nullptr;
	_head->next = nullptr;
	_size = 0;
}

template<typename T>
T& LinkedList<T>::get(const int index)const
{
	if (index < 0 || index >= _size)
	{
		throw out_of_range("Index out of range");
	}
	
	Node* current = _head->next;
	for (int i = 0; i < index; i++)
	{
		current = current->next;
	}

	return current->data;
}

template<typename T>
T& LinkedList<T>::operator[](const int index)
{
	if (index < 0 || index >= _size)
	{
		throw out_of_range("Index out of range");
	}

	Node* current = _head->next;
	for (int i = 0; i < index; i++)
	{
		current = current->next;
	}

	return current->data;
}

template<typename T>
T LinkedList<T>::operator[](const int index) const
{
	if (index < 0 || index >= _size)
	{
		throw out_of_range("Index out of range");
	}

	Node* current = _head->next;
	for (int i = 0; i < index; i++)
	{
		current = current->next;
	}

	return current->data;
}

