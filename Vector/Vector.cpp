//
// Created by yang on 18-7-28.
//
#include <cstdlib>
#include "Vector.h"

template <typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi)
{
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi)
    {
        _elem[_size++] = A[lo++];
    }
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &v)
{
    if (_elem)
        delete [] _elem;
    copyFrom(v._elem, 0, v.size());
    return *this;
}

template <typename T>
void Vector<T>::expand()
{
    if (_size < _capacity)
        return;
    if (_capacity < DEFAULT_CAPACITY)
        _capacity = DEFAULT_CAPACITY;
    T *oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete [] oldElem;
}

template <typename T>
void Vector<T>::shrink()
{
    if (_capacity < DEFAULT_CAPACITY << 1)
        return;
    if (_size << 2 > _capacity)
        return;
    T *oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; i++)
    {
        _elem[i] == oldElem[i];
    }
    delete [] oldElem;
}

template <typename T>
T &Vector<T>::operator[](Rank r) const
{
    return _elem[r];
}

template <typename T>
void swap(T &a, T &b)
{
    T c = a;
    a = b;
    b = c;
}

template <typename T>
void permute(Vector<T> &v)
{
    for (int i = v.size(); i > 0; i--)
        swap(v[i - 1], v[rand() % i]);
}

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
    T *v = _elem + lo;
    for (Rank i = hi - lo; i > 0; --i)
    {
        swap(v[i - 1], v[rand() % i]);
    }
}

template <typename T>
Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const
{
    while ((lo < hi--) && (e != _elem[hi]));
    return hi;
}

template <typename T>
Rank Vector<T>::insert(Rank r, const T &e)
{
    expand();
    for (int i = _size; i > r; i--)
        _elem[i] = _elem[i - 1];
    _elem[r] = e;
    return r;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
    if (lo == hi)
        return 0;
    while (hi < _size)
        _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink();
    return hi - lo;
}

template <typename T>
T Vector<T>::remove(Rank r)
{
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

template <typename T>
int Vector<T>::deduplicate()
{
    int oldSize = _size;
    Rank i = 1;
    while (i < _size)
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
    return oldSize - _size;
}

template <typename T>
void Vector<T>::traverse(void (*visit)(T &))
{
    for (int i = 0; i < _size; i++)
        visit(_elem[i]);
}

template <typename T> template <typename VST>
void Vector<T>::traverse(VST &visit)
{
    for (int i = 0; i < _size; i++)
        visit(_elem[i]);
}

template <typename T>
int Vector<T>::disordered() const
{
    int n = 0;
    for (int i = 1; i < _size; i++)
        if (_elem[i - 1] > _elem[i])
            n++;
    return n;
}

template <typename T>
int Vector<T>::uniquify()
{
    Rank i = 0, j = 0;
    while (++j < _size)
        if (_elem[i] != _elem[j])
            _elem[++i] = _elem[j];
    _size = ++i;
    shrink();
    return j - i;
}

//binSearch A
/*template <typename T>
static Rank binSearch(T *A, const T &e, Rank lo, Rank hi)
{
    while (lo < hi)
    {
        Rank mi = (lo + hi) >> 1;
        if (e < A[mi])
            hi = mi;
        else if (A[mi] < e)
            lo = mi + 1;
        else
            return mi;
    }
    return -1;
}*/

//fibSearch
/*#include "../fibonacci/Fib.h"

template <typename T>
static Rank fibSearch(T *A, const T &e, Rank lo, Rank hi)
{
    Fib fib(hi - lo);
    while (lo < hi)
    {
        while (hi - lo < fib.get())
            fib.prev();
        Rank mi = lo + fib.get() - 1;
        if (e < A[mi])
            hi = mi;
        else if (A[mi] < e)
            lo = mi + 1;
        else
            return mi;
    }
    return -1
}*/

//binSearch B
/*
template <typename T>
static Rank binSearch(T *A, const T &e, Rank lo, Rank hi)
{
    while (1 < hi - lo)
    {
        Rank mi = (lo + hi) >> 1;
        (e < A[mi]) ? hi = mi : lo = mi;
    }
    return (e == A[lo]) ? lo : -1;
}
*/

//binSearch C
template <typename T>
static Rank binSearch(T *A, const T &e, Rank lo, Rank hi)
{
    while (lo < hi)
    {
        Rank mi = (lo + hi) >> 1;
        (e < A[mi]) ? hi = mi : lo = mi + 1;
    }
    return --lo;
}

template <typename T>
Rank Vector<T>::search(const T &e, Rank lo, Rank hi) const
{
    return binSearch(_elem, e, lo, hi);
}

template <typename T>
void Vector<T>::sort(Rank lo, Rank hi)//选 堆 快见后
{
    switch (rand() % 5)
    {
        case 1:
            bubbleSort(lo, hi);
            break;
        case 2:
            selectionSort(lo, hi);
            break;
        case 3:
            mergeSort(lo, hi);
            break;
        case 4:
            heapSort(lo, hi);
            break;
        default:
            quickSort(lo, hi);
            break;
    }
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
    while (!bubble(lo, hi--));
}

template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi)//可改进，比如中间有有序的区间
{
    bool sorted = true;
    while (++lo < hi)
    {
        if (_elem[lo - 1] > _elem[lo])
        {
            sorted = false;
            swap(_elem[lo - 1], _elem[lo]);
        }

    }
    return sorted;
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
    if (hi - lo < 2)
        return;
    int mi = (lo + hi) >> 1;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)//可简化， C和A共用一块空间，也就是放C元素时候永远不会越界
{
    T *A = _elem + lo;
    int lb = mi - lo;
    T *B = new T[lb];
    for (Rank i = 0; i < lb; B[i] = A[i++]);
    int lc = hi - mi;
    T *C = _elem + mi;
    for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc); )
    {
        if ((j < lb) && (!(k < lc) || (B[j] < C[k])))
            A[i++] = B[j++];
        if ((k < lc) && (!(j < lb) || (C[k] > B[j])))
            A[i++] = C[k++];
    }
    delete [] B;
}