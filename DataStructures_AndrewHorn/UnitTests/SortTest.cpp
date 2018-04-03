#include "stdafx.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "Exception.h"
#include <string>
#include "Sort.h"
#include <vector>
#include "Array.h"
#include <stdlib.h>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;
using std::vector;
using std::ofstream;

static const int TEN = 10000;
static const int TWENTY = 20000;
static const int THIRTY = 30000;
static const int BIG = 100000;

namespace UnitTests
{
	static int cTen[TEN];
	static int cTenTest[TEN];
	static int cTwenty[TWENTY];
	static int cTwentyTest[TWENTY];
	static int cThirty[THIRTY];
	static int cThirtyTest[THIRTY];
	static int cBig[BIG];
	static int cBigTest[BIG];

	static Array<int> aTen;
	static Array<int> aTenTest;
	static Array<int> aTwenty;
	static Array<int> aTwentyTest;
	static Array<int> aThirty;
	static Array<int> aThirtyTest;

	static vector<int> vTen;
	static vector<int> vTenTest;
	static vector<int> vTwenty;
	static vector<int> vTwentyTest;
	static vector<int> vThirty;
	static vector<int> vThirtyTest;

	static void printArray(ofstream &stream, const char *title, int length, int time)
	{
		size_t i = 0;
		while (title[i] != '\0')
			stream << title[i++];
		stream << "Elements: " << length << " - Time to complete: " << time << "ms." << endl;
	}

	static void copyArray(int *source, int *dest, int length)
	{
		for (size_t i = 0; i < length; i++)
			dest[(int)i] = source[(int)i];
	}

	static void PrepTest()
	{
		vTenTest.clear();
		vTenTest = vTen;
		vTwentyTest.clear();
		vTwentyTest = vTwenty;
		vThirtyTest.clear();
		vThirtyTest = vThirty;

		aTenTest = aTen;
		aTwentyTest = aTwenty;
		aThirtyTest = aThirty;

		copyArray(cTen, cTenTest, TEN);
		copyArray(cTwenty, cTwentyTest, TWENTY);
		copyArray(cThirty, cThirtyTest, THIRTY);
		copyArray(cBig, cBigTest, BIG);
	}

