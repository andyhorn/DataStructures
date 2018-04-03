/*
Name:			Andrew Horn
Date:			2/10/2018
Last Modified:	2/10/2018
Filename:		StackArray.h

Overview:		Implements a Stack using a static array. As of last modified date,
				all functionality tests pass. Elements are added from 0 index to end
				of array, removed from end of array down to 0 index.

Functions:		Parameter ctor (in: const int array size), copy ctor (in: const StackArray
				reference), dtor, Push (in: const data reference), Pop (out: data reference),
				Peek (out: data reference), Size (out: size of array), isEmpty (out: True if 
				array/stack is empty), isFull (out: True if array/stack is full).

Protected:		viewStack (out: const reference to member Array, used in copy ctor).
*/

#pragma once

#include "Array.h"
#include "Exception.h"

template<class T>
class StackArray
{
private:
	Array<T> _stack;
	size_t _size;
	size_t _stackIndex;
	const int getLength() const;
protected:
	const Array<T>& viewStack();
	const Array<T>& viewStack() const;
	const size_t getIndex();
	const size_t getIndex() const;
public:
	StackArray();
	StackArray(const int size);
	StackArray(const StackArray<T> &copy);
	~StackArray();
	void copyStack(const StackArray<T> &copy);
	StackArray<T>& operator=(const StackArray<T> &rhs);
	void Push(const T &data);
	T& Pop();
	T& Pop() const;
	const T& Peek();
	const T& Peek() const;
	int Size();
	int Size() const;
	const bool isEmpty();
	const bool isEmpty() const;
	const bool isFull();
	const bool isFull() const;
};

template<class T>
inline StackArray<T>::StackArray()
	: _stack(1), _size(1), _stackIndex(0)
{}

template<class T>
inline StackArray<T>::StackArray(const int size)
{
	_stack.setLength(size);
	_size = size;
	_stackIndex = 0;
}

template<class T>
inline StackArray<T>::StackArray(const StackArray<T> &copy)
{
	copyStack(copy);
}

template<class T>
inline StackArray<T>::~StackArray()
{
	_size = 0; 
	_stackIndex = 0;
}

template<class T>
inline const Array<T>& StackArray<T>::viewStack()
{
	return _stack;
}

template<class T>
inline const Array<T>& StackArray<T>::viewStack() const
{
	return _stack;
}

template<class T>
inline const size_t StackArray<T>::getIndex()
{
	return _stackIndex;
}

template<class T>
inline const size_t StackArray<T>::getIndex() const
{
	return _stackIndex;
}

template<class T>
inline void StackArray<T>::copyStack(const StackArray<T> &copy)
{
	if (this != &copy)
	{
		_size = copy.getLength();
		_stackIndex = copy.getIndex();
		_stack.setLength((int)_size);

		if (_size != 0)
			for (size_t i = 0; i < _size; i++)
				_stack[(int)i] = copy.viewStack()[(int)i];
	}
}

template<class T>
inline StackArray<T>& StackArray<T>::operator=(const StackArray<T> &rhs)
{
	copyStack(rhs);
	return *this;
}

template<class T>
inline void StackArray<T>::Push(const T &data)
{
	if (!isFull())
	{
		_stack[(int)_stackIndex++] = data;
	}
	else
		throw Exception("Exception: Stack Overflow!");
}

template<class T>
inline T& StackArray<T>::Pop()
{
	if (!isEmpty())
	{
		return _stack[(int)--_stackIndex];
	}
	else
		throw Exception("Exception: Stack Underflow!");
}

template<class T>
inline T& StackArray<T>::Pop() const
{
	if (!isEmpty())
	{
		return _stack[(int)--_stackIndex];
	}
	else
		throw Exception("Exception: Stack Underflow!");
}

template<class T>
inline const T& StackArray<T>::Peek()
{
	if (!isEmpty())
	{
		return _stack[(int)_stackIndex - 1];
	}
	else
		throw Exception("Exception: Stack Underflow!");
}

template<class T>
inline const T& StackArray<T>::Peek() const
{
	if (!isEmpty())
	{
		return _stack[(int)_stackIndex - 1];
	}
	else
		throw Exception("Exception: Stack Underflow!");
}

template<class T>
inline int StackArray<T>::Size()
{
	if (!isEmpty())
		return (int)_stackIndex - 1;
	else
		return 0;
}

template<class T>
inline int StackArray<T>::Size() const
{
	if (!isEmpty())
		return (int)_stackIndex - 1;
	else
		return 0;
}

template<class T>
inline const bool StackArray<T>::isEmpty()
{
	return (_stackIndex == 0);
}

template<class T>
inline const bool StackArray<T>::isEmpty() const
{
	return (_stackIndex == 0);
}

template<class T>
inline const bool StackArray<T>::isFull()
{
	return (_stackIndex == _size);
}

template<class T>
inline const bool StackArray<T>::isFull() const
{
	return (_stackIndex == _size);
}

template<class T>
inline const int StackArray<T>::getLength() const { return (int)_size; }