#pragma once
#include <Windows.h>
#include "Array.h"
#include <vector>

using std::vector;

template<class T>
class ISort
{
private:
	const char* title_;
	ISort() = delete;
public:
	ISort(const char *title);
	~ISort();
	virtual int Sort();
	const char* GetTitle() const;
};

template<class T>
inline ISort<T>::ISort(const char *title) 
	: title_(title) {}

template<class T>
inline ISort<T>::~ISort() {}

template<class T>
inline int ISort<T>::Sort() { return 0; }

template<class T>
inline const char* ISort<T>::GetTitle() const { return title_; }

//template<class T>
//class ISortAlgo : public ISort<T>
//{
//private:
//	const char* title_;
//	ISortAlgo() = delete;
//public:
//	ISortAlgo(const char* title);
//	const char* GetTitle() const;
//};
//
//template<class T>
//inline ISortAlgo<T>::ISortAlgo(const char* title)
//	: title_(title) {}
//
//template<class T>
//inline const char* ISortAlgo<T>::GetTitle() const { return title_; }

/****************************************************/
/****************** BUBBLE SORT *********************/
/****************************************************/
template<class T>
class BubbleSort : public ISort<T>
{
public:
	BubbleSort();
	int Sort(T *arr, int length);
	int Sort(vector<T> &arr);
	int Sort(Array<T> &arr);
};

template<class T>
inline BubbleSort<T>::BubbleSort()
	: ISort("BubbleSort") {}

template<class T>
inline int BubbleSort<T>::Sort(T *arr, int length)
{
	int begin = GetTickCount(), end = 0;
	for (size_t pass = 0; pass < length; pass++)
	{
		for (size_t swap = 0; swap < length - 1; swap++)
		{
			if (arr[(int)swap] > arr[(int)swap + 1])
			{
				T temp = arr[(int)swap + 1];
				arr[(int)swap + 1] = arr[(int)swap];
				arr[(int)swap] = temp;
			}
		}
	}
	end = GetTickCount();
	return (end - begin);
}

template<class T>
inline int BubbleSort<T>::Sort(vector<T> &arr)
{
	int begin = GetTickCount(), end = 0;
	for (size_t pass = 0; pass < arr.size(); pass++)
	{
		for (size_t swap = 0; swap < arr.size() - 1; swap++)
		{
			if (arr[(int)swap] > arr[(int)swap + 1])
			{
				T temp = arr[(int)swap + 1];
				arr[(int)swap + 1] = arr[(int)swap];
				arr[(int)swap] = temp;
			}
		}
	}
	end = GetTickCount();
	return (end - begin);
}

template<class T>
inline int BubbleSort<T>::Sort(Array<T> &arr)
{
	int begin = GetTickCount(), end = 0;
	for (size_t pass = 0; pass < arr.getLength(); pass++)
	{
		for (size_t swap = 0; swap < arr.getLength() - 1; swap++)
		{
			if (arr[(int)swap] > arr[(int)swap + 1])
			{
				T temp = arr[(int)swap + 1];
				arr[(int)swap + 1] = arr[(int)swap];
				arr[(int)swap] = temp;
			}
		}
	}
	end = GetTickCount();
	return (end - begin);
}

/****************************************************/
/**************** FLAGGED BUBBLE SORT ***************/
/****************************************************/

template<class T>
class BubbleSortImproved : public ISort<T>
{
public:
	BubbleSortImproved();
	int Sort(T *arr, int length);
	int Sort(vector<T> &arr);
	int Sort(Array<T> &arr);
};

template<class T>
inline BubbleSortImproved<T>::BubbleSortImproved()
	: ISort("Improved Bubble Sort") {}

