#pragma once
#include "Sort.h"

using std::vector;

/* BUBBLE SORT */

template<class T>
class BubbleSort : public ISort<T>
{
private:

public:
	int Sort(T *sortArray, int length);
	int Sort(vector<T> &sortVector);
	int Sort(Array<T> &sortArray);
};

template<class T>
inline int BubbleSort<T>::Sort(T *sortArray, int length)
{
	int begin = GetTickCount(), end = 0;
	for (size_t pass = 0; pass < length; pass++)
	{
		for (size_t swap = 0; swap < length - 1; swap++)
		{
			if (sortArray[(int)swap] > sortArray[(int)swap + 1])
			{
				T temp = sortArray[(int)swap + 1];
				sortArray[(int)swap + 1] = sortArray[(int)swap];
				sortArray[(int)swap] = temp;
			}
		}
	}
	end = GetTickCount();
	return (end - begin);
}

template<class T>
inline int BubbleSort<T>::Sort(vector<T> &sortVector)
{
	int begin = GetTickCount(), end = 0;
	for (size_t pass = 0; pass < sortVector.size(); pass++)
	{
		for (size_t swap = 0; swap < sortVector.size() - 1; swap++)
		{
			if (sortVector[(int)swap] > sortVector[(int)swap + 1])
			{
				T temp = sortVector[(int)swap + 1];
				sortVector[(int)swap + 1] = sortVector[(int)swap];
				sortVector[(int)swap] = temp;
			}
		}
	}
	end = GetTickCount();
	return (end - begin);
}

template<class T>
inline int BubbleSort<T>::Sort(Array<T> &sortArray)
{
	int begin = GetTickCount(), end = 0;
	for (size_t pass = 0; pass < sortArray.getLength(); pass++)
	{
		for (size_t swap = 0; swap < sortArray.getLength() - 1; swap++)
		{
			if (sortArray[(int)swap] > sortArray[(int)swap + 1])
			{
				T temp = sortArray[(int)swap + 1];
				sortArray[(int)swap + 1] = sortArray[(int)swap];
				sortArray[(int)swap] = temp;
			}
		}
	}
	end = GetTickCount();
	return (end - begin);
}