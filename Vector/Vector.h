//
// Created by yang on 18-7-28.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <cstdlib>
typedef int Rank; //秩
#define DEFAULT_CAPACITY 3 //默认的初始容量

template<class T>
class Vector //vector template class
{
protected:
	//规模 容量 数据区
	Rank _size;
	int _capacity;
	T *_elem;

	void copyFrom(T const *A, Rank lo, Rank hi)
	{
		_elem = new T[_capacity = 2 * (hi - lo)];
		_size = 0;
		while (lo < hi)
		{
			_elem[_size++] = A[lo++];
		}
	}

	void expand()
	{
		if (_size < _capacity)
			return;
		if (_capacity < DEFAULT_CAPACITY)
			_capacity = DEFAULT_CAPACITY;
		T *oldElem = _elem;
		_elem = new T[_capacity <<= 1];
		for (int i = 0; i < _size; i++)
			_elem[i] = oldElem[i];
		delete[] oldElem;
	}
	
	void shrink()
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
		delete[] oldElem;
	}
	//binSearch A
	/*template <class T>
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

	template <class T>
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
	template <class T>
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
	static Rank binSearch(T *A, const T &e, Rank lo, Rank hi)
	{
		while (lo < hi)
		{
			Rank mi = (lo + hi) >> 1;
			(e < A[mi]) ? hi = mi : lo = mi + 1;
		}
		return --lo;
	}

	bool bubble(Rank lo, Rank hi)//可改进，比如中间有有序的区间
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

	void bubbleSort(Rank lo, Rank hi)
	{
		while (!bubble(lo, hi--));
	}
	Rank max(Rank lo, Rank hi); //选取最大元素
	void selectionSort(Rank lo, Rank hi); //选择排序算法

	void merge(Rank lo, Rank mi, Rank hi)//可简化， C和A共用一块空间，也就是放C元素时候永远不会越界
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
		delete[] B;
	}

	void mergeSort(Rank lo, Rank hi)
	{
		if (hi - lo < 2)
			return;
		int mi = (lo + hi) >> 1;
		mergeSort(lo, mi);
		mergeSort(mi, hi);
		merge(lo, mi, hi);
	}
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
		delete[] _elem;
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

	int disordered() const
	{
		int n = 0;
		for (int i = 1; i < _size; i++)
			if (_elem[i - 1] > _elem[i])
				n++;
		return n;
	}

	Rank find(const T &e, Rank lo, Rank hi) const
	{
		while ((lo < hi--) && (e != _elem[hi]));
		return hi;
	}
	Rank find(const T &e) const //无序向量整体查找
	{
		return find(e, 0, _size);
	}

	Rank search(const T &e, Rank lo, Rank hi) const
	{
		return binSearch(_elem, e, lo, hi);
	}
	Rank search(const T &e) const //有序向量整体查找
	{
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}

	//可写访问接口

	T &operator[](Rank r) const
	{
		return _elem[r];
	}

	void swap(T &a, T &b)
	{
		T c = a;
		a = b;
		b = c;
	}

	void permute(Vector<T> &v)
	{
		for (int i = v.size(); i > 0; i--)
			swap(v[i - 1], v[rand() % i]);
	}

	Vector<T> &operator=(const Vector<T> &v)
	{
		if (_elem)
			delete[] _elem;
		copyFrom(v._elem, 0, v.size());
		return *this;
	}

	T remove(Rank r)
	{
		T e = _elem[r];
		remove(r, r + 1);
		return e;
	}

	int remove(Rank lo, Rank hi)
	{
		if (lo == hi)
			return 0;
		while (hi < _size)
			_elem[lo++] = _elem[hi++];
		_size = lo;
		shrink();
		return hi - lo;
	}

	Rank insert(Rank r, const T &e)
	{
		expand();
		for (int i = _size; i > r; i--)
			_elem[i] = _elem[i - 1];
		_elem[r] = e;
		return r;
	}
	Rank insert(T const &e) //默认作为末元素插入
	{
		return insert(_size, e);
	}

	void sort(Rank lo, Rank hi)//选 堆 快见后
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
	void sort() //整体排序
	{
		sort(0, _size);
	}

	void unsort(Rank lo, Rank hi)
	{
		T *v = _elem + lo;
		for (Rank i = hi - lo; i > 0; --i)
		{
			swap(v[i - 1], v[rand() % i]);
		}
	}
	void unsort() //整体置乱
	{
		unsort(0, _size);
	}

	int deduplicate()
	{
		int oldSize = _size;
		Rank i = 1;
		while (i < _size)
			(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
		return oldSize - _size;
	}

	int uniquify()
	{
		Rank i = 0, j = 0;
		while (++j < _size)
			if (_elem[i] != _elem[j])
				_elem[++i] = _elem[j];
		_size = ++i;
		shrink();
		return j - i;
	}

	void traverse(void(*visit)(T &))
	{
		for (int i = 0; i < _size; i++)
			visit(_elem[i]);
	}

	template <typename VST>
	void traverse(VST &visit)
	{
		for (int i = 0; i < _size; i++)
			visit(_elem[i]);
	}

}; //Vector

#endif //VECTOR_VECTOR_H