template<class T>
inline int BubbleSortImproved<T>::Sort(T *arr, int length)
{
	int begin = GetTickCount();
	bool sorted = false;
	for (size_t pass = 0; pass < length && !sorted; pass++)
	{
		sorted = true;
		for (size_t swap = 0; swap < length - 1; swap++)
		{
			if (arr[(int)swap] > arr[(int)swap + 1])
			{
				sorted = false;
				T temp = arr[(int)swap];
				arr[(int)swap] = arr[(int)swap + 1];
				arr[(int)swap + 1] = temp;
			}
		}
	}
	return GetTickCount() - begin;
}

template<class T>
inline int BubbleSortImproved<T>::Sort(vector<T> &arr)
{
	int begin = GetTickCount();
	bool sorted = false;
	for (size_t pass = 0; pass < arr.size() && !sorted; pass++)
	{
		sorted = true;
		for (size_t swap = 0; swap < arr.size() - 1; swap++)
		{
			if (arr[(int)swap] > arr[(int)swap + 1])
			{
				sorted = false;
				T temp = arr[(int)swap];
				arr[(int)swap] = arr[(int)swap + 1];
				arr[(int)swap + 1] = temp;
			}
		}
	}
	return (GetTickCount() - begin);
}

template<class T>
inline int BubbleSortImproved<T>::Sort(Array<T> &arr)
{
	int begin = GetTickCount();
	bool sorted = false;
	for (size_t pass = 0; pass < arr.getLength() && !sorted; pass++)
	{
		sorted = true;
		for (size_t swap = 0; swap < arr.getLength() - 1; swap++)
		{
			if (arr[(int)swap] > arr[(int)swap + 1])
			{
				sorted = false;
				T temp = arr[(int)swap];
				arr[(int)swap] = arr[(int)swap + 1];
				arr[(int)swap + 1] = temp;
			}
		}
		if (sorted) return GetTickCount() - begin;
	}
	return GetTickCount() - begin;
}
/****************************************************/
/***************** SELECTION SORT *******************/
/****************************************************/
template<class T>
class SelectionSort : public ISort<T>
{
public:
	SelectionSort();
	int Sort(T *arr, int length);
	int Sort(vector<T> &arr);
	int Sort(Array<T> &arr);
};

template<class T>
inline SelectionSort<T>::SelectionSort()
	: ISort("Selection Sort") {}

template<class T>
inline int SelectionSort<T>::Sort(T *arr, int length)
{
	int begin = GetTickCount();
	for (size_t last = length - 1; last > 0; last--)
	{
		int index = (int)last;
		for (size_t j = 0; j < last; j++)
			if (arr[(int)j] > arr[(int)index])
				index = (int)j;

		T temp = arr[(int)index];
		arr[(int)index] = arr[(int)last];
		arr[(int)last] = temp;
	}
	return (GetTickCount() - begin);
}

template<class T>
inline int SelectionSort<T>::Sort(vector<T> &arr)
{
	int begin = GetTickCount();
	for (size_t last = arr.size() - 1; last > 0; last--)
	{
		int index = (int)last;
		for (size_t j = 0; j < last; j++)
			if (arr[(int)j] > arr[(int)index])
				index = (int)j;

		T temp = arr[(int)index];
		arr[(int)index] = arr[(int)last];
		arr[(int)last] = temp;
	}
	return (GetTickCount() - begin);
}

template<class T>
inline int SelectionSort<T>::Sort(Array<T> &arr)
{
	int begin = GetTickCount();
	for (size_t last = arr.getLength() - 1; last > 0; last--)
	{
		int index = (int)last;
		for (size_t j = 0; j < last; j++)
			if (arr[(int)j] > arr[(int)index])
				index = (int)j;

		T temp = arr[(int)index];
		arr[(int)index] = arr[(int)last];
		arr[(int)last] = temp;
	}
	return (GetTickCount() - begin);
}
/****************************************************/
/**************** INSERTION SORT ********************/
/****************************************************/
template<class T>
class InsertionSort : public ISort<T>
{
public:
	InsertionSort();
	int Sort(T *arr, int length);
	int Sort(vector<T> &arr);
	int Sort(Array<T> &arr);
};

