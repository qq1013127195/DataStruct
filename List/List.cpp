//
// Created by yang on 18-8-6.
//

#include <cstdlib>
#include "List.h"

template <typename T>
void List<T>::init()
{
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    header->pred = nullptr;
    trailer->pred = header;
    trailer->succ = nullptr;
    _size = 0;
}

template <typename T>
T& List<T>::operator[](Rank r) const
{
    ListNodePosi(T) p = first();
    while (0 < r--)
    {
        p = p->succ;
    }
    return p->data;
}

template <typename T>
ListNode<T> * List<T>::find(const T &e, int n, ListNode<T> *p) const
{
    while (0 < n--)
    {
        if (e == (p = p->pred)->data)
            return p;
    }
    return nullptr;
}

template <typename T>
ListNode<T> * List<T>::insertAsFirst(const T &e)
{
    _size++;
    return header->insertAsSucc(e);
}

template <typename T>
ListNode<T> * List<T>::insertAsLast(const T &e)
{
    _size++;
    return trailer->insertAsPred(e);
}

template <typename T>
ListNode<T> * List<T>::insertA(ListNode<T> *p, const T &e)
{
    _size++;
    return p->insertAsSucc(e);
}

template <typename T>
ListNode<T> * List<T>::insertB(ListNode<T> *p, const T &e)
{
    _size++;
    return p->insertAsPred(e);
}

template <typename T>
void List<T>::copyNodes(ListNode<T> *p, int n)
{
    init();
    while (n--)
    {
        insertAsLast(p->data);
        p = p->succ;
    }
}

template <typename T>
List<T>::List(ListNode<T> *p, int n)
{
    copyNodes(p, n);
}

template <typename T>
List<T>::List(const List<T> &L)
{
    copyNodes(L.first(), L._size);
}

template <typename T>
List<T>::List(const List<T> &L, Rank r, int n)
{
    copyNodes(L[r], n);
}

template <typename T>
T List<T>::remove(ListNode<T> *p)
{
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}

template <typename T>
List<T>::~List()
{
    clear();
    delete header;
    delete trailer;
}

template <typename T>
int List<T>::clear()
{
    int oldSize = _size;
    while (0 < _size)
    {
        remove(header->succ);
    }

    return oldSize;
}

template <typename T>
int List<T>::deduplicate()
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

template <typename T>
void List<T>::traverse(void (*visit)(T &))
{
    for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
        visit(p->data);
}

template <typename T> template <typename VST>
void List<T>::traverse(VST &visit)
{
    for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
        visit(p->data);
}

template <typename T>
int List<T>::uniquify()
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

template <typename T>
ListNode<T> * List<T>::search(const T &e, int n, ListNode<T> *p) const
{
    while (0 < n--)
        if (((p = p->pred)->data) <= e)
            break;
    return p;
}

template <typename T>
void List<T>::sort(ListNode<T> *p, int n)
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

template <typename T>
void List<T>::insertionSort(ListNode<T> *p, int n)
{
    for (int r = 0; r < n; r++)
    {
        insertA(search(p->data), r, p);
        p = p->succ;
        remove(p->pred);
    }
}

template <typename T>
void List<T>::selectionSort(ListNode<T> *p, int n)
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

template <typename T>
ListNode<T> * List<T>::selectMax(ListNode<T> *p, int n)
{
    ListNodePosi(T) max = p;
    for (ListNodePosi(T) cur = p; 1 < n; n--)
        if (!it((cur = cur->succ)->data), max->data)//'it' not implement
            max = cur;

    return max;
}

template <typename T>
void List<T>::merge(ListNode<T> *&p, int n, List<T> &L, ListNode<T> *q, int m)
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

template <typename T>
void List<T>::mergeSort(ListNode<T> *&p, int n)
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