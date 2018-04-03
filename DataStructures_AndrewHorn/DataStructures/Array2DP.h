#ifndef ARRAY2DP_H
#define ARRAY2DP_H

#include <iostream>
#include "Row.h"
#include "Array.h"
#include "Exception.h"

template<class T>
class RowP;

template<class T>
class Array2DP
{
private: 
	T **m_array;
	int m_row;
	int m_col;
	void copyArray(const Array2DP<T> &copy);
	void purgeData();
	void initializeData();
public:
	Array2DP();
	Array2DP(int row, int col);
	Array2DP(const Array2DP<T> &copy);
	~Array2DP();

	Array2DP<T> &operator=(const Array2DP<T> &rhs);
	RowP<T> operator[](int index);
	RowP<T> operator[](int index) const;

	const int getRow();
	const int getRow() const;
	void setRow(const int row);
	void setRow(const int row) const;
	const int getCol();
	const int getCol() const;
	void setCol(const int col);
	void setCol(const int col) const;

	T& Select(int row, int column);
	T& Select(int row, int column) const;
};

template<class T>
inline Array2DP<T>::Array2DP()
	: m_array(nullptr), m_row(0), m_col(0) {}

template<class T>
inline Array2DP<T>::Array2DP(int row, int col)
{
	if (row < 1 || col < 1)
		throw Exception("Error: Invalid value.");

	m_array = new T *[row * col];
	m_row = row;
	m_col = col;
	initializeData();
}

template<class T>
inline Array2DP<T>::Array2DP(const Array2DP<T> &copy)
{
	copyArray(copy);
}

template<class T>
inline Array2DP<T>::~Array2DP()
{
	purgeData();
	m_row = 0; 
	m_col = 0;
}

template<class T>
inline Array2DP<T>& Array2DP<T>::operator=(const Array2DP &rhs)
{
	copyArray(rhs);
	return *this;
}

template<class T>
inline RowP<T> Array2DP<T>::operator[](const int row)
{
	if (row > -1)
	{
		RowP<T> returnRow(*this, row);
		return returnRow;
	}
	else
		throw Exception("Error: Index out of bounds.");
}

template<class T>
inline RowP<T> Array2DP<T>::operator[](const int row) const
{
	if (index > -1)
	{
		RowP<T> row(*this, index);
		return row;
	}
	else
		throw Exception("Error: Index out of bounds.");
}

template<class T>
inline const int Array2DP<T>::getRow()
{
	return m_row;
}

template<class T>
inline const int Array2DP<T>::getRow() const
{
	return m_row;
}

template<class T>
inline void Array2DP<T>::setRow(const int rows)
{
	if (rows == 0)
	{
		m_row = 0;
		if (m_col != 0)
			purgeData();
	}
	else if (rows > 0)
	{
		if (m_col > 0)
		{
			T **tempArray = new T*[rows * m_col];
			for (int i = 0; i < rows * m_col; i++)
				tempArray[i] = new T;

			for (int index = 0; index < (rows * m_col) && index < (m_row * m_col); index++)
				*tempArray[index] = *m_array[index];

			purgeData();
			m_array = tempArray;
		}
		m_row = rows;
	}
	else
		throw Exception("Error: Invalid value.");
}

template<class T>
inline void Array2DP<T>::setRow(const int rows) const
{
	if (rows == 0)
	{
		m_row = 0;
		if (m_col != 0)
			purgeData();
	}
	else if (rows > 0)
	{
		if (m_col > 0)
		{
			T **tempArray = new T*[rows * m_col];
			for (int i = 0; i < rows * m_col; i++)
				tempArray[i] = new T;

			for (int index = 0; index < (rows * m_col) && index < (m_row * m_col); index++)
				*tempArray[index] = *m_array[index];

			purgeData();
			m_array = tempArray;
		}
		m_row = rows;
	}
	else
		throw Exception("Error: Invalid value.");
}

template<class T>
inline const int Array2DP<T>::getCol()
{
	return m_col;
}

template<class T>
inline const int Array2DP<T>::getCol() const
{
	return m_col;
}

template<class T>
inline void Array2DP<T>::setCol(const int col)
{
	if (col == 0)
	{
		m_col = col;
		if (m_row != 0)
			purgeData();
	}
	else if (col > 0)
	{
		if (m_row > 0)
		{
			T **tempArray = new T*[m_row * col];
			for (int i = 0; i < (m_row * col); i++)
				tempArray[i] = new T;

			for (int row = 0, index = 0; row < m_row; row++)
				for (int column = 0; column < col && column < m_col; column++)
					*tempArray[index++] = *m_array[(row * m_col) + column];

			purgeData();
			m_array = tempArray;
		}
		m_col = col;
	}
	else
		throw Exception("Error: Invalid value.");
}

template<class T>
inline void Array2DP<T>::setCol(const int col) const
{
	if (col == 0)
	{
		m_col = col;
		if (m_row != 0)
			purgeData();
	}
	else if (col > 0)
	{
		if (m_row > 0)
		{
			T **tempArray = new T*[m_row * col];
			for (int i = 0; i < (m_row * col); i++)
				tempArray[i] = new T;

			for (int row = 0, index = 0; row < m_row; row++)
				for (int column = 0; column < col && column < m_col; column++)
					*tempArray[index++] = *m_array[(row * m_col) + column];

			purgeData();
			m_array = tempArray;
		}
		m_col = col;
	}
	else
		throw Exception("Error: Invalid value.");
}

template<class T>
inline T& Array2DP<T>::Select(const int row, const int column)
{
	int index = 0;
	if (row >= 0 && column >= 0 && row < m_row && column < m_col)
		index = (row * m_col + column);
	else
		throw Exception("Error: Out of bounds.");

	return *m_array[index];
}

template<class T>
inline T& Array2DP<T>::Select(const int row, const int column) const
{
	int index = 0;
	if (row >= 0 && column >= 0 && row < m_row && column < m_col)
		index = (row * m_col + column);
	else
		throw Exception("Error: Out of bounds.");

	return *(m_array[index]);
}

template<class T>
inline void Array2DP<T>::copyArray(const Array2DP &copy)
{
	purgeData();
	m_row = copy.getRow();
	m_col = copy.getCol();
	m_array = new T*[m_row * m_col];
	initializeData();

	for (int row = 0, index = 0; row < m_row; row++)
		for (int col = 0; col < m_col; col++)
			*(m_array[index++]) = copy.Select(row, col);
}

template<class T>
inline void Array2DP<T>::purgeData()
{
	if (m_col > 0 && m_row > 0)
	{
		for (int i = 0; i < m_row * m_col; i++)
			delete m_array[i];
		delete m_array;
	}
}

template<class T>
inline void Array2DP<T>::initializeData()
{
	for (int i = 0; i < m_row * m_col; i++)
		m_array[i] = new T;
}
#endif