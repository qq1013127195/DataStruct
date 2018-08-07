//
// Created by yang on 18-8-6.
//

#include "ListNode.h"

template <typename T>
ListNode<T> * ListNode<T>::insertAsPred(const T &e)
{
    ListNodePosi(T) x = new ListNode(e, pred, this);
    pred->succ = x;
    pred = x;
    return x;
}

template <typename T>
ListNode<T> * ListNode<T>::insertAsSucc(const T &e)
{
    ListNodePosi(T) x = new ListNode(e, this, succ);
    succ->pred = x;
    succ = x;
}