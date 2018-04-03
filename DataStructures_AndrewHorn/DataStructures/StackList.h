/*
Name:			Andrew Horn
Date:			2/10/2018
Last Modified:	2/10/2018
Filename:		StackList.h

Overview:		Implements a Stack using a double-linked list. As of last modified
				date, all tests pass. New elements are Appended to the list, and 
				removed from the tail end.

Functions:		Default ctor, copy ctor (in: const StackList reference), dtor, 
				Push (in: const data reference), Pop (out: data copy), Peek (out:
				data reference), Size (out: current size of stack/list), isEmpty
				(out: True if stack/list has no elements).

Protected:		viewStack (out: const pointer to member stack List, used in copy ctor).
*/

#pragma once

#include "DList.h"
#include "Exception.h"
#include "BackwardIterator.h"
#include "ForwardIterator.h"

template<class T>
class StackList
{
private:
	DList<T> _stack;
	size_t _size;

protected:
	const DList<T>& viewStack();
	const DList<T>& viewStack() const;

public:
	StackList();
	StackList(const StackList<T> &copy);
	~StackList();

	void Push(const T &data);
	T Pop();
	T Pop() const;
	const T& Peek();
	const T& Peek() const;
	const int Size();
	const int Size() const;
	const bool isEmpty();
	const bool isEmpty() const;
};

template<class T>
inline const DList<T>& StackList<T>::viewStack() const
{
	return _stack;
}

template<class T>
inline const DList<T>& StackList<T>::viewStack()
{
	return _stack;
}

template<class T>
inline StackList<T>::StackList()
	: _size(0) {}

template<class T>
inline StackList<T>::StackList(const StackList<T> &copy)
{
	if (this != &copy)
	{
		ForwardIterator<T> iterator;
		iterator = copy.viewStack().getHead();

		while (!iterator.IsDone())
			_stack.Append(*iterator++);
		_stack.Append(*iterator);

		_size = copy.Size();
	}
}

template<class T>
inline StackList<T>::~StackList() 
{
	_stack.Purge();
	_size = 0;
}

template<class T>
inline void StackList<T>::Push(const T &data)
{
	_stack.Append(data);
	_size++;
}

template<class T>
inline T StackList<T>::Pop()
{
	if (!isEmpty())
	{
		T returnThis = _stack.getTail()->getData();
		_stack.Extract(returnThis);
		_size--;

		return returnThis;
	}
	else
		throw Exception("Exception: Stack Underflow!");
}

template<class T>
inline T StackList<T>::Pop() const
{
	if (!isEmpty())
	{
		T returnThis = _stack.getTail()->getData();
		_stack.Extract(returnThis);
		_size--;

		return returnThis;
	}
	else
		throw Exception("Exception: Stack Underflow!");
}

template<class T>
inline const T& StackList<T>::Peek()
{
	if (!isEmpty())
		return _stack.getTail()->getData();
	else
		throw Exception("Exception: Stack Underflow!");
}

template<class T>
inline const T& StackList<T>::Peek() const
{
	if (!isEmpty())
		return _stack.getTail()->getData();
	else
		throw Exception("Exception: Stack Underflow!");
}

template<class T>
inline const int StackList<T>::Size()
{
	return (int)_size;
}

template<class T>
inline const int StackList<T>::Size() const
{
	return (int)_size;
}

template<class T>
inline const bool StackList<T>::isEmpty()
{
	return _size == 0;
}

template<class T>
inline const bool StackList<T>::isEmpty() const
{
	return _size == 0;
}