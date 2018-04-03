/*
Name:			Andrew Horn
Date:			1/31/2018
Last Modified:	2/2/2018
Course:			CST211 - Data Structures
Filename:		BackwardIterator.h

Overview:		Provides full implementation for the Iterator template class. Begins at the END of a DList
				and moves backward, ending at the FRONT of the list. 

Functions:		Reset (returns to END/TAIL of list), IsDone (returns boolean, true: BEGINNING of list has 
				been reached), MoveNext (moves to PREVIOUS Node), Assignment operator overload (sets Node 
				pointer equal to righthand-side Node pointer), increment operator (++) overload (moves to 
				PREVIOUS Node).
*/

#ifndef BACKWARDITERATOR_H
#define BACKWARDITERATOR_H

#include "ListIterator.h"

template<class T>
class BackwardIterator : public ListIterator<T>
{
private:
public:
	void Reset();
	bool IsDone();
	void MoveNext();
	DLNode<T>* operator=(DLNode<T> * const rhs) override;
	BackwardIterator<T>& operator++(int);
};

template<class T>
inline void BackwardIterator<T>::Reset()
{
	while (this->getNodePtr()->hasNext())
		this->setNodePtr(this->getNodePtr()->getNext());
	this->setDone(false);
}

template<class T>
inline bool BackwardIterator<T>::IsDone()
{
	return (!this->getNodePtr()->hasPrev());
}

template<class T>
inline void BackwardIterator<T>::MoveNext()
{
	if (this->getNodePtr()->hasPrev())
	{
		this->setNodePtr(this->getNodePtr()->getPrev());
		this->setDone(false);
	}
	else
		this->setDone(true);
}

template<class T>
inline DLNode<T>* BackwardIterator<T>::operator=(DLNode<T> * const rhs)
{
	if (rhs != this->getNodePtr())
		this->setNodePtr(rhs);
		
	return this->getNodePtr();
}

template<class T>
inline BackwardIterator<T>& BackwardIterator<T>::operator++(int) // int makes this a post-increment.
{
	if (this->getNodePtr()->hasPrev())
		MoveNext();
	return *this;
}

#endif