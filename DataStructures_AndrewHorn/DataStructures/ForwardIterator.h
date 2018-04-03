/*
Name:			Andrew Horn
Date:			1/31/2018
Last Modified:	2/2/2018
Course:			CST211 - Data Structures
Filename:		ForwardIterator.h

Overview:		Provides full implementation for the Iterator template class. Begins at the FRONT of a DList and
				moves toward the END. 

Functions:		Reset (returns to FRONT/HEAD of list), IsDone (returns boolean, true: end of list has been reached), 
				MoveNext (moves to NEXT Node in list, if available), Assignment operator overload (sets Node pointer 
				equal to righthand-side Node pointer), Increment operator (++) overload (moves to NEXT Node in list, 
				if available).
*/

#ifndef FORWARDITERATOR_H
#define FORWARDITERATOR_H

#include "ListIterator.h"

template<class T>
class ForwardIterator : public ListIterator<T>
{
private:
public:
	void Reset() override;
	bool IsDone() override;
	void MoveNext() override;
	DLNode<T>* operator=(DLNode<T> * const rhs) override;
	ForwardIterator<T>& operator++(int);
};

template<class T>
inline void ForwardIterator<T>::Reset()
{
	while (this->getNodePtr()->getPrev())
		this->setNodePtr(this->getNodePtr()->getPrev());
	this->setDone(false);
}

template<class T>
inline bool ForwardIterator<T>::IsDone()
{
	return (!(this->getNodePtr()->hasNext()));
}

template<class T>
inline void ForwardIterator<T>::MoveNext()
{
	if (this->getNodePtr()->hasNext())
	{
		this->setNodePtr(this->getNodePtr()->getNext());
		this->setDone(false);
	}
	else
		this->setDone(true);
}

template<class T>
inline DLNode<T>* ForwardIterator<T>::operator=(DLNode<T> * const rhs)
{
	if (rhs != this->getNodePtr())
		this->setNodePtr(rhs);
	return this->getNodePtr();
}

template<class T>
inline ForwardIterator<T>& ForwardIterator<T>::operator++(int)
{
	ForwardIterator<T> *previous;
	previous = this;
	MoveNext();
	return *previous;
}

#endif