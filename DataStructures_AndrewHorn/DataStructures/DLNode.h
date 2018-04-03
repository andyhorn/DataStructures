/*
Name:			Andrew Horn
Date:			1/31/2018
Last Modified:	2/2/2018
Course:			CST211 - Data Structures
Filname:		DLNode.h

Overview:		Template for a doubly-linked list Node class. The Node contains data and pointers to both the previous Node
				and the next Node. This class is used inside the DList class template.

Functions:		Functions include the standard, canonical methods:
				Default ctor, Copy ctor, Parameterized ctor, hasNext, hasPrev, getNext, getPrev,
				setNext, setPrev, setData, and getData.
*/


#ifndef DLNode_H
#define DLNode_H

template<class T>
class DLNode
{
private:
	T _data;
	DLNode *_next;
	DLNode *_prev;
public:
	DLNode();
	DLNode(const T &data, DLNode<T> *next = nullptr, DLNode<T> *prev = nullptr);
	DLNode(const DLNode &copy);
	bool hasNext();
	bool hasPrev();
	DLNode<T>* getNext();
	DLNode<T>* getNext() const;
	void setNext(DLNode<T> * const next);
	DLNode<T>* getPrev();
	DLNode<T>* getPrev() const;
	void setPrev(DLNode<T> * const prev);
	void setData(const T &data);
	T& getData();
	T& getData() const;
};

template<class T>
inline DLNode<T>::DLNode()
	: _data(), _next(nullptr), _prev(nullptr) {}

template<class T>
inline DLNode<T>::DLNode(const T &data, DLNode<T> *next, DLNode<T> *prev)
{
	_data = data;
	_next = next;
	_prev = prev;
}

template<class T>
inline DLNode<T>::DLNode(const DLNode &copy)
{
	_data = copy.getData();
	_next = copy.getNext();
	_prev = copy.getPrev();
}

template<class T>
inline bool DLNode<T>::hasNext()
{
	return (_next != nullptr);
}

template<class T>
inline bool DLNode<T>::hasPrev()
{
	return (_prev != nullptr);
}

template<class T>
inline DLNode<T>* DLNode<T>::getNext()
{
	return _next;
}

template<class T>
inline DLNode<T>* DLNode<T>::getNext() const
{
	return _next;
}

template<class T>
inline void DLNode<T>::setNext(DLNode<T> * const next)
{
	_next = next;
}

template<class T>
inline DLNode<T>* DLNode<T>::getPrev()
{
	return _prev;
}

template<class T>
inline DLNode<T>* DLNode<T>::getPrev() const
{
	return _prev;
}

template<class T>
inline void DLNode<T>::setPrev(DLNode<T> * const prev)
{
	_prev = prev;
}

template<class T>
inline void DLNode<T>::setData(const T &data)
{
	_data = data;
}

template<class T>
inline T& DLNode<T>::getData()
{
	return _data;
}

template<class T>
inline T& DLNode<T>::getData() const
{
	return _data;
}

#endif