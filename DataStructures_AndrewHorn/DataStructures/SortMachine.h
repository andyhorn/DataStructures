#pragma once
#include <stdlib.h>
#include "Sort.h"

static const int TEN = 10000;
static const int TWENTY = 20000;
static const int THIRTY = 30000;
static const int BIG = 100000;

enum ARRAYS { I_TEN, I_TEN_TEST, I_TWENTY, I_TWENTY_TEST, I_THIRTY, I_THIRTY_TEST, I_BIG, I_BIG_TEST };

template<class T>
class SortMachine : public ISort<T>
{
private:
	vector<ISort<T>*> sorts_;
	vector<int*> intArrays_;
	vector<Array<T>> arrays_;
	vector<vector<int>> vectors_;
	void initCArrays();
	void initArrays();
	void initVectors();
	void randomize();
	void setTests();
	void copyArray(T *source, T* dest, int length);
	void Sort(int *times);
protected:
	const vector<ISort<T>*>* getSorts() const;
	const vector<int*>* getIntArrays() const;
	const vector<Array<T>>* getArrays() const;
	const vector<vector<T>>* getVectors() const;
public:
	SortMachine();
	SortMachine(const SortMachine<T> &copy);
	~SortMachine();

	void AddSort(ISort<T>*);
	//void RemoveSort(ISort<T>*);
	void SortToFile(const char* filename = "C:\\Users\\andyj\\Documents\\SortLog.txt");
	void SortToScreen();
	void ResetTests();

	SortMachine<T>& operator=(const SortMachine<T> &rhs);
};

/*******************************************************/
/***************** PUBLIC METHODS **********************/
/*******************************************************/
template<class T>
inline SortMachine<T>::SortMachine()
	: ISort("Sort Machine")
{
	sorts_.clear();
	intArrays_.clear();
	arrays_.clear();
	vectors_.clear();

	initCArrays();
	initArrays();
	initVectors();

	randomize();
	setTests();
}

template<class T>
inline SortMachine<T>::SortMachine(const SortMachine<T> &copy)
{
	if (&copy != this)
		*this = copy;
}

template<class T>
inline SortMachine<T>::~SortMachine() {}

template<class T>
inline void SortMachine<T>::AddSort(ISort<T> *sort) { sorts_.push_back(sort); }

template<class T>
inline void SortMachine<T>::ResetTests()
{
	vectors_[I_TEN_TEST].clear();
	vectors_[I_TWENTY_TEST].clear();
	vectors_[I_THIRTY_TEST].clear();

	for (size_t v = 0; v < vectors_.size(); v += 2)
		vectors_[(int)v + 1] = vectors_[(int)v];
	for (size_t a = 0; a < arrays_.size(); a += 2)
		arrays_[(int)a + 1] = arrays_[(int)a];

	copyArray(intArrays_[I_TEN], intArrays_[I_TEN_TEST], TEN);
	copyArray(intArrays_[I_TWENTY], intArrays_[I_TWENTY_TEST]);
	copyArray(intArrays_[I_THIRTY], intArrays_[I_THIRTY_TEST]);
	copyArray(intArrays_[I_BIG], intArrays_[I_BIG_TEST]);
}

template<class T>
inline void SortMachine<T>::SortToFile(const char *filename)
{
	std::ofstream file;
	file.open(filename, std::ofstream::out | std::ofstream::app);
	int times[88]{ 0 };
	Sort(times);
	size_t timeIndex = 0;
	for (size_t i = 0; i < sorts_.size(); i++)
	{
		file << "*** " << sorts_[i] << " ***" << endl;
		file << "C-Arrays\nElements: " << TEN << ". Time: " << times[timeIndex++] << "ms." << endl;
		file << "Elements: " << TWENTY << ". Time: " << times[timeIndex++] << "ms." << endl;
		file << "Elements: " << THIRTY << ". Time: " << times[timeIndex++] << "ms." << endl;
		file << "Elements: " << BIG << ". Time: " << times[timeIndex++] << "ms.\n" << endl;
		file << "MyArrays\nElements: " << TEN << ". Time: " << times[timeIndex++] << "ms." << endl;
		file << "Elements: " << TWENTY << ". Time: " << times[timeIndex++] << "ms." << endl;
		file << "Elements: " << THIRTY << ". Time: " << times[timeIndex++] << "ms." << endl;
		file << "Elements: " << BIG << ". Time: " << times[timeIndex++] << "ms.\n" << endl;
		file << "Vectors\nElements: " << TEN << ". Time: " << times[timeIndex++] << "ms." << endl;
		file << "Elements: " << TWENTY << ". Time: " << times[timeIndex++] << "ms." << endl;
		file << "Elements: " << THIRTY << ". Time: " << times[timeIndex++] << "ms." << endl;
	}
	file.close();
}

