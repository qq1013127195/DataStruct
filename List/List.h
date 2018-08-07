//
// Created by yang on 18-8-2.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H

#include "ListNode.h"

template<typename T>
class List
{
private:
    int _size;
    ListNodePosi(T) header;
    ListNodePosi(T) trailer;

protected:
    void init();
    int clear();
    void copyNodes(ListNodePosi(T), int);
    void merge(ListNodePosi(T)&, int, List<T> &, ListNodePosi(T), int);
    void mergeSort(ListNodePosi(T)&, int);
    void selectionSort(ListNodePosi(T), int);
    void insertionSort(ListNodePosi(T), int);

public:
    List() { init(); }
    List(const List<T> &L);
    List(const List<T> &L, Rank r, int n);
    List(ListNodePosi(T) p, int n);

    ~List();

    Rank size() const { return _size; }
    bool empty() const { return _size <= 0; }
    T &operator[](Rank r) const;
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
    ListNodePosi(T) find(const T &e, int n, ListNodePosi(T) p) const;
    ListNodePosi(T) search(const T &e, int n, ListNodePosi(T) p) const;
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
    ListNodePosi(T) selectMax()
    {
        return selectMax(header->succ, _size);
    }

    ListNodePosi(T) insertAsFirst(const T &e);
    ListNodePosi(T) insertAsLast(const T &e);
    ListNodePosi(T) insertA(ListNodePosi(T) p, const T &e);//e as succ
    ListNodePosi(T) insertB(ListNodePosi(T) p, const T &e);//e as pred
    T remove(ListNodePosi(T) p);
    void merge(List<T> &l)
    {
        merge(first(), size(), l, l.first(), l._size);
    }
    void sort(ListNodePosi(T) p, int n);
    void sort() { sort(first(), _size); }
    int deduplicate();
    int uniquify();
    void reverse();

    void traverse(void (*)(T &));
    template <typename VST>
    void traverse(VST &);

};

#endif //LIST_LIST_H
