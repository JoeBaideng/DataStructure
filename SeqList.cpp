// SeqList.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<vector>
#include <functional>
#define DCAP 10 //默认容量
using namespace std;
template <typename T>
/*
SeqList类是一个动态数组的实现，可以存储任意类型的元素。它提供了一系列方法，例如插入、删除、访问、查找等操作。

该类使用模板实现，可以适用于不同类型的数据。它使用动态数组作为内部存储结构，初始容量为10，并且在需要时可以自动扩容。

SeqList类还实现了拷贝构造函数、赋值运算符重载和等于运算符重载，以方便对象的复制和比较。 --ChapGPT
*/

/*
* 注意：
* 1.使用了C++11特性for(auto:)、initializer_list
* 2.这里并没有进行严格的内存优化，尤其是remove()函数
*/
class SeqList
{
private:
    T* _p;
    int _size;
    int _capasity;
    //std::function<bool(const T&, const T&)>_campare_fun;
    void _extend();//扩容
public:
    SeqList();//默认构造函数
    ~SeqList();//析构函数
    SeqList(const int cap);//根据大小进行初始化，分配好内存
    SeqList(const SeqList<T>& other); // 复制构造函数
    SeqList(std::initializer_list<T> initList);//用初始化列表构造，使得可以用大括号初始化
    SeqList<T>& operator=(const SeqList<T>& other); // 赋值运算符重载
    bool operator==(const SeqList<T>other)const;// 等于运算符重载
    int size() const;//返回有效元素个数
    int getCapasity() const;//返回总容量
    bool full() const;//判断容量是否用完
    bool isEmpty() const;//判断是否为空
    void clear();//清空并重新初始化
    void pushBack(const T& ele);//尾加
    void insert(const int index, const T& ele);//从中间插入
    void remove(const int index);//移除
    T& get(const int index)const;//访问一个元素
    SeqList<T> get(const int start, const int end);//产生并返回子列
    //SeqList<T> get(const SeqList<int>indexs);//产生并返回不连续子列
    T& operator[](const int index);//重载[]，使得可以用下标修改并访问
    T operator[](const int index) const;  //重载[]，使得可以只读时用下标访问
    int findIndex(const T& ele)const;//查找一个元素的位置，若没有则返回-2
    void reverse()const;//倒置
    void sort();//排序，使用快速排序实现
    void sort(bool (*compare)(const T, const T));//自定义排序方式
};
template<typename T>
ostream& operator<<(ostream& out, const SeqList<T> &lst)
{
    out << "[";
    for (int i = 0; i < lst.size(); i++)
    {
        if (i != lst.size() - 1)
        {
            out << lst[i] << ",";
        }
        else
        {
            out << lst[i];
        }
    }
    out << "]";
    return out;
}
//struct MyChar
//{
//    MyChar()
//    {
//        c = 'i';
//    };
//    MyChar(char t)
//    {
//        this->c = t;
//    }
//    char c;
//};
//ostream& operator<<(ostream& out, const MyChar& MC)
//{
//    out << MC.c;
//    return out;
//}
int main()
{
   // SeqList<char> lst;
   // for (int i = 0; i < 15; i++)
   // {
   //     lst.pushBack('a' + i);
   // }
   // SeqList<SeqList<char>>llst;
   // SeqList<char> lst2 =lst.get(2,5);
   // 
   // //lst.insert(3, 'v');
   // //lst.remove(3);
   ///* const SeqList<char>& clst = lst;*/
   // llst.pushBack(lst);
   // llst.pushBack(lst);
   // llst.pushBack(lst);
   // llst.pushBack(lst);
   // llst.insert(2, lst2);
   // llst.reverse();
   // //cout<<llst.findIndex(lst);
   // //llst.remove(1);
   // cout << llst;
    SeqList<int>lst = { 2,8,4,6,11,3,1,5,88,32,12,9,15 };
    lst.sort([](const int a, const int b) { return a >= b; });
    lst.reverse();
    cout << lst<<endl;
    lst.sort();
    cout << lst << endl;
}
template<typename T>
void SeqList<T>::_extend()
{
    T* p_old = this->_p;
    this->_p = new T[2 * this->_capasity];//增加内存
    for (int i = 0; i < this->_size; i++) {
        this->_p[i] = p_old[i];  // 复制原有数据
    }
    this->_capasity *= 2;
    delete[] p_old;//释放临时内存
}
template<typename T>
SeqList<T>::SeqList()
{
    this->_p = new T[DCAP];
    this->_size = 0;
    this->_capasity = DCAP;
}

template<typename T>
SeqList<T>::~SeqList()
{
    if (this->_p != NULL)
        delete[] _p;
    this->_size = 0;
    this->_capasity = 0;
}
template<typename T>
SeqList<T>::SeqList(const int cap)
{
    this->_p = new T[cap];
    this->_size = 0;
    this->_capasity = cap;
}
template<typename T>
SeqList<T>::SeqList(const SeqList<T>& other)
{
    this->_size = other._size;
    this->_capasity = other._capasity;
    this->_p = new T[this->_capasity];
    for (int i = 0; i < this->_size; i++)
    {
        this->_p[i] = other._p[i];
    }
}
template<typename T>
SeqList<T>::SeqList(std::initializer_list<T> initList)
{
    this->_size = initList.size();
    this->_capasity = initList.size();
    this->_p = new T[this->_capasity];
    int i = 0;
    for (auto& ele : initList) {//initList不能用下标访问
        this->_p[i++] = ele;
    }
   /* for (int i = 0; i < this->_size; i++)
    {
        this->_p[i] = initList[i];
    }*/
}
template<typename T>
SeqList<T>& SeqList<T>::operator=(const SeqList<T>& other)
{
    if (this != &other)
    {
        delete[] this->_p;
        this->_size = other._size;
        this->_capasity = other._capasity;
        this->_p = new T[this->_capasity];
        for (int i = 0; i < this->_size; i++)
        {
            this->_p[i] = other._p[i];
        }
    }
    return *this;
}
template<typename T>
bool SeqList<T>::operator==(const SeqList<T>other)const//如果元素为结构体，需要重载该结构体的==
{
    if (this->_size != other.size())
        return false;
    for (int i = 0; i < this->_size; i++)
    {
        if(!(this->get(i) == other.get(i)))
            return false;
    }
    return true;
}
template<typename T>
int SeqList<T>::size() const
{
    return this->_size;
}