template<class T>
inline void SortMachine<T>::SortToScreen()
{
	int times[88]{ 0 };
	Sort(times);
	size_t timeIndex = 0;
	for (size_t i = 0; i < sorts_.size(); i++)
	{
		cout << "*** " << sorts_[i] << " ***" << endl;
		cout << "C-Arrays\nElements: " << TEN << ". Time: " << times[timeIndex++] << "ms." << endl;
		cout << "Elements: " << TWENTY << ". Time: " << times[timeIndex++] << "ms." << endl;
		cout << "Elements: " << THIRTY << ". Time: " << times[timeIndex++] << "ms." << endl;
		cout << "Elements: " << BIG << ". Time: " << times[timeIndex++] << "ms.\n" << endl;
		cout << "MyArrays\nElements: " << TEN << ". Time: " << times[timeIndex++] << "ms." << endl;
		cout << "Elements: " << TWENTY << ". Time: " << times[timeIndex++] << "ms." << endl;
		cout << "Elements: " << THIRTY << ". Time: " << times[timeIndex++] << "ms." << endl;
		cout << "Elements: " << BIG << ". Time: " << times[timeIndex++] << "ms.\n" << endl;
		cout << "Vectors\nElements: " << TEN << ". Time: " << times[timeIndex++] << "ms." << endl;
		cout << "Elements: " << TWENTY << ". Time: " << times[timeIndex++] << "ms." << endl;
		cout << "Elements: " << THIRTY << ". Time: " << times[timeIndex++] << "ms." << endl;
	}
}

template<class T>
inline void SortMachine<T>::Sort(int *times)
{
	size_t timeIndex = 0;
	for (size_t sort = 0; sort < sorts_.size(); sort++)
	{
		for (size_t c = 0; c < intArrays_.size(); c++)
			times[timeIndex++] = sorts_[(int)sort].Sort(intArrays_[(int)c]);
		for (size_t a = 0; a < arrays_.size(); a++)
			times[timeIndex++] = sorts_[(int)sort].Sort(arrays_[(int)a]);
		for (size_t v = 0; v < vectors_.size(); v++)
			times[timeIndex++] = sorts_[(int)sort].Sort(vectors_[(int)v]);
	}
}

template<class T>
inline SortMachine<T>& SortMachine<T>::operator=(const SortMachine<T> &rhs)
{
	if (&rhs != this)
	{
		sorts_.clear();
		intArrays_.clear();
		arrays_.clear();
		vectors_.clear();

		for (size_t i = 0; i < rhs.getSorts()->size(); i++)
			sorts_[(int)i] = rhs.getSorts[(int)i];
		for (size_t j = 0; j < rhs.getArrays()->size(); j++)
			arrays_[(int)i] = rhs.getArrays()[(int)i];

		copyArray(rhs.getIntArrays()[I_TEN], intArrays_[I_TEN], TEN);
		copyArray(rhs.getIntArrays()[I_TEN_TEST], intArrays_[I_TEN_TEST], TEN);
		copyArray(rhs.getIntArrays()[I_TWENTY], intArrays_[I_TWENTY], TWENTY);
		copyArray(rhs.getIntArrays()[I_TWENTY_TEST], intArrays_[I_TWENTY_TEST], TWENTY);
		copyArray(rhs.getIntArrays()[I_THIRTY], intArrays_[I_THIRTY], THIRTY);
		copyArray(rhs.getIntArrays()[I_THIRTY_TEST], intArrays_[I_THIRTY_TEST], THIRTY);
		copyArray(rhs.getIntArrays()[I_BIG], intArrays_[I_BIG], BIG);
		copyArray(rhs.getIntArrays()[I_BIG_TEST], intArrays_[I_BIG_TEST], BIG);
	}
}

/*******************************************************/
/****************** PROTECTED METHODS ******************/
/*******************************************************/

template<class T>
inline const vector<ISort<T>*>* SortMachine<T>::getSorts() const { return &sorts_; }

template<class T>
inline const vector<int*>* SortMachine<T>::getIntArrays() const { return &intArrays_; }

template<class T>
inline const vector<Array<T>>* SortMachine<T>::getArrays() const { return &arrays_; }

