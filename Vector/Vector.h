//
// Created by yang on 18-7-28.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

typedef int Rank; //秩
#define DEFAULT_CAPACITY 3 //默认的初始容量

template<typename T>
class Vector //vector template class
{
protected:
    //规模 容量 数据区
    Rank _size;
    int _capacity;
    T *_elem;

    void copyFrom(T const *A, Rank lo, Rank hi); //复制数组区间A[lo, hi)
    void expand(); // 空间不足时扩容
    void shrink(); // 装填因子过小时压缩
    bool bubble(Rank lo, Rank hi); //扫描交换
    void bubbleSort(Rank lo, Rank hi); //冒泡排序算法
    Rank max(Rank lo, Rank hi); //选取最大元素
    void selectionSort(Rank lo, Rank hi); //选择排序算法
    void merge(Rank lo, Rank mi, Rank hi); //归并算法
    void mergeSort(Rank lo, Rank hi); //归并排序算法
    Rank partition(Rank lo, Rank hi); //轴点构造算法
    void quickSort(Rank lo, Rank hi); //快速排序算法
    void heapSort(Rank lo, Rank hi); //堆排序

public:
    //构造函数
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
    { //容量为c 规模为s 所有元素初始为v
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v); //s<=c
    }
    Vector(T const *A, Rank n)
    {
        copyFrom(A, 0, n);
    }
    Vector(T const *A, Rank lo, Rank hi)
    {
        copyFrom(A, lo, hi);
    }
    Vector(const Vector<T> &V)
    {
        copyFrom(V._elem, 0, V._size);
    }
    Vector(const Vector<T> &V, Rank lo, Rank hi)
    {
        copyFrom(V._elem, lo, hi);
    }

    //析构函数
    ~Vector()
    {
        delete [] _elem;
    }

    //只读访问接口
    Rank size() const //规模
    {
        return _size;
    }
    bool empty() const //判空
    {
        return !_size;
    }
    int disordered() const; //判断向量是否已排序
    Rank find(const T &e, Rank lo, Rank hi) const; //无序向量区间查找
    Rank find(const T &e) const //无序向量整体查找
    {
        return find(e, 0, _size);
    }
    Rank search(const T &e, Rank lo, Rank hi) const; //有序向量区间查找
    Rank search(const T &e) const //有序向量整体查找
    {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }

    //可写访问接口
    T &operator[](Rank r) const;
    Vector<T> &operator=(const Vector<T> &);
    T remove(Rank r); //删除秩为r的元素
    int remove(Rank lo, Rank hi); //删除秩在区间[lo, hi)之内的元素
    Rank insert(Rank r, const T &e); //插入元素
    Rank insert(T const &e) //默认作为末元素插入
    {
        return insert(_size, e);
    }
    void sort(Rank lo, Rank hi); //对[lo. hi)排序
    void sort() //整体排序
    {
        sort(0, _size);
    }
    void unsort(Rank lo, Rank hi); //对[lo, hi)置乱
    void unsort() //整体置乱
    {
        unsort(0, _size);
    }
    int deduplicate(); //无序去重
    int uniquify(); //有序去重

    //遍历
    void traverse(void (*)(T&)); //遍历（使用函数指针, 只读或局部性修改）
    template <typename VST> void traverse(VST&); //遍历（使用函数对象, 可全局性修改）

}; //Vector

#endif //VECTOR_VECTOR_H