template<class T>
inline InsertionSort<T>::InsertionSort()
	: ISort("Insertion Sort") {}

template<class T>
inline int InsertionSort<T>::Sort(T *arr, int length)
{
	int begin = GetTickCount();
	for (size_t i = 1; i < length; i++)
	{
		T next = arr[(int)i];
		int prev;
		for (prev = (int)i - 1; prev >= 0 && arr[prev] > next; prev--)
			arr[prev + 1] = arr[prev];
		arr[prev + 1] = next;
	}
	return GetTickCount() - begin;
}

template<class T>
inline int InsertionSort<T>::Sort(Array<T> &arr)
{
	int begin = GetTickCount();
	for (size_t i = 1; i < arr.getLength(); i++)
	{
		T next = arr[(int)i];
		int prev;
		for (prev = (int)i - 1; prev >= 0 && arr[prev] > next; prev--)
			arr[prev + 1] = arr[prev];
		arr[prev + 1] = next;
	}
	return GetTickCount() - begin;
}

template<class T>
inline int InsertionSort<T>::Sort(vector<T> &arr)
{
	int begin = GetTickCount();
	for (size_t i = 1; i < arr.size(); i++)
	{
		T next = arr[(int)i];
		int prev;
		for (prev = (int)i - 1; prev >= 0 && arr[prev] > next; prev--)
			arr[prev + 1] = arr[prev];
		arr[prev + 1] = next;
	}
	return GetTickCount() - begin;
}
/****************************************************/
/******************** MERGE SORT ********************/
/****************************************************/
template<class T>
class MergeSort : public ISort<T>
{
private:
	void mergeSort(T *arr, int begin, int end);
	void merge(T *arr, int begin, int mid, int end);
	void mergeSort(vector<T> &arr, int begin, int end);
	void merge(vector<T> &arr, int begin, int mid, int end);
	void mergeSort(Array<T> &arr, int begin, int end);
	void merge(Array<T> &arr, int begin, int mid, int end);
public:
	MergeSort();
	int Sort(T *arr, int length);
	int Sort(vector<T> &arr);
	int Sort(Array<T> &arr);
};

template<class T>
inline MergeSort<T>::MergeSort()
	: ISort("Merge Sort") {}

template<class T>
inline int MergeSort<T>::Sort(T * arr, int length)
{
	int begin = GetTickCount();
	mergeSort(arr, 0, length);
	return GetTickCount() - begin;
}

template<class T>
inline int MergeSort<T>::Sort(vector<T>& arr)
{
	int begin = GetTickCount();
	mergeSort(arr, 0, (int)arr.size() - 1);
	return GetTickCount() - begin;
}

template<class T>
inline int MergeSort<T>::Sort(Array<T>& arr)
{
	int begin = GetTickCount();
	mergeSort(arr, 0, arr.getLength() - 1);
	return GetTickCount() - begin;
}

template<class T>
inline void MergeSort<T>::mergeSort(T *arr, int begin, int end)
{
	if (begin < end)
	{
		int mid = (begin + end) / 2;
		mergeSort(arr, begin, mid);
		mergeSort(arr, mid + 1, end);
		merge(arr, begin, mid, end);
	}
}

template<class T>
inline void MergeSort<T>::mergeSort(vector<T> &arr, int begin, int end)
{
	if (begin < end)
	{
		int mid = (begin + end) / 2;
		mergeSort(arr, begin, mid);
		mergeSort(arr, mid + 1, end);
		merge(arr, begin, mid, end);
	}
}

template<class T>
inline void MergeSort<T>::mergeSort(Array<T> &arr, int begin, int end)
{
	if (begin < end)
	{
		int mid = (begin + end) / 2;
		mergeSort(arr, begin, mid);
		mergeSort(arr, mid + 1, end);
		merge(arr, begin, mid, end);
	}
}

