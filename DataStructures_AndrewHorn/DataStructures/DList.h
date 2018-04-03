/*
Name:			Andrew Horn
Date:			1/31/2018
Course:			CST211 - Data Structures
Filename:		DList.h

Overview:		Class template for a doubly-linked list. the DList class contains two DLNode pointers, one for the HEAD
				of the list and one for the TAIL of the list. Also contains a private method which copies another DList
				object.

Functions:		Default ctor, Copy ctor, Dtor, Assignment operator overload (copies right-hand side DList object), 
				isEmpty, Last (returns data from last Node), First (returns data from first Node), getHead (returns 
				pointer to HEAD of list), getTail (returns pointer to TAIL of list), Append (appends new Node to 
				end of list), Prepend (adds new Node to front of list), Purge (deletes all data contained in list), 
				Extract (removes, but does not return, a specified data object), InsertAfter (inserts a new Node 
				directly after a specified Node), InsertBefore (inserts a new Node directly before a specified Node).

Exceptions:		"Null Value":		Last()
									First()
				"Unable to Insert":	InsertBefore()
									InsertAfter()
*/

#ifndef DLIST_H
#define DLIST_H

#include "DLNode.h"
#include "Exception.h"

template<class T>
class DList
{
private:
	DLNode<T> *_head;
	DLNode<T> *_tail;
	void copyList(const DList<T> &copy);
public:
	DList();
	DList(const DList<T> &copy);
	~DList();

	DList<T> &operator=(const DList<T> &rhs);

	bool isEmpty();
	bool isEmpty() const;
	const T& Last();
	const T& Last() const;
	const T& First();
	const T& First() const;
	DLNode<T>* getHead();
	DLNode<T>* getHead() const;
	DLNode<T>* getTail();
	DLNode<T>* getTail() const;
	void Append(const T &data);
	void Prepend(const T &data);
	void Purge();
	void Extract(const T &data);
	void InsertAfter(const T &data, const T &after);
	void InsertBefore(const T &data, const T &before);
};

template<class T>
inline DList<T>::DList()
	: _head(nullptr), _tail(nullptr) {}

template<class T>
inline DList<T>::DList(const DList<T> &copy)
{
	_head = nullptr;
	_tail = nullptr;
	copyList(copy);
}

template<class T>
inline DList<T>::~DList()
{
	Purge();
}

template<class T>
inline DList<T>& DList<T>::operator=(const DList<T> &rhs)
{
	copyList(rhs);
	return *this;
}

template<class T>
inline bool DList<T>::isEmpty()
{
	return (_head == nullptr && _tail == nullptr);
}

template<class T>
inline bool DList<T>::isEmpty() const
{
	return (_head == nullptr && _tail == nullptr);
}

template<class T>
inline const T& DList<T>::Last()
{
	if (!isEmpty())
		return _tail->getData();
	else
		throw Exception("Error: Null value.");
}

template<class T>
inline const T& DList<T>::Last() const
{
	if (!isEmpty())
		return _tail->getData();
	else
		throw Exception("Error: Null value.");
}

template<class T>
inline const T& DList<T>::First()
{
	if (!isEmpty())
		return _head->getData();
	else
		throw Exception("Error: Null value.");
}

template<class T>
inline const T& DList<T>::First() const
{
	if (!isEmpty())
		return _head->getData();
	else
		throw Exception("Error: Null value.");
}

template<class T>
inline DLNode<T>* DList<T>::getHead()
{
	return _head;
}

template<class T>
inline DLNode<T>* DList<T>::getHead() const
{
	return _head;
}

template<class T>
inline DLNode<T>* DList<T>::getTail()
{
	return _tail;
}

template<class T>
inline DLNode<T>* DList<T>::getTail() const
{
	return _tail;
}

template<class T>
inline void DList<T>::Append(const T &data)
{
	if (isEmpty())
	{
		_head = new DLNode<T>(data);
		_tail = _head;
	}
	else
	{
		DLNode<T> *newDLNode = new DLNode<T>(data);
		newDLNode->setPrev(_tail);
		_tail->setNext(newDLNode);
		_tail = newDLNode;
	}
}

template<class T>
inline void DList<T>::Prepend(const T &data)
{
	if (isEmpty())
	{
		_head = new DLNode<T>(data);
		_tail = _head;
	}
	else
	{
		DLNode<T> * temp = new DLNode<T>(data, _head);
		_head = temp;
		_head->getNext()->setPrev(_head);
	}
}

