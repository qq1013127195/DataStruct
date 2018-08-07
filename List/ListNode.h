//
// Created by yang on 18-8-2.
//

#ifndef LIST_LISTNODE_H
#define LIST_LISTNODE_H

typedef int Rank;
#define ListNodePosi(T) ListNode<T>*

template<typename T>
struct ListNode
{
    T data;
    ListNodePosi(T) pred;
    ListNodePosi(T) succ;

    ListNode() {}
    ListNode(T e, ListNodePosi(T)p = nullptr, ListNodePosi(T)s = nullptr)
            : data(e), pred(p), succ(s) {}
    ListNodePosi(T) insertAsPred(const T &e);
    ListNodePosi(T) insertAsSucc(const T &e);

};

#endif //LIST_LISTNODE_H
