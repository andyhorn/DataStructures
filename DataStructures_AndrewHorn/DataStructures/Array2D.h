/*
Name:			Andrew Horn
Date:			1/22/18
Course:			CST211 - Data Structures
Filename:		Array2D.h

Overview:		A two dimensional Array template class. Provides incorporated
				functionality along with a two dimensional array holding objects
				of any type. Works with the Row template class to provide dual
				subscript operator overloading to work as an actual 2D array.

Functions:		Default Ctor, parameter Ctor, Copy Ctor, Dtor, assignment operator,
				subscript operator, getRow, getColumn, setRow & setColumn (which both
				could result in data loss), Select (directly selects an object from 
				underlying Array object), and copyArray2D (which copies another Array2D
				object).

Exceptions:		Invalid parameters: Array(row, column)
				Out of bounds: operator[], Select()
				Negative length: setRow(), setColumn()
*/


#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <iostream>
#include "Exception.h"
#include "Array.h"
#include "Row.h"

template<class T>
class Row;

template<class T>
class Array2D
{
private:
	Array<T> m_array;
	int m_row;
	int m_col;
public:
	Array2D();
	Array2D(const int row, const int col);
	Array2D(const Array2D<T> &copy);
	~Array2D();

	Array2D<T>& operator=(const Array2D<T> &rhs);
	Row<T> operator[](const int index);
	Row<T> operator[](const int index) const;
	const int getRow();
	const int getRow() const;
	void setRow(const int rows);
	const int getColumn();
	const int getColumn() const;
	void setColumn(const int columns);
	T& Select(const int row, const int column);
	T& Select(const int row, const int column) const;
	void copyArray2D(const Array2D<T> &copy);
};

template<class T>
inline Array2D<T>::Array2D()
	: m_array(Array<T>()), m_row(0), m_col(0) {}

template<class T>
inline Array2D<T>::Array2D(const int row, const int col)
{
	if (row > 0 && col > 0)
	{
		m_array = Array<T>(row*col, 0);
		m_row = row;
		m_col = col;
	}
	else
		throw Exception("Error: Row and Column must be greater than 0.");
}

template<class T>
inline Array2D<T>::Array2D(const Array2D<T> &copy)
{
	copyArray2D(copy);
}

template<class T>
inline Array2D<T>::~Array2D()
{
	m_array = 0;
	m_row = 0;
	m_col = 0;
}

template<class T>
inline Array2D<T>& Array2D<T>::operator=(const Array2D<T> &rhs)
{
	copyArray2D(rhs);
	return *this;
}

template<class T>
inline Row<T> Array2D<T>::operator[](const int index)
{
	if (index > -1)
	{
		Row<T> row(*this, index);
		return row;
	}
	else
		throw Exception("Error: Index out of bounds");
}

template<class T>
inline Row<T> Array2D<T>::operator[](const int index) const
{
	if (index > -1)
	{
		Row<T> row(*this, index);
		return row;
	}
	else
		throw Exception("Error: Index out of bounds");
}

template<class T>
inline const int Array2D<T>::getRow()
{
	return m_row;
}

template<class T>
inline const int Array2D<T>::getRow() const
{
	return m_row;
}

template<class T>
inline void Array2D<T>::setRow(const int rows)
{
	if (rows < 0)
		throw Exception("Error: Row cannot be negative.");
	else if (rows == 0)
	{
		m_array.setLength(0);
		m_row = 0;
		m_col = 0;
	}
	else
	{
		m_array.setLength((rows * m_col));
		m_row = rows;
	}
}

template<class T>
inline const int Array2D<T>::getColumn()
{
	return m_col;
}

template<class T>
inline const int Array2D<T>::getColumn() const
{
	return m_col;
}

template<class T>
inline void Array2D<T>::setColumn(const int columns)
{
	if (columns < 0)
		throw Exception("Error: Column cannot be negative.");
	else if (columns == 0)
	{
		m_array.setLength(0);
		m_row = 0;
		m_col = 0;
	}
	else
	{
		Array<T> tempArray((m_row * columns), 0);
		int index = 0;
		for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j < columns && j < m_col; j++)
			{
				tempArray[index++] = m_array[(i * m_col) + j];
			}
		}
		m_col = columns;
		m_array = tempArray;
	}
}

template<class T>
inline T & Array2D<T>::Select(const int row, const int column)
{
	int index = 0;
	if (row >= 0 && column >= 0 && row < m_row && column < m_col)
		index = (row * m_col + column);
	else
		throw Exception("Error: Out of bounds");

	return m_array[index];
}

template<class T>
inline T& Array2D<T>::Select(const int row, const int column) const
{
	int index = 0;
	if (row >= 0 && column >= 0 && row < m_row && column < m_col)
		index = (row * m_col + column);
	else
		throw Exception("Error: Out of bounds");

	return m_array[index];
}

template<class T>
inline void Array2D<T>::copyArray2D(const Array2D<T> &copy)
{
	m_row = copy.getRow();
	m_col = copy.getColumn();
	m_array.setLength(m_row * m_col);

	int index = 0;
	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++)
			m_array[index++] = copy.Select(i, j);
}

#endif
