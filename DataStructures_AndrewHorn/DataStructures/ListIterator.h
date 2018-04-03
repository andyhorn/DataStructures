/*
Name:			Andrew Horn
Date:			1/31/2018
Last Modified:	2/2/2018
Course:			CST211 - Data Structures
Filename:		ListIterator.h

Overview:		Provides an implemented base class for an Iterator template class. Derives from the
				abstract class AbstractIterator. Contains a protected DLNode pointer and a protected boolean
				signaling when the end of a list has been reached.

Functions:		getNodePtr (returns _node pointer), setNodePtr (changes _node pointer), passes along virtual methods
				Reset, IsDone, and MoveNext, GetCurrent (returns current Node's data), Assignment operator overload, 
				Dereference operator overload (returns current Node's data).
*/


#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include "DLNode.h"
#include "DList.h"
#include "AbstractIterator.h"

template<class T>
class ListIterator : public AbstractIterator<T>
{
private:
	DLNode<T> * _node;
	bool _done;
public:
	DLNode<T>* getNodePtr();
	DLNode<T>* getNodePtr() const;
	void setNodePtr(DLNode<T> * const node);
	void setDone(const bool done);
	virtual void Reset() = 0;
	virtual bool IsDone() = 0;
	virtual void MoveNext() = 0;
	T& GetCurrent() override;
	T& GetCurrent() const override;
	virtual DLNode<T>* operator=(DLNode<T> * const rhs) = 0;
	T& operator*();
	T& operator*() const;
};

template<class T>
inline DLNode<T>* ListIterator<T>::getNodePtr()
{
	return _node;
}

template<class T>
inline DLNode<T>* ListIterator<T>::getNodePtr() const
{
	return _node;
}

template<class T>
inline void ListIterator<T>::setNodePtr(DLNode<T> * const node)
{
	_node = node;
}

template<class T>
inline void ListIterator<T>::setDone(const bool done)
{
	_done = done;
}

template<class T>
inline T& ListIterator<T>::GetCurrent()
{
	return _node->getData();
}

template<class T>
inline T& ListIterator<T>::GetCurrent() const
{
	return _node->getData();
}

template<class T>
inline T& ListIterator<T>::operator*()
{
	return _node->getData();
}

template<class T>
inline T& ListIterator<T>::operator*() const
{
	return _node->getData();
}

#endif