template<class T>
inline void MergeSort<T>::merge(T *arr, int begin, int mid, int end)
{
	T *temp = new T[end - begin + 1];
	
	int index = 0, left = begin, right = mid + 1;
	while (left <= mid && right <= end)
	{
		if (arr[left] <= arr[right])
			temp[index++] = arr[left++];
		else
			temp[index++] = arr[right++];
	}
	while (left <= mid)
		temp[index++] = arr[left++];
	while (right <= end)
		temp[index++] = arr[right++];

	for (size_t i = 0; i < (end - begin + 1); i++)
		arr[begin + (int)i] = temp[(int)i];

	delete[] temp;
}

template<class T>
inline void MergeSort<T>::merge(vector<T> &arr, int begin, int mid, int end)
{
	T *temp = new T[end - begin + 1];

	int index = 0, left = begin, right = mid + 1;
	while (left <= mid && right <= end)
	{
		if (arr[left] <= arr[right])
			temp[index++] = arr[left++];
		else
			temp[index++] = arr[right++];
	}
	while (left <= mid)
		temp[index++] = arr[left++];
	while (right <= end)
		temp[index++] = arr[right++];

	for (size_t i = 0; i < (end - begin + 1); i++)
		arr[begin + (int)i] = temp[(int)i];

	delete[] temp;
}

template<class T>
inline void MergeSort<T>::merge(Array<T> &arr, int begin, int mid, int end)
{
	T *temp = new T[end - begin + 1];

	int index = 0, left = begin, right = mid + 1;
	while (left <= mid && right <= end)
	{
		if (arr[left] <= arr[right])
			temp[index++] = arr[left++];
		else
			temp[index++] = arr[right++];
	}
	while (left <= mid)
		temp[index++] = arr[left++];
	while (right <= end)
		temp[index++] = arr[right++];

	for (size_t i = 0; i < (end - begin + 1); i++)
		arr[begin + (int)i] = temp[(int)i];

	delete[] temp;
}
/****************************************************/
/******************** QUICK SORT ********************/
/****************************************************/
template<class T>
class QuickSort : public ISort<T>
{
private:
	void partition(T *arr, int left, int right);
	void partition(Array<T> &arr, int left, int right);
	void partition(vector<T> &arr, int left, int right);
public:
	QuickSort();
	int Sort(T *arr, int length);
	int Sort(Array<T> &arr);
	int Sort(vector<T> &arr);
};

template<class T>
inline QuickSort<T>::QuickSort()
	: ISort("Quick Sort") {}

template<class T>
inline int QuickSort<T>::Sort(T *arr, int length)
{
	int begin = GetTickCount();
	partition(arr, 0, length - 1);
	return GetTickCount() - begin;
}

template<class T>
inline void QuickSort<T>::partition(T *arr, int left, int right)
{
	if (left < right)
	{
		int l = left, r = right, pivot = right;
		while (l < r)
		{
			// all elements > pivot on its right
			// all elements < pivot on its left
			// partition sub-arrays
			while (l < r && arr[l] < arr[pivot])
				l++;
			while (r > l && arr[r] >= arr[pivot])
				r--;
			if (l < r)
			{
				T temp = arr[r];
				arr[r] = arr[l];
				arr[l] = temp;
			}
		}
		// if left > right, swap left with pivot
		T temp = arr[l];
		arr[l] = arr[pivot];
		arr[pivot] = temp;
		pivot = l;

		partition(arr, left, pivot - 1);
		partition(arr, pivot + 1, right);
	}
}

template<class T>
inline int QuickSort<T>::Sort(Array<T> &arr)
{
	int begin = GetTickCount();
	partition(arr, 0, arr.getLength() - 1);
	return GetTickCount() - begin;
}

