/*
Name:			Andrew Horn
Date:			2/10/2018
Last Modified:	2/10/2018
Filename:		QueueList.h

Overview:		Implements a Queue using a double-linked list. As of last modified date,
				all functionality tests pass. This queue appends all Enqueues and Dequeues
				from the tail end of the list.

Functions:		Default ctor, Copy ctor (in: const QueueList reference), dtor
				Enqueue (in: const data reference), Dequeue (out: data copy),
				Front(out: data reference), Size (out: const value of size of list),
				isEmpty (out: const bool True: List is empty, False: List is not empty).

Protected:		viewStack (out: const reference to member DList, used in copy ctor).
*/

#pragma once

#include "DList.h"
#include "Exception.h"
#include "ForwardIterator.h"

template<class T>
class QueueList
{
private:
	DList<T> _stack;
	size_t _size;
protected:
	const DList<T>& viewStack() const;
public:
	QueueList();
	QueueList(const QueueList<T> &copy);
	~QueueList();

	void Enqueue(const T &data);
	T Dequeue();
	T Dequeue() const;
	T& Front();
	T& Front() const;
	void Purge();
	const int Size();
	const int Size() const;
	const bool isEmpty();
	const bool isEmpty() const;
};

template<class T>
inline const DList<T>& QueueList<T>::viewStack() const
{
	return _stack;
}

template<class T>
inline QueueList<T>::QueueList()
	: _size(0) {}

template<class T>
inline QueueList<T>::QueueList(const QueueList<T> &copy)
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
inline QueueList<T>::~QueueList()
{
	_stack.Purge();
	_size = 0;
}

template<class T>
inline void QueueList<T>::Enqueue(const T &data)
{
	_stack.Prepend(data);
	_size++;
}

template<class T>
inline T QueueList<T>::Dequeue()
{
	if (!isEmpty())
	{
		T temp = _stack.getTail()->getData();
		_stack.Extract(temp);
		_size--;
		return temp;
	}
	else
		throw Exception("Exception: Stack Underflow!");
}

template<class T>
inline T QueueList<T>::Dequeue() const
{
	if (!isEmpty())
	{
		T temp = _stack.getTail()->getData();
		_stack.Extract(temp);
		_size--;
		return temp;
	}
	else
		throw Exception("Exception: Stack Underflow!");
}

template<class T>
inline T& QueueList<T>::Front()
{
	if (!isEmpty())
		return _stack.getTail()->getData();
	else
		throw Exception("Exception: Stack Underflow!");
}

template<class T>
inline T& QueueList<T>::Front() const
{
	if (!isEmpty())
		return _stack.getTail()->getData();
	else
		throw Exception("Exception: Stack Underflow!");
}

template<class T>
inline void QueueList<T>::Purge()
{
	if (!isEmpty())
	{
		_stack.Purge();
		_size = 0;
	}
}

template<class T>
inline const int QueueList<T>::Size()
{
	return static_cast<int>(_size);
}

template<class T>
inline const int QueueList<T>::Size() const
{
	return static_cast<int>(_size);
}

template<class T>
inline const bool QueueList<T>::isEmpty()
{
	return _size == 0;
}

template<class T>
inline const bool QueueList<T>::isEmpty() const
{
	return _size == 0;
}