template<class T>
inline void DList<T>::Purge()
{
	if (!isEmpty())
	{
		DLNode<T> * temp = _head;
		while (temp->hasNext())
		{
			temp = temp->getNext();
			delete temp->getPrev();
		}
		delete temp;
	}
	_head = nullptr;
	_tail = nullptr;
}

template<class T>
inline void DList<T>::Extract(const T &data)
{
	if (!isEmpty())
	{
		bool found = false;
		DLNode<T> *temp = _head;
		while (temp != nullptr && found == false)
		{
			if (temp->getData() == data)
			{
				if (temp->hasNext() && temp->hasPrev()) // Somewhere in the middle
				{
					temp->getPrev()->setNext(temp->getNext());
					temp->getNext()->setPrev(temp->getPrev());
				}
				else if (temp->hasNext() && !temp->hasPrev()) // Head
				{
					_head = temp->getNext();
					_head->setPrev(nullptr);
				}
				else if (temp->hasPrev() && !temp->hasNext()) // Tail
				{
					_tail = temp->getPrev();
					_tail->setNext(nullptr);
				}
				else if (temp == _head && temp == _tail) // 1 item in list
				{
					_head = nullptr;
					_tail = nullptr;
					delete temp;
					break;
				}
				delete temp;
				found = true;
			}
			else
				temp = temp->getNext();
		}
	}
}

template<class T>
inline void DList<T>::InsertAfter(const T &data, const T &after)
{
	if (!isEmpty())
	{
		bool found = false;
		DLNode<T> *afterNode = _head;
		DLNode<T> *newDLNode = new DLNode<T>(data);
		while (afterNode != nullptr && found == false)
		{
			if (afterNode->getData() == after)
			{
				found = true;
				if (afterNode == _tail || (afterNode == _head && afterNode == _tail))
				{
					Append(data);
					found = true;
					delete newDLNode;
				}
				else if (afterNode == _head)
				{
					newDLNode->setNext(_head->getNext());
					newDLNode->setPrev(_head);
					if (_head->hasNext())
						newDLNode->getNext()->setPrev(newDLNode);
					_head->setNext(newDLNode);
				}
				else if (afterNode != _head && afterNode != _tail)
				{
					newDLNode->setNext(afterNode->getNext());
					newDLNode->setPrev(afterNode);
					afterNode->setNext(newDLNode);
					newDLNode->getNext()->setPrev(newDLNode);
				}
			}
			afterNode = afterNode->getNext();
		}
		if (found == false)
			throw Exception("Unable to insert, \"after\" case not found.");
	}
	else
	{
		_head = new DLNode<T>(data);
		_tail = _head;
	}
}

template<class T>
inline void DList<T>::InsertBefore(const T &data, const T &before)
{
	if (!isEmpty())
	{
		bool found = false;
		DLNode<T> *temp = _head;
		DLNode<T> *newDLNode = new DLNode<T>(data);
		while (temp != nullptr && found == false)
		{
			if (temp->getData() == before)
			{
				found = true;
				if (temp != _head && temp != _tail)
				{
					newDLNode->setPrev(temp->getPrev());
					newDLNode->setNext(temp);
					newDLNode->getPrev()->setNext(newDLNode);
					temp->setPrev(newDLNode);
				}
				else if (temp == _head)
				{
					newDLNode->setNext(_head);
					_head->setPrev(newDLNode);
					_head = newDLNode;
				}
				else if (temp == _tail)
				{
					newDLNode->setPrev(_tail->getPrev());
					newDLNode->setNext(_tail);
					newDLNode->getPrev()->setNext(newDLNode);
					_tail->setPrev(newDLNode);
				}
			}
			temp = temp->getNext();
		}
		if (found == false)
			throw Exception("Unable to insert, \"before\" case not found.");
	}
	else
	{
		_head = new DLNode<T>(data);
		_tail = _head;
	}
}

template<class T>
inline void DList<T>::copyList(const DList<T> &copy)
{
	if (!copy.isEmpty())
	{
		DLNode<T> *temp = copy.getHead();
		while (temp != nullptr)
		{
			Append(temp->getData());
			temp = temp->getNext();
		}
	}
}

#endif