template<class T>
inline void QuickSort<T>::partition(Array<T> &arr, int left, int right)
{
	if (left < right)
	{
		int l = left, r = right, pivot = right;
		while (l < r)
		{
			// all elements > pivot on its right
			// all elements < pivot on its left
			// partition sub-arrays
			while (l < r && arr[l] < arr[pivot])
				l++;
			while (r > l && arr[r] >= arr[pivot])
				r--;
			if (l < r)
			{
				T temp = arr[r];
				arr[r] = arr[l];
				arr[l] = temp;
			}
		}
		// if left > right, swap left with pivot
		T temp = arr[l];
		arr[l] = arr[pivot];
		arr[pivot] = temp;
		pivot = l;

		partition(arr, left, pivot - 1);
		partition(arr, pivot + 1, right);
	}
}

template<class T>
inline int QuickSort<T>::Sort(vector<T> &arr)
{
	int begin = GetTickCount();
	partition(arr, 0, (int)arr.size() - 1);
	return GetTickCount() - begin;
}

template<class T>
inline void QuickSort<T>::partition(vector<T> &arr, int left, int right)
{
	if (left < right)
	{
		int l = left, r = right, pivot = right;
		while (l < r)
		{
			// all elements > pivot on its right
			// all elements < pivot on its left
			// partition sub-arrays
			while (l < r && arr[l] < arr[pivot])
				l++;
			while (r > l && arr[r] >= arr[pivot])
				r--;
			if (l < r)
			{
				T temp = arr[r];
				arr[r] = arr[l];
				arr[l] = temp;
			}
		}
		// if left > right, swap left with pivot
		T temp = arr[l];
		arr[l] = arr[pivot];
		arr[pivot] = temp;
		pivot = l;

		partition(arr, left, pivot - 1);
		partition(arr, pivot + 1, right);
	}
}
/****************************************************/
/******************** SHELL SORT ********************/
/****************************************************/
template<class T>
class ShellSort : public ISort<T>
{
public: 
	ShellSort();
	int Sort(T *arr, int length);
	int Sort(vector<T> &arr);
	int Sort(Array<T> &arr);
};

template<class T>
inline ShellSort<T>::ShellSort()
	: ISort("Shell Sort") {}

template<class T>
inline int ShellSort<T>::Sort(T *arr, int length)
{
	int begin = GetTickCount();
	for (size_t gap = length / 2; gap > 0; gap /= 2)
	{
		for (int num = (int)gap; num < length; num++)
		{
			T temp = arr[num];
			int check = num;
			for (; check >= (int)gap && arr[check - (int)gap] > temp; check -= (int)gap)
				arr[check] = arr[check - (int)gap];
			arr[check] = temp;
		}
	}
	return GetTickCount() - begin;
}

template<class T>
inline int ShellSort<T>::Sort(vector<T> &arr)
{
	int begin = GetTickCount();
	for (size_t gap = arr.size() / 2; gap > 0; gap /= 2)
	{
		for (int num = (int)gap; num < arr.size(); num++)
		{
			T temp = arr[num];
			int check = num;
			for (; check >= (int)gap && arr[check - (int)gap] > temp; check -= (int)gap)
				arr[check] = arr[check - (int)gap];
			arr[check] = temp;
		}
	}
	return GetTickCount() - begin;
}

template<class T>
inline int ShellSort<T>::Sort(Array<T> &arr)
{
	int begin = GetTickCount();
	for (size_t gap = arr.getLength() / 2; gap > 0; gap /= 2)
	{
		for (int num = (int)gap; num < arr.getLength(); num++)
		{
			T temp = arr[num];
			int check = num;
			for (; check >= (int)gap && arr[check - (int)gap] > temp; check -= (int)gap)
				arr[check] = arr[check - (int)gap];
			arr[check] = temp;
		}
	}
	return GetTickCount() - begin;
}
/****************************************************/
/******************** HEAP SORT *********************/
/****************************************************/
template<class T>
class HeapSort : public ISort<T>
{
private:
	void heapSort(T *arr, int length);
	void heapSort(vector<T> &arr, int length);
	void heapSort(Array<T> &arr, int length);

