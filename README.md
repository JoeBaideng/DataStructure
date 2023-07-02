# SeqList
SeqList
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