//
// Created by yang on 18-8-2.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H

#include "ListNode.h"

template<class T>
class List
{
private:
	int _size;
	ListNodePosi(T) header;
	ListNodePosi(T) trailer;

protected:
	
	void init()
	{
		header = new ListNode<T>;
		trailer = new ListNode<T>;
		header->succ = trailer;
		header->pred = nullptr;
		trailer->pred = header;
		trailer->succ = nullptr;
		_size = 0;
	}
	
	int clear()
	{
		int oldSize = _size;
		while (0 < _size)
		{
			remove(header->succ);
		}

		return oldSize;
	}
	
	void copyNodes(ListNodePosi(T) p, int n)
	{
		init();
		while (n--)
		{
			insertAsLast(p->data);
			p = p->succ;
		}
	}
	
	void merge(ListNodePosi(T) &p, int n, List<T> &L, ListNodePosi(T) q, int m)
	{
		while (0 < m)
		{
			if ((0 < n) && (p->data <= q->data))
			{
				if (q == (p = p->succ))
					break;
				n--;
			}
			else
			{
				insertB(p, L.remove((q = q->succ)->pred));
				m--;
			}
		}
	}
	
	void mergeSort(ListNodePosi(T) &p, int n)
	{
		if (n < 2)
			return;
		int m = n >> 1;
		ListNodePosi(T) q = p;
		for (int i = 0; i < m; i++)
			q = q->succ;
		mergeSort(p, m);
		mergeSort(q, n - m);
		merge(p, m, *this, q, n - m);
	}
	
	void selectionSort(ListNodePosi(T) p, int n)
	{
		ListNodePosi(T) head = p->pred;
		ListNodePosi(T) tail = p;
		for (int i = 0; i < n; ++i)
			tail = tail->succ;
		while (1 < n)
		{
			ListNodePosi(T) max = selectMax(head->succ, n);
			insertB(tail, remove(max));
			tail = tail->pred;
			n--;
		}
	}
	
	void insertionSort(ListNodePosi(T) p, int n)
	{
		for (int r = 0; r < n; r++)
		{
			insertA(search(p->data), r, p);
			p = p->succ;
			remove(p->pred);
		}
	}

public:
	List() { init(); }
	
	List(const List<T> &L)
	{
		copyNodes(L.first(), L._size);
	}
	
	List(const List<T> &L, Rank r, int n)
	{
		copyNodes(L[r], n);
	}
	
	List(ListNodePosi(T) p, int n)
	{
		copyNodes(p, n);
	}

	
	~List()
	{
		clear();
		delete header;
		delete trailer;
	}

	Rank size() const { return _size; }
	bool empty() const { return _size <= 0; }
	
	T& operator[](Rank r) const
	{
		ListNodePosi(T) p = first();
		while (0 < r--)
		{
			p = p->succ;
		}
		return p->data;
	}
	ListNodePosi(T) first() const { return header->succ; }
	ListNodePosi(T) last() const { return trailer->pred; }
	bool valid(ListNodePosi(T) p)
	{
		return p && (trailer != p) && (header != p);
	}
	int disordered() const;
	ListNodePosi(T) find(const T &e) const
	{
		return find(e, _size, trailer);
	}
	
	ListNodePosi(T) find(const T &e, int n, ListNodePosi(T) p) const
	{
		while (0 < n--)
		{
			if (e == (p = p->pred)->data)
				return p;
		}
		return nullptr;
	}
	
	ListNodePosi(T) search(const T &e, int n, ListNodePosi(T) p) const
	{
		while (0 < n--)
			if (((p = p->pred)->data) <= e)
				break;
		return p;
	}
	
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n)
	{
		ListNodePosi(T) max = p;
		for (ListNodePosi(T) cur = p; 1 < n; n--)
			if (!it((cur = cur->succ)->data), max->data)//'it' not implement
				max = cur;

		return max;
	}
	ListNodePosi(T) selectMax()
	{
		return selectMax(header->succ, _size);
	}

	
	ListNodePosi(T) insertAsFirst(const T &e)
	{
		_size++;
		return header->insertAsSucc(e);
	}
	
	ListNodePosi(T) insertAsLast(const T &e)
	{
		_size++;
		return trailer->insertAsPred(e);
	}
	
	ListNodePosi(T) insertA(ListNodePosi(T) p, const T &e)
	{
		_size++;
		return p->insertAsSucc(e);
	}
	
	ListNodePosi(T) insertB(ListNodePosi(T) p, const T &e)
	{
		_size++;
		return p->insertAsPred(e);
	}
	
	T remove(ListNodePosi(T) p)
	{
		T e = p->data;
		p->pred->succ = p->succ;
		p->succ->pred = p->pred;
		delete p;
		_size--;
		return e;
	}
	void merge(List<T> &l)
	{
		merge(first(), size(), l, l.first(), l._size);
	}
	
	void sort(ListNodePosi(T) p, int n)
	{
		switch (rand() % 3)
		{
		case 1:
			insertionSort(p, n);
			break;
		case 2:
			selectionSort(p, n);
			break;
		default:
			mergeSort(p, n);
			break;
		}
	}
	void sort() { sort(first(), _size); }
	
	int deduplicate()
	{
		if (_size < 2)
			return 0;
		int oldSize = _size;
		ListNodePosi(T) p = header;
		Rank r = 0;
		while (trailer != (p = p->succ))
		{
			ListNodePosi(T) q = find(p->data, r, p);
			q ? remove(q) : r++;
		}
		return oldSize - _size;
	}
	
	int uniquify()
	{
		if (_size < 2)
			return 0;
		int oldSize = _size;
		ListNodePosi(T) p = first();
		ListNodePosi(T) q;
		while (trailer != (q = p->succ))
		{
			if (p->data != q->data)
				p = q;
			else
				remove(q);
		}
		return oldSize - _size;
	}
	void reverse();

	
	void traverse(void(*visit)(T &))
	{
		for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
			visit(p->data);
	}

	template <typename VST>
	void traverse(VST &visit)
	{
		for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
			visit(p->data);
	}

};

#endif //LIST_LIST_H