template<typename T>
int SeqList<T>::getCapasity() const
{
    return this->_capasity;
}

template<typename T>
bool SeqList<T>::full() const
{
    return this->_size==this->_capasity;
}

template<typename T>
bool SeqList<T>::isEmpty() const
{
    return this->_size == 0;
}

template<typename T>
void SeqList<T>::clear()
{
    if (this->_p != NULL)
        delete[] _p;
    this->_p = new T[DCAP];
    this->_size = 0;
    this->_capasity = DCAP;
}

template<typename T>
void SeqList<T>::pushBack(const T& ele)
{
    if (this->full())//已有内存用完
    {
        this->_extend();
    }
    *(this->_p+this->_size) = ele;
    this->_size++;//有效数据个数加一
    
}
template<typename T>
T& SeqList<T>:: operator[](const int index)
{
    if (index < 0 || index >= this->_size)
    {
        throw std::out_of_range("Index out of range");
    }
    else
    {
        return this->_p[index];
    }
}
template<typename T>
T SeqList<T>::operator[](const int index) const
{
    if (index < 0 || index >= this->_size)
    {
        throw std::out_of_range("Index out of range");
    }
    else
    {
        return this->_p[index];
    }
}
template<typename T>
void SeqList<T>::insert(const int index, const T& ele)
{
    if (index < 0 || index > this->_size)
    {
        throw std::out_of_range("Index out of range");
    }
    else
    {
        if (index == this->_size)//边界处理
        {
            pushBack(ele)
        }
        else
        {

            if (this->full())//已有内存用完
            {
                this->_extend();
            }
            T* p_old = this->_p;
            this->_size++;//有效数据个数加一
            for (int i = index + 1; i < this->_size; i++)
            {
                this->_p[i] = p_old[i - 1];
            }
            this->_p[index] = ele;
            //delete[] p_old;
        }
    }
    
}

template<typename T>
void SeqList<T>::remove(const int index)//只进行移除操作，未进行内存优化
{
    if (index < 0 || index >= this->_size)
    {
        throw std::out_of_range("Index out of range");
    }
    else
    {
        this -> _size--;
        for (int i = index; i < this->_size; i++)
        {
            this->_p[i] = this->_p[i + 1];
        }
    }

}

template<typename T>
T& SeqList<T>::get(const int index) const
{
    if (index < 0 || index >= this->_size)
    {
        throw std::out_of_range("Index out of range");
    }
    else
    {
        return this->_p[index];
    }
}
template<typename T>
SeqList<T> SeqList<T>::get(const int start, const int end)
{
    SeqList<T>res(end-start);
    if(start>end||start<0||end>=this->_size)
        throw std::out_of_range("Index out of range");
    for (int i = start; i < end + 1; i++)
    {
        res.pushBack(this->_p[i]);
    }
    return res;
}

template<typename T>
int SeqList<T>::findIndex(const T& ele) const//返回按顺序查找到的第一个符合条件元素的索引
{
    if (this->isEmpty())
    {
        return -2;
    }
    for (int i = 0; i < this->_size; i++)
    {
        if (this->_p[i] == ele)
            return i;
    }
    return -2;//未找到，返回-2
}

template<typename T>
//挨个拷贝进行倒置，避免自定义数据类型重载swap的麻烦
void SeqList<T>::reverse()const
{
    SeqList<T>old_lst(*this);
    for (int i=0;i<this->size();i++)
    {
        this->_p[this->size()-i-1] = old_lst[i];
    }
}
//交换函数，自定义数据类型使用时需要重载等号
template<typename T>
void Swap(T& a, T& b)
{
    T m=a;
    a = b;
    b = m;
}
template<typename T>
void quickSort(SeqList<T>& arr, int low, int high, bool (*compare)(const T, const T))
{
    if (low < high) {
        T pivot = arr[high];  // 选择最后一个元素作为基准
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (compare(arr[j], pivot)) {
                ++i;
                Swap(arr[i], arr[j]);
            }
        }

        Swap(arr[i + 1], arr[high]);

        int pivotIndex = i + 1;

        quickSort(arr, low, pivotIndex - 1,compare);
        quickSort(arr, pivotIndex + 1, high , compare);
    }
}
template<typename T>
bool ascend(const T  a, const T  b)
{
    return a <= b;
}
template<typename T>
void SeqList<T>::sort()
{
    quickSort(*this, 0, this->_size - 1, &ascend<T>);
}

template<typename T>
void SeqList<T>::sort(bool (*compare)(const T, const T))
{
    quickSort(*this, 0, this->_size - 1, compare);
}
