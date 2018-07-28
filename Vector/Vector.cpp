//
// Created by yang on 18-7-28.
//
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
