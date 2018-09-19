#pragma once
#ifndef STACK_STACK_H
#define STACK_STACK_H

#include "../Vector/Vector.h"

template <class T>
class Stack : public Vector<T>
{
public:
	Stack(int c = DEFAULT_CAPACITY, int s = 0, T v = NULL) : Vector<T>(c, s, v) {};

	void push(const T e)
	{
		this->insert(this->size(), e);
	}

	T pop()
	{
		return this->remove(this->size() - 1);
	}

	T& top()
	{
		return (*this)[this->size() - 1];
	}
};

#endif //STACK_STACK_H