	TEST_CLASS(SortTest)
	{
	public:

		TEST_CLASS_INITIALIZE(Init)
		{
			aTen.setLength(10000);
			aTwenty.setLength(20000);
			aThirty.setLength(30000);

			for (int i = 0; i < 100000; i++)
			{
				int num = rand() % 100000;
				cBig[i] = num;

				if (i < 30000)
				{
					cThirty[i] = num;
					aThirty[i] = num;
					vThirty.push_back(num);

					if (i < 20000)
					{
						cTwenty[i] = num;
						aTwenty[i] = num;
						vTwenty.push_back(num);

						if (i < 10000)
						{
							cTen[i] = num;
							aTen[i] = num;
							vTen.push_back(num);
						}
					}
				}
			}
		}

		TEST_METHOD(BubbleSortTest)
		{
			PrepTest();

			CrtCheckMemory check;
			BubbleSort<int> sort;

			int cTenTime = sort.Sort(cTenTest, TEN);
			int cTwentyTime = sort.Sort(cTwentyTest, TWENTY);
			int cThirtyTime = sort.Sort(cThirtyTest, THIRTY);
			int cBigTime = sort.Sort(cBigTest, BIG);

			int aTenTime = sort.Sort(aTenTest);
			int aTwentyTime = sort.Sort(aTwentyTest);
			int aThirtyTime = sort.Sort(aThirtyTest);

			int vTenTime = sort.Sort(vTenTest);
			int vTwentyTime = sort.Sort(vTwentyTest);
			int vThirtyTime = sort.Sort(vThirtyTest);

			ofstream output_file;
			output_file.open("C:\\Users\\andyj\\Documents\\SortLog.txt", std::ofstream::out | std::ofstream::app);
			output_file << "*** BUBBLE SORT ***" << endl;
			printArray(output_file, "C-ARRAY\n", TEN, cTenTime);
			printArray(output_file, "", TWENTY, cTwentyTime);
			printArray(output_file, "", THIRTY, cThirtyTime);
			printArray(output_file, "", BIG, cBigTime);
			printArray(output_file, "ARRAY\n", aTen.getLength(), aTenTime);
			printArray(output_file, "", aTwenty.getLength(), aTwentyTime);
			printArray(output_file, "", aThirty.getLength(), aThirtyTime);
			printArray(output_file, "VECTOR\n", (int)vTen.size(), vTenTime);
			printArray(output_file, "", (int)vTwenty.size(), vTwentyTime);
			printArray(output_file, "", (int)vThirty.size(), vThirtyTime);
			output_file << endl;
			output_file.close();

			Assert::IsTrue(aTenTime && aTwentyTime && aThirtyTime 
				&& vTenTime && vTwentyTime && vThirtyTime);
		}

		TEST_METHOD(ImprovedBubbleSortTest)
		{
			PrepTest();

			CrtCheckMemory check;
			BubbleSortImproved<int> sort;

			int cTenTime = sort.Sort(cTenTest, TEN);
			int cTwentyTime = sort.Sort(cTwentyTest, TWENTY);
			int cThirtyTime = sort.Sort(cThirtyTest, THIRTY);
			int cBigTime = sort.Sort(cBigTest, BIG);

			int aTenTime = sort.Sort(aTenTest);
			int aTwentyTime = sort.Sort(aTwentyTest);
			int aThirtyTime = sort.Sort(aThirtyTest);

			int vTenTime = sort.Sort(vTenTest);
			int vTwentyTime = sort.Sort(vTwentyTest);
			int vThirtyTime = sort.Sort(vThirtyTest);

			ofstream output_file;
			output_file.open("C:\\Users\\andyj\\Documents\\SortLog.txt", std::ofstream::out | std::ofstream::app);
			output_file << "*** IMPROVED BUBBLE SORT ***" << endl;
			printArray(output_file, "C-ARRAY\n", TEN, cTenTime);
			printArray(output_file, "", TWENTY, cTwentyTime);
			printArray(output_file, "", THIRTY, cThirtyTime);
			printArray(output_file, "", BIG, cBigTime);
			printArray(output_file, "ARRAY\n", aTen.getLength(), aTenTime);
			printArray(output_file, "", aTwenty.getLength(), aTwentyTime);
			printArray(output_file, "", aThirty.getLength(), aThirtyTime);
			printArray(output_file, "VECTOR\n", (int)vTen.size(), vTenTime);
			printArray(output_file, "", (int)vTwenty.size(), vTwentyTime);
			printArray(output_file, "", (int)vThirty.size(), vThirtyTime);
			output_file << endl;
			output_file.close();

			Assert::IsTrue(cBigTime && aTenTime && aTwentyTime && aThirtyTime
				&& vTenTime && vTwentyTime && vThirtyTime);
		}

		TEST_METHOD(SelectionSortTest)
		{
			PrepTest();

			CrtCheckMemory check;
			SelectionSort<int> sort;

			int cTenTime = sort.Sort(cTenTest, TEN);
			int cTwentyTime = sort.Sort(cTwentyTest, TWENTY);
			int cThirtyTime = sort.Sort(cThirtyTest, THIRTY);
			int cBigTime = sort.Sort(cBigTest, BIG);

			int aTenTime = sort.Sort(aTenTest);
			int aTwentyTime = sort.Sort(aTwentyTest);
			int aThirtyTime = sort.Sort(aThirtyTest);

			int vTenTime = sort.Sort(vTenTest);
			int vTwentyTime = sort.Sort(vTwentyTest);
			int vThirtyTime = sort.Sort(vThirtyTest);

			ofstream output_file;
			output_file.open("C:\\Users\\andyj\\Documents\\SortLog.txt", std::ofstream::out | std::ofstream::app);
			output_file << "*** SELECTION SORT ***" << endl;
			printArray(output_file, "C-ARRAY\n", TEN, cTenTime);
			printArray(output_file, "", TWENTY, cTwentyTime);
			printArray(output_file, "", THIRTY, cThirtyTime);
			printArray(output_file, "", BIG, cBigTime);
			printArray(output_file, "ARRAY\n", aTen.getLength(), aTenTime);
			printArray(output_file, "", aTwenty.getLength(), aTwentyTime);
			printArray(output_file, "", aThirty.getLength(), aThirtyTime);
			printArray(output_file, "VECTOR\n", (int)vTen.size(), vTenTime);
			printArray(output_file, "", (int)vTwenty.size(), vTwentyTime);
			printArray(output_file, "", (int)vThirty.size(), vThirtyTime);
			output_file << endl;
			output_file.close();

			Assert::IsTrue(cBigTime && aTenTime && aTwentyTime && aThirtyTime
				&& vTenTime && vTwentyTime && vThirtyTime);
		}

		TEST_METHOD(InsertionSortTest)
		{
			PrepTest();

			CrtCheckMemory check;
			InsertionSort<int> sort;

			int cTenTime = sort.Sort(cTenTest, TEN);
			int cTwentyTime = sort.Sort(cTwentyTest, TWENTY);
			int cThirtyTime = sort.Sort(cThirtyTest, THIRTY);
			int cBigTime = sort.Sort(cBigTest, BIG);

			int aTenTime = sort.Sort(aTenTest);
			int aTwentyTime = sort.Sort(aTwentyTest);
			int aThirtyTime = sort.Sort(aThirtyTest);

			int vTenTime = sort.Sort(vTenTest);
			int vTwentyTime = sort.Sort(vTwentyTest);
			int vThirtyTime = sort.Sort(vThirtyTest);

			ofstream output_file;
			output_file.open("C:\\Users\\andyj\\Documents\\SortLog.txt", std::ofstream::out | std::ofstream::app);
			output_file << "*** INSERTION SORT ***" << endl;
			printArray(output_file, "C-ARRAY\n", TEN, cTenTime);
			printArray(output_file, "", TWENTY, cTwentyTime);
			printArray(output_file, "", THIRTY, cThirtyTime);
			printArray(output_file, "", BIG, cBigTime);
			printArray(output_file, "ARRAY\n", aTen.getLength(), aTenTime);
			printArray(output_file, "", aTwenty.getLength(), aTwentyTime);
			printArray(output_file, "", aThirty.getLength(), aThirtyTime);
			printArray(output_file, "VECTOR\n", (int)vTen.size(), vTenTime);
			printArray(output_file, "", (int)vTwenty.size(), vTwentyTime);
			printArray(output_file, "", (int)vThirty.size(), vThirtyTime);
			output_file << endl;
			output_file.close();

			Assert::IsTrue(cBigTime && aTenTime && aTwentyTime && aThirtyTime
				&& vTenTime && vTwentyTime && vThirtyTime);
		}

		TEST_METHOD(MergeSortTest)
		{
			PrepTest();

			CrtCheckMemory check;
			MergeSort<int> sort;

			int cTenTime = sort.Sort(cTenTest, TEN);
			int cTwentyTime = sort.Sort(cTwentyTest, TWENTY);
			int cThirtyTime = sort.Sort(cThirtyTest, THIRTY);
			int cBigTime = sort.Sort(cBigTest, BIG);

			int aTenTime = sort.Sort(aTenTest);
			int aTwentyTime = sort.Sort(aTwentyTest);
			int aThirtyTime = sort.Sort(aThirtyTest);

			int vTenTime = sort.Sort(vTenTest);
			int vTwentyTime = sort.Sort(vTwentyTest);
			int vThirtyTime = sort.Sort(vThirtyTest);

			ofstream output_file;
			output_file.open("C:\\Users\\andyj\\Documents\\SortLog.txt", std::ofstream::out | std::ofstream::app);
			output_file << "*** MERGE SORT ***" << endl;
			printArray(output_file, "C-ARRAY\n", TEN, cTenTime);
			printArray(output_file, "", TWENTY, cTwentyTime);
			printArray(output_file, "", THIRTY, cThirtyTime);
			printArray(output_file, "", BIG, cBigTime);
			printArray(output_file, "ARRAY\n", aTen.getLength(), aTenTime);
			printArray(output_file, "", aTwenty.getLength(), aTwentyTime);
			printArray(output_file, "", aThirty.getLength(), aThirtyTime);
			printArray(output_file, "VECTOR\n", (int)vTen.size(), vTenTime);
			printArray(output_file, "", (int)vTwenty.size(), vTwentyTime);
			printArray(output_file, "", (int)vThirty.size(), vThirtyTime);
			output_file << endl;
			output_file.close();

			Assert::IsTrue(cBigTime && aTenTime && aTwentyTime && aThirtyTime
				&& vTenTime && vTwentyTime && vThirtyTime);
		}

		TEST_METHOD(QuickSortTest)
		{
			PrepTest();

			CrtCheckMemory check;
			QuickSort<int> sort;

			int cTenTime = sort.Sort(cTenTest, TEN);
			int cTwentyTime = sort.Sort(cTwentyTest, TWENTY);
			int cThirtyTime = sort.Sort(cThirtyTest, THIRTY);
			int cBigTime = sort.Sort(cBigTest, BIG);

			int aTenTime = sort.Sort(aTenTest);
			int aTwentyTime = sort.Sort(aTwentyTest);
			int aThirtyTime = sort.Sort(aThirtyTest);

			int vTenTime = sort.Sort(vTenTest);
			int vTwentyTime = sort.Sort(vTwentyTest);
			int vThirtyTime = sort.Sort(vThirtyTest);

			ofstream output_file;
			output_file.open("C:\\Users\\andyj\\Documents\\SortLog.txt", std::ofstream::out | std::ofstream::app);
			output_file << "*** QUICK SORT ***" << endl;
			printArray(output_file, "C-ARRAY\n", TEN, cTenTime);
			printArray(output_file, "", TWENTY, cTwentyTime);
			printArray(output_file, "", THIRTY, cThirtyTime);
			printArray(output_file, "", BIG, cBigTime);
			printArray(output_file, "ARRAY\n", aTen.getLength(), aTenTime);
			printArray(output_file, "", aTwenty.getLength(), aTwentyTime);
			printArray(output_file, "", aThirty.getLength(), aThirtyTime);
			printArray(output_file, "VECTOR\n", (int)vTen.size(), vTenTime);
			printArray(output_file, "", (int)vTwenty.size(), vTwentyTime);
			printArray(output_file, "", (int)vThirty.size(), vThirtyTime);
			output_file << endl;
			output_file.close();

			Assert::IsTrue(cBigTime && aTenTime && aTwentyTime && aThirtyTime
				&& vTenTime && vTwentyTime && vThirtyTime);
		}

		TEST_METHOD(ShellSortTest)
		{
			PrepTest();

			CrtCheckMemory check;
			ShellSort<int> sort;

			int cTenTime = sort.Sort(cTenTest, TEN);
			int cTwentyTime = sort.Sort(cTwentyTest, TWENTY);
			int cThirtyTime = sort.Sort(cThirtyTest, THIRTY);
			int cBigTime = sort.Sort(cBigTest, BIG);

			int aTenTime = sort.Sort(aTenTest);
			int aTwentyTime = sort.Sort(aTwentyTest);
			int aThirtyTime = sort.Sort(aThirtyTest);

			int vTenTime = sort.Sort(vTenTest);
			int vTwentyTime = sort.Sort(vTwentyTest);
			int vThirtyTime = sort.Sort(vThirtyTest);

			ofstream output_file;
			output_file.open("C:\\Users\\andyj\\Documents\\SortLog.txt", std::ofstream::out | std::ofstream::app);
			output_file << "*** SHELL SORT ***" << endl;
			printArray(output_file, "C-ARRAY\n", TEN, cTenTime);
			printArray(output_file, "", TWENTY, cTwentyTime);
			printArray(output_file, "", THIRTY, cThirtyTime);
			printArray(output_file, "", BIG, cBigTime);
			printArray(output_file, "ARRAY\n", aTen.getLength(), aTenTime);
			printArray(output_file, "", aTwenty.getLength(), aTwentyTime);
			printArray(output_file, "", aThirty.getLength(), aThirtyTime);
			printArray(output_file, "VECTOR\n", (int)vTen.size(), vTenTime);
			printArray(output_file, "", (int)vTwenty.size(), vTwentyTime);
			printArray(output_file, "", (int)vThirty.size(), vThirtyTime);
			output_file << endl;
			output_file.close();

			Assert::IsTrue(cBigTime && aTenTime && aTwentyTime && aThirtyTime
				&& vTenTime && vTwentyTime && vThirtyTime);
		}

		TEST_METHOD(HeapSortTest)
		{
			PrepTest();

			CrtCheckMemory check;
			HeapSort<int> sort;

			int cTenTime = sort.Sort(cTenTest, TEN);
			int cTwentyTime = sort.Sort(cTwentyTest, TWENTY);
			int cThirtyTime = sort.Sort(cThirtyTest, THIRTY);
			int cBigTime = sort.Sort(cBigTest, BIG);

			int aTenTime = sort.Sort(aTenTest);
			int aTwentyTime = sort.Sort(aTwentyTest);
			int aThirtyTime = sort.Sort(aThirtyTest);

			int vTenTime = sort.Sort(vTenTest);
			int vTwentyTime = sort.Sort(vTwentyTest);
			int vThirtyTime = sort.Sort(vThirtyTest);

			ofstream output_file;
			output_file.open("C:\\Users\\andyj\\Documents\\SortLog.txt", std::ofstream::out | std::ofstream::app);
			output_file << "*** HEAP SORT ***" << endl;
			printArray(output_file, "C-ARRAY\n", TEN, cTenTime);
			printArray(output_file, "", TWENTY, cTwentyTime);
			printArray(output_file, "", THIRTY, cThirtyTime);
			printArray(output_file, "", BIG, cBigTime);
			printArray(output_file, "ARRAY\n", aTen.getLength(), aTenTime);
			printArray(output_file, "", aTwenty.getLength(), aTwentyTime);
			printArray(output_file, "", aThirty.getLength(), aThirtyTime);
			printArray(output_file, "VECTOR\n", (int)vTen.size(), vTenTime);
			printArray(output_file, "", (int)vTwenty.size(), vTwentyTime);
			printArray(output_file, "", (int)vThirty.size(), vThirtyTime);
			output_file << endl;
			output_file.close();

			Assert::IsTrue(cBigTime && aTenTime && aTwentyTime && aThirtyTime
				&& vTenTime && vTwentyTime && vThirtyTime);
		}
	};
}