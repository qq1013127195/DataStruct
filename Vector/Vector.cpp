//
// Created by yang on 18-7-28.
//
#include <unordered_map>
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