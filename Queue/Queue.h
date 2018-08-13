#pragma once
#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

#include "../List/List.h"
template<class T>
class Queue : public List<T>
{
public:
    Queue() : List<T>() {};
    void enqueue(const T e)
    {
        this->insertAsFirst(e);
    }
    T dequeue()
    {
        return this->remove(this->first());
    }
    T &front()
    {
        return this->first()->data;
    }
};

#endif
