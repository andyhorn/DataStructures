/*
Name:			Andrew Horn
Date:			2/10/2018
Last Modified:	2/10/2018
Filename:		QueueArray.h

Overview:		Implements a Queue using a static array. As of last modified date, 
				all tests pass. All Enqueues cause the array elements to be shifted
				+1 index before new data can be added to the 0 index.

Functions:		Parameter ctor (in: array size), copy ctor (in: const QueueArray reference),
				dtor, Enqueue (in: const data reference), Dequeue (out: data copy), Front
				(out: copy reference), Size (out: const int - size of array), isEmpty (out:
				True if array/stack is empty), isFull (out: True if array/stack is full).

Protected:		viewStack (out: const reference to member Array, used in copy ctor),
				getIndex (out: const size_t, used in copy ctor).
*/

#pragma once

#include "Array.h"
#include "Exception.h"

template<class T>
class QueueArray
{
private:
	Array<T> _stack;
	size_t _size;
	size_t _topIndex;
	QueueArray();
	const int getLength() const;
protected:
	const Array<T>& viewStack();
	const Array<T>& viewStack() const;
	const size_t getIndex();
	const size_t getIndex() const;
public:
	QueueArray(const int size);
	QueueArray(const QueueArray<T> &copy);
	~QueueArray();

	void Enqueue(const T &data);
	T Dequeue();
	T Dequeue() const;
	T& Front();
	T& Front() const;
	const int Size();
	const int Size() const;
	const bool isEmpty();
	const bool isEmpty() const;
	const bool isFull();
	const bool isFull() const;
};

template<class T>
inline const Array<T>& QueueArray<T>::viewStack() 
{
	return _stack;
}

template<class T>
inline const Array<T>& QueueArray<T>::viewStack() const
{
	return _stack;
}

template<class T>
inline const size_t QueueArray<T>::getIndex()
{
	return _topIndex;
}

template<class T>
inline const size_t QueueArray<T>::getIndex() const
{
	return _topIndex;
}

template<class T>
inline QueueArray<T>::QueueArray()
	: _size(0), _topIndex(0) {}

template<class T>
inline QueueArray<T>::QueueArray(const int size)
{
	if (size > 0)
	{
		_stack.setLength(size);
		_size = size;
		_topIndex = 0;
	}
	else
		throw Exception("Exception: Invalid Size Parameter!");
}

template<class T>
inline QueueArray<T>::QueueArray(const QueueArray<T> &copy)
{
	if (this != &copy)
	{
		_size = copy.getLength();
		_stack.setLength((int)_size);
		_topIndex = copy.getIndex();

		for (size_t i = 0; i < _size; i++)
			_stack[(int)i] = copy.viewStack()[(int)i];
	}
}

template<class T>
inline QueueArray<T>::~QueueArray()
{
	_size = 0;
	_topIndex = 0;
}

template<class T>
inline void QueueArray<T>::Enqueue(const T &data)
{
	if (!isFull())
	{
		for (size_t i = _topIndex++; i > 0; i--)
			_stack[(int)i] = _stack[(int)(i - 1)];

		_stack[0] = data;
	}
	else
		throw Exception("Exception: Stack Overflow!");
}

template<class T>
inline T QueueArray<T>::Dequeue()
{
	if (!isEmpty())
		return _stack[(int)--_topIndex];
	else
		throw Exception("Exception: Stack Underflow!");
}

template<class T>
inline T QueueArray<T>::Dequeue() const
{
	if (!isEmpty())
		return _stack[(int)--_topIndex];
	else
		throw Exception("Exception: Stack Underflow!");
}

template<class T>
inline T& QueueArray<T>::Front()
{
	if (!isEmpty())
		return _stack[(int)(_topIndex - 1)];
	else
		throw Exception("Exception: Stack Underflow!");
}

template<class T>
inline T& QueueArray<T>::Front() const
{
	if (!isEmpty())
		return _stack[(int)(_topIndex - 1)];
	else
		throw Exception("Exception: Stack Underflow!");
}

template<class T>
inline const int QueueArray<T>::Size()
{
	if (!isEmpty())
		return (int)_topIndex - 1;
	else
		return 0;
}

template<class T>
inline const int QueueArray<T>::Size() const
{
	if (!isEmpty())
		return (int)_topIndex - 1;
	else
		return 0;
}

template<class T>
inline const bool QueueArray<T>::isEmpty()
{
	return _topIndex == 0;
}

template<class T>
inline const bool QueueArray<T>::isEmpty() const
{
	return _topIndex == 0;
}

template<class T>
inline const bool QueueArray<T>::isFull()
{
	return _topIndex == _size;
}

template<class T>
inline const bool QueueArray<T>::isFull() const
{
	return _topIndex == _size;
}

template<class T>
inline const int QueueArray<T>::getLength() const { return (int)_size; }