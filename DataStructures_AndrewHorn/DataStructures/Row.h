/*
Name:			Andrew Horn
Date:			1/22/18
Course:			CST211 - Data Structures
Filename:		Row.h

Overview:		Row template class. Circular dependency with Array2D template class.
				This class allows the Array2D template to work with two subscript
				operators in conjunction. The first Array2D[] will return a Row object,
				which will work with the second [] to return a reference from the calling
				Array2D object's underlying Array object.
*/


#ifndef ROW_H
#define ROW_H

#include <iostream>
#include "Array2D.h"
#include "Array2DP.h"

template<class T>
class Array2D;

template<class T>
class Array2DP;

template<class T>
class Row
{
private:
	const Array2D<T> &m_array2D;
	int m_row;
public:
	Row(const Array2D<T> &inputArray, const int row);
	T& operator[](const int column);
	T& operator[](const int column) const;
};

template<class T>
inline Row<T>::Row(const Array2D<T> &inputArray, const int row)
	: m_array2D(inputArray), m_row(row) {}

template<class T>
inline T& Row<T>::operator[](const int column)
{
	return m_array2D.Select(m_row, column);
}

template<class T>
inline T& Row<T>::operator[](const int column) const
{
	return m_array2D.Select(m_row, column);
}

template<class T>
class RowP
{
private:
	const Array2DP<T>&m_array2DP;
	int m_row;
public:
	RowP(const Array2DP<T> &inputArray, const int row);
	T& operator[](const int column);
};

template<class T>
inline RowP<T>::RowP(const Array2DP<T> &inputArray, const int row)
	: m_array2DP(inputArray), m_row(row) {}

template<class T>
inline T& RowP<T>::operator[](const int column)
{
	return m_array2DP.Select(m_row, column);
}
#endif