	void heapify(T *arr, int length, int root);
	void heapify(vector<T> &arr, int length, int root);
	void heapify(Array<T> &arr, int length, int root);
public:
	HeapSort();
	int Sort(T *arr, int length);
	int Sort(vector<T> &arr);
	int Sort(Array<T> &arr);
};

template<class T>
inline HeapSort<T>::HeapSort()
	: ISort("Heap Sort") {}

template<class T>
inline int HeapSort<T>::Sort(T *arr, int length)
{
	int begin = GetTickCount();
	heapSort(arr, length);
	return GetTickCount() - begin;
}

template<class T>
inline int HeapSort<T>::Sort(vector<T> &arr)
{
	int begin = GetTickCount();
	heapSort(arr, (int)arr.size());
	return GetTickCount() - begin;
}

template<class T>
inline int HeapSort<T>::Sort(Array<T> &arr)
{
	int begin = GetTickCount();
	heapSort(arr, arr.getLength());
	return GetTickCount() - begin;
}

template<class T>
inline void HeapSort<T>::heapSort(T *arr, int length)
{
	for (size_t node = length / 2 - 1; node >= 0 && node < length; node--)
		heapify(arr, length, (int)node);

	for (size_t root = length - 1; root >= 0 && root < length; root--)
	{
		T temp = arr[0];
		arr[0] = arr[root];
		arr[root] = temp;

		heapify(arr, (int)root, 0);
	}
}

template<class T>
inline void HeapSort<T>::heapSort(vector<T> &arr, int length)
{
	for (size_t node = length / 2 - 1; node >= 0 && node < length; node--)
		heapify(arr, length, (int)node);

	for (size_t root = length - 1; root >= 0 && root < length; root--)
	{
		T temp = arr[0];
		arr[0] = arr[root];
		arr[root] = temp;

		heapify(arr, (int)root, 0);
	}
}

template<class T>
inline void HeapSort<T>::heapSort(Array<T> &arr, int length)
{
	for (size_t node = length / 2 - 1; node >= 0 && node < length; node--)
		heapify(arr, length, (int)node);

	for (size_t root = length - 1; root >= 0 && root < length; root--)
	{
		T temp = arr[0];
		arr[0] = arr[(int)root];
		arr[(int)root] = temp;

		heapify(arr, (int)root, 0);
	}
}

template<class T>
inline void HeapSort<T>::heapify(T *arr, int length, int root)
{
	if (length > 0 && root >= 0)
	{
		int largest = root, left = (2 * root + 1), right = (2 * root + 2);

		if (left < length && arr[left] > arr[largest])
			largest = left;

		if (right < length && arr[right] > arr[largest])
			largest = right;

		if (largest != root)
		{
			T temp = arr[largest];
			arr[largest] = arr[root];
			arr[root] = temp;
			heapify(arr, length, largest);
		}
	}
}

template<class T>
inline void HeapSort<T>::heapify(vector<T> &arr, int length, int root)
{
	if (length > 0 && root >= 0)
	{
		int largest = root, left = (2 * root + 1), right = (2 * root + 2);

		if (left < length && arr[left] > arr[largest])
			largest = left;

		if (right < length && arr[right] > arr[largest])
			largest = right;

		if (largest != root)
		{
			T temp = arr[largest];
			arr[largest] = arr[root];
			arr[root] = temp;
			heapify(arr, length, largest);
		}
	}
}

template<class T>
inline void HeapSort<T>::heapify(Array<T> &arr, int length, int root)
{
	if (length > 0 && root >= 0)
	{
		int largest = root, left = (2 * root + 1), right = (2 * root + 2);

		if (left < length && arr[left] > arr[largest])
			largest = left;

		if (right < length && arr[right] > arr[largest])
			largest = right;

		if (largest != root)
		{
			T temp = arr[largest];
			arr[largest] = arr[root];
			arr[root] = temp;
			heapify(arr, length, largest);
		}
	}
}