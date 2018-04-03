/*
Name:			Andrew Horn
Date:			1/31/2018
Last Modified:	2/2/2018
Course:			CST211 - Data Structures
Filename:		AbstractIterator.h

Overview:		Abstract base class for Iterator template. 
				Includes abstract functions for MoveNext, Reset, IsDone, and GetCurrent.
*/


#ifndef ABSTRACTITERATOR_H
#define ABSTRACTITERATOR_H

template<class T>
class AbstractIterator
{
public:
	virtual void MoveNext() = 0;
	virtual void Reset() = 0;
	virtual bool IsDone() = 0;
	virtual T& GetCurrent() = 0;
	virtual T& GetCurrent() const = 0;
};

#endif