//#include "linkedlist.h"
#include<iostream>
using namespace std;


/*
* ����һ������ģ���˫������LinkedList����ʵ�֡�
* ������ͷ�ڵ�ָ�롢�����С��һЩ�����Ĳ�������������롢�Ƴ����жϰ�������ȡ��С���������ȡ�
* ������֧������Ԫ�ص��������ͣ�������ʹ���±���������з��ʺ��޸ġ�
* ���⣬������������������������Խ������е�Ԫ����������С�
* ��Ҫ�ص�������ڵ�ṹ��������ݳ�Ա��ǰ��ָ�룬֧�ֳ�ʼ���б��캯����֧�ָ��ƹ��캯���͸�ֵ���ز�������
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
		Node* prev;  // ָ��ǰһ���ڵ��ָ��
		Node* next;  // ָ���һ���ڵ��ָ��
	};

	Node* _head;  // ͷ�ڵ�ָ��
	int _size;    // �����С
	void _copy(const LinkedList<T>& other);
public:
	LinkedList();//Ĭ�Ϲ��캯��
	~LinkedList();//��������
	LinkedList(const LinkedList<T>& other);//���ƹ��캯��
	LinkedList(std::initializer_list<T> initList);//�ó�ʼ���б��죬ʹ�ÿ����ô����ų�ʼ��
	LinkedList<T>& operator=(const LinkedList<T>other);//��ֵ����
	void insert(const T& ele);//ͷ��ֵ
	void remove(const T& ele);//�Ƴ�һ��Ԫ��
	bool contains(const T& ele) const;//�Ƿ����
	int size() const;//��С
	void clear();//��ղ����³�ʼ��
	T& get(const int index)const;
	T& operator[](const int index);//����[]��ʹ�ÿ������±��޸Ĳ�����
	T operator[](const int index) const;  //����[]��ʹ�ÿ���ֻ��ʱ���±����
	friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& lst)
	{
		// ������ʵ�������������������
		// ����ʹ��os��������е�Ԫ��
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
	}//�������
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
	Node* tmp = other._head->next; // ����ͷ�ڵ�
	Node* last = _head; // ����ǰһ���ڵ��ָ��

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
	//����ͷ�ڵ�
	_head = new Node;
	//��ʼ��ָ��ʹ�С
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
	_head = new Node; // ����ͷ�ڵ�
	_head->prev = nullptr;
	_head->next = nullptr;
	_size = 0;
	_copy(other);

}

template<typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> initList)
{
	//����ͷ�ڵ�
	_head = new Node;
	//��ʼ��ָ��ʹ�С
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
	// TODO: �ڴ˴����� return ���
}

//ͷ��
template<typename T>
void LinkedList<T>::insert(const T& ele)
{
	if (_head == nullptr)
	{
		cout << "List not initiated!\n";
		return;
	}
	Node *tmp_head = _head;//������ʱͷָ��ڵ�
	if (tmp_head->next == nullptr)//ֻ��һ��ͷ�ڵ�
	{
		Node* add = new Node;
		add->data = ele;//���ݸ�ֵ
		add->next = tmp_head->next;//�����ڵ����ָ������
		tmp_head->next = add;
		add->prev = tmp_head;//�����ڵ�ǰ��ָ������
		
	}
	else//����һ���ڵ�
	{
		Node* add = new Node;
		add->data = ele;//���ݸ�ֵ
		tmp_head->next->prev = add;//ͷ�ڵ�֮��ԭ���ڵ��ǰһ����Ϊ�����ڵ�
		add->prev = tmp_head;//�����ڵ�ǰ��ָ������
		add->next = tmp_head->next;//�����ڵ����ָ������
		tmp_head->next = add;//ͷ�ڵ�ĺ�һ�ڵ�ָ�������ڵ�
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
	Node* tmp_head = _head;//������ʱͷָ��ڵ�
	while (tmp_head->next!=NULL)
	{
		tmp_head = tmp_head->next;
		if (tmp_head->data == ele)//ɾ����һ������������ֵ
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
	Node* tmp_head = _head;//������ʱͷָ��ڵ�
	while (tmp_head->next != NULL)
	{
		tmp_head = tmp_head->next;
		if (tmp_head->data == ele)//ɾ����һ������������ֵ
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
	//����ͷ�ڵ�
	_head = new Node;
	//��ʼ��ָ��ʹ�С
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

