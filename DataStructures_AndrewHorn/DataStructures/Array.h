/*
Name:			Andrew Horn
Date:			1/21/18
Course:			CST211 - Data Structures
Filename:		Array.h

Overview:		An Array template class. Gives users the ability to create an Array<T> class with
				built-in functionality. Allows users to set array length and starting index at
				instantiation and on-the-fly. Changing length on the fly could result in data loss,
				but is still allowed. Includes exceptions when users try to access indices that are
				out of bounds, or when users try to set a negative length.

Functions:		Default ctor, 2 parameter ctors, copy ctor, dtor, assignment & subscript operator
				overloading, get and set for length and starting index.

Exceptions:		Out of bounds: operator[]
				Negative length: setLength(), Array(length, start_index)
*/

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include "Exception.h"

template<class T>
class Array
{
private:
	T *m_array;
	int m_length;
	int m_start_index;
public:
	Array();
	Array(int length, int start_index = 0);
	Array(const Array & copy);
	~Array();

	Array<T>& operator=(const Array &rhs);
	T& operator[](int index);
	T& operator[](int index) const;

	int getStartIndex();
	int getStartIndex() const;
	void setStartIndex(const int start_index);
	int getLength();
	int getLength() const;
	int getTrueIndex(const int request) const;
	void setLength(const int length);
};

template<class T>
inline Array<T>::Array()
{
	m_array = nullptr;
	m_length = 0;
	m_start_index = 0;
}

template<class T>
inline Array<T>::Array(const int length, const int start_index)
{
	try
	{
		if (length >= 0)
		{
			if (length > 0)
			{
				m_array = new T[length];
				m_length = length;
			}
			else
			{
				m_array = NULL;
				m_length = 0;
			}
			m_start_index = start_index;
		}
		else
		{
			throw Exception("Error: Negative length");
		}
	}
	catch (Exception &e)
	{
		e.print();
		throw e;
	}
}

template<class T>
inline Array<T>::Array(const Array &copy)
{
	m_length = copy.getLength();
	m_start_index = copy.getStartIndex();

	if (m_length > 0)
	{
		m_array = new T[m_length];
		for (int i = 0; i < m_length; i++)
			m_array[i] = copy[i];
	}
	else if (m_length == 0)
		m_array = NULL;
}

template<class T>
inline Array<T>::~Array()
{
	if (m_length > 0)
		delete[] m_array;
	else
		delete m_array;

	m_length = 0;
	m_start_index = 0;
}

template<class T>
inline Array<T>& Array<T>::operator=(const Array &rhs)
{
	if (m_length > 0)
		delete[] m_array;

	m_length = rhs.getLength();
	m_start_index = rhs.getStartIndex();

	if (m_length > 0)
		m_array = new T[m_length];
	else
		m_array = NULL;

	for (int i = 0; i < m_length; i++)
		m_array[i] = rhs[i];

	return *this;
}

template<class T>
inline T& Array<T>::operator[](const int index)
{
	try
	{
		return m_array[getTrueIndex(index)];
	}
	catch (Exception &e)
	{
		e.print();
		throw e;
	}
}

template<class T>
inline T& Array<T>::operator[](const int index) const
{
	try
	{
		return m_array[getTrueIndex(index)];
	}
	catch (Exception &e)
	{
		e.print();
		throw e;
	}
}

template<class T>
inline int Array<T>::getTrueIndex(const int request) const
{
	int true_index = 0;
	/***********************************************/
	if (m_start_index == 0)
	{
		if (request < 0 || request >= m_length)
		{
			throw Exception("Error: Out of bounds.");
		}
		else
		{
			true_index = request;
		}
	}
	/***********************************************/

	/***********************************************/
	// If start index is positive
	else if (m_start_index > 0)
	{
		if (request >= m_start_index)
			true_index = request - m_start_index;
		else
		{
			throw Exception("Out of bounds");
		}
	}
	/***********************************************/

	/***********************************************/
	// If start index is negative
	else if (m_start_index < 0)
	{
		if (request < m_start_index)
		{
			throw Exception("Out of bounds");
		}
		else
		{
			true_index = abs(m_start_index - request);
		}
	}
	/***********************************************/
	if (true_index < 0)
	{
		throw Exception("Out of bounds");
	}
	return true_index;
}

template<class T>
inline int Array<T>::getStartIndex()
{
	return m_start_index;
}

template<class T>
inline int Array<T>::getStartIndex() const
{
	return m_start_index;
}

template<class T>
inline void Array<T>::setStartIndex(const int start_index)
{
	m_start_index = start_index;
}

template<class T>
inline int Array<T>::getLength()
{
	return m_length;
}

template<class T>
inline int Array<T>::getLength() const
{
	return m_length;
}

template<class T>
inline void Array<T>::setLength(const int length)
{
	if (length > 0)
	{
		T *tempArray = new T[length];
		for (int i = 0; i < m_length && i < length; i++)
			tempArray[i] = m_array[i];

		if (m_length > 0)
			delete[] m_array;

		m_array = tempArray;
		m_length = length;
	}
	else if (length == 0)
	{
		if (m_length > 0)
			delete[] m_array;
		else
			delete m_array;

		m_length = length;
		m_array = NULL;
	}
	else
	{
		throw Exception("Error: Negative length.");
	}
}

#endif