template<class T>
inline const vector<vector<T>>* SortMachine<T>::getVectors() const { return &vectors_; }

/*******************************************************/
/***************** PRIVATE METHODS *********************/
/*******************************************************/

template<class T>
inline void SortMachine<T>::initCArrays()
{
	/* C-ARRAYS */
	int cTen[TEN];
	int cTenTest[TEN];
	int cTwenty[TWENTY];
	int cTwentyTest[TWENTY];
	int cThirty[THIRTY];
	int cThirtyTest[THIRTY];
	int cBig[BIG];
	int cBigTest[BIG];

	intArrays_.push_back(cTen);
	intArrays_.push_back(cTenTest);
	intArrays_.push_back(cTwenty);
	intArrays_.push_back(cTwentyTest);
	intArrays_.push_back(cThirty);
	intArrays_.push_back(cThirtyTest);
	intArrays_.push_back(cBig);
	intArrays_.push_back(cBigTest);
}

template<class T>
inline void SortMachine<T>::initArrays()
{
	/* ARRAYS */
	Array<int> aTen;
	Array<int> aTenTest;
	Array<int> aTwenty;
	Array<int> aTwentyTest;
	Array<int> aThirty;
	Array<int> aThirtyTest;
	Array<int> aBig;
	Array<int> aBigTest;

	aTen.setLength(TEN);
	aTenTest.setLength(TEN);
	aTwenty.setLength(TWENTY);
	aTwentyTest.setLength(TWENTY);
	aThirty.setLength(THIRTY);
	aThirtyTest.setLength(THIRTY);
	aBig.setLength(BIG);
	aBigTest.setLength(BIG);

	arrays_.push_back(aTen);
	arrays_.push_back(aTenTest);
	arrays_.push_back(aTwenty);
	arrays_.push_back(aThirty);
	arrays_.push_back(aThirtyTest);
	arrays_.push_back(aBig);
	arrays_.push_back(aBigTest);
}

template<class T>
inline void SortMachine<T>::initVectors()
{
	vector<int> vTen;
	vector<int> vTenTest;
	vector<int> vTwenty;
	vector<int> vTwentyTest;
	vector<int> vThirty;
	vector<int> vThirtyTest;

	vectors_.push_back(vTen);
	vectors_.push_back(vTenTest);
	vectors_.push_back(vTwenty);
	vectors_.push_back(vTwentyTest);
	vectors_.push_back(vThirty);
	vectors_.push_back(vThirtyTest);
}

template<class T>
inline void SortMachine<T>::randomize()
{
	for (size_t vector = 0; vector < vectors_.size(); vector++)
		vectors_[(int)vector].clear();

	for (size_t i = 0; i < BIG; i++)
	{
		int num = rand() % 100000;
		intArrays_[I_BIG][(int)i] = num;
		arrays_[I_BIG][(int)i] = num;

		if (i < THIRTY)
		{
			intArrays_[I_THIRTY][(int)i] = num;
			arrays_[I_THIRTY][(int)i] = num;
			vectors_[I_THIRTY].push_back(num);

			if (i < TWENTY)
			{
				intArrays_[I_TWENTY][(int)i] = num;
				arrays_[I_TWENTY][(int)i] = num;
				vectors_[I_TWENTY].push_back(num);

				if (i < TEN)
				{
					intArrays_[I_TEN][(int)i] = num;
					arrays_[I_TEN][(int)i] = num;
					vectors_[I_TEN].push_back(num);
				}
			}
		}
	}
}

template<class T>
inline void SortMachine<T>::setTests()
{
	for (size_t v = 0; v < vectors_.size(); v += 2)
		vectors_[v + 1] = vectors_[v];
	for (size_t a = 0; a < arrays_.size(); a += 2)
		arrays_[a + 1] = arrays_[a];

	copyArray(intArrays_[I_TEN], intArrays_[I_TEN_TEST], TEN);
	copyArray(intArrays_[I_TWENTY], intArrays_[I_TWENTY_TEST], TWENTY);
	copyArray(intArrays_[I_THIRTY], intArrays_[I_THIRTY_TEST], THIRTY);
	copyArray(intArrays_[I_BIG], intArrays_[I_BIG_TEST], BIG);
}

template<class T>
inline void SortMachine<T>::copyArray(T *source, T* dest, int length)
{
	for (size_t i = 0; i < length; i++)
		dest[(int)i] = source[(int)i];
}

