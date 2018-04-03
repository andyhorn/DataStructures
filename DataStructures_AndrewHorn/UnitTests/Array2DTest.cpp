/*
Name:			Andrew Horn
Date:			1/22/18
Course:			CST211 - Data Structures
Filename:		Array2DTest.cpp

Overview:		Tests all methods on the Array2D template. As of 1/22/18, all 28 tests
				pass. 
*/


#include "stdafx.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "Array2D.h"
#include "Exception.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(Array2DTest)
	{
	public:
		TEST_METHOD(Array2DDefaultCtorTest)
		{
			CrtCheckMemory check;
			Array2D<int> defaultCtor;
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DStringDefaultCtorTest)
		{
			CrtCheckMemory check;
			Array2D<string> stringArray;
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DGoodCtorTest)
		{
			CrtCheckMemory check;
			Array2D<int> myArray(3, 3);
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DStringGoodCtorTest)
		{
			CrtCheckMemory check;
			Array2D<string> myStringArray(3, 3);
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DBadRowCtorTest)
		{
			CrtCheckMemory check;
			try
			{
				Array2D<int> badArray(-1, 3);
			}
			catch (Exception)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DBadColCtorTest)
		{
			CrtCheckMemory check;
			try
			{
				Array2D<int> badArray(3, -1);
			}
			catch (Exception)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DStringBadRowCtorTest)
		{
			CrtCheckMemory check;
			try
			{
				Array2D<string> badStringArray(-1, 3);
			}
			catch (Exception)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DStringBadColCtorTest)
		{
			CrtCheckMemory check;
			try
			{
				Array2D<string> badStringArray(3, -1);
			}
			catch (Exception)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DCopyCtorTest)
		{
			CrtCheckMemory check;
			Array2D<int> arrayOne(3, 3);
			Array2D<int> arrayTwo(arrayOne);
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DStringCopyCtorTest)
		{
			CrtCheckMemory check;
			Array2D<string> stringArrayOne(3, 3);
			Array2D<string> stringArrayTwo(stringArrayOne);
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DAssignmentOpTest)
		{
			CrtCheckMemory check;
			Array2D<int> sourceArray(3, 3);
			Array2D<int> destArray;
			destArray = sourceArray;
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DStringAssignmentOpTest)
		{
			CrtCheckMemory check;
			Array2D<string> sourceStringArray(3, 3);
			Array2D<string> destStringArray(3, 3);
			destStringArray = sourceStringArray;
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DSubscriptOpGoodTest)
		{
			CrtCheckMemory check;
			try
			{
				int count = 0;
				Array2D<int> myArray(3, 3);
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						myArray[i][j] = count++;
					}
				}
				Assert::IsTrue(true);
			}
			catch (Exception)
			{
				// Not expecting an exception.
			}
		}

		TEST_METHOD(Array2DSubscriptOpBadRowTest)
		{
			CrtCheckMemory check;
			try
			{
				Array2D<int> myArray(3, 3);
				myArray[-1][0] = 1;
			}
			catch (Exception)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DSubscriptOpBadColTest)
		{
			CrtCheckMemory check;
			try
			{
				Array2D<int> myArray(3, 3);
				myArray[0][-1] = 1;
			}
			catch (Exception)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DStringSubscriptOpGoodTest)
		{
			CrtCheckMemory check;
			try
			{
				Array2D<string> myStringArray(3, 3);
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						myStringArray[i][j] = "Test String " + (i + j);
				Assert::IsTrue(true);
			}
			catch (Exception)
			{
				// Not expecting an exception.
			}
		}

		TEST_METHOD(Array2DStringSubscriptOpBadRowTest)
		{
			CrtCheckMemory check;
			Array2D<string> myStringArray(3, 3);
			try
			{
				myStringArray[-1][0] = "Bad String.";
			}
			catch (Exception)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DStringSubscriptOpBadColTest)
		{
			CrtCheckMemory check;
			Array2D<string> myStringArray(3, 3);
			try
			{
				myStringArray[0][-1] = "Bad String.";
			}
			catch (Exception)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DSetRowGoodTest)
		{
			CrtCheckMemory check;
			Array2D<int> myArray(3, 3);
			myArray.setRow(4);
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DSetColumnGoodTest)
		{
			CrtCheckMemory check;
			Array2D<int> myArray(3, 3);
			myArray.setColumn(4);
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DSetRowBadTest)
		{
			CrtCheckMemory check;
			Array2D<int> myArray(3, 3);
			try
			{
				myArray.setRow(-1);
			}
			catch (Exception)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DSetColumnBadTest)
		{
			CrtCheckMemory check;
			Array2D<int> myArray(3, 3);
			try
			{
				myArray.setColumn(-1);
			}
			catch (Exception)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DStringSetRowGoodTest)
		{
			CrtCheckMemory check;
			Array2D<string> myStringArray(3, 3);
			myStringArray.setRow(4);
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DStringSetColGoodTest)
		{
			CrtCheckMemory check;
			Array2D<string> myStringArray(3, 3);
			myStringArray.setColumn(4);
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DStringSetRowBadTest)
		{
			CrtCheckMemory check;
			Array2D<string> myStringArray(3, 3);
			try
			{
				myStringArray.setRow(-1);
			}
			catch (Exception)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DStringSetColumnBadTest)
		{
			CrtCheckMemory check;
			Array2D<string> myStringArray(3, 3);
			try
			{
				myStringArray.setColumn(-1);
			}
			catch (Exception)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DSetRowDataLossTest)
		{
			CrtCheckMemory check;
			Array2D<int> myArray(3, 3);
			int index = 0;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					myArray[i][j] = index++;
			// 0 1 2
			// 3 4 5
			// 6 7 8

			myArray.setRow(2);
			// 0 1 2
			// 3 4 5
			// +
			//--------
			// 15

			int total = 0;
			for (int i = 0; i < myArray.getRow(); i++)
				for (int j = 0; j < myArray.getColumn(); j++)
					total += myArray[i][j];

			Assert::IsTrue(total == 15);
		}

		TEST_METHOD(Array2DSetColumnDataLossTest)
		{
			CrtCheckMemory check;
			Array2D<int> myArray(3, 3);
			int index = 0;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					myArray[i][j] = index++;
			// 0 1 2
			// 3 4 5
			// 6 7 8

			myArray.setColumn(2);
			// 0 1
			// 3 4
			// 6 7
			// +
			//------
			// 21

			int total = 0;
			for (int i = 0; i < myArray.getRow(); i++)
				for (int j = 0; j < myArray.getColumn(); j++)
					total += myArray[i][j];

			Assert::IsTrue(total == 21);
		}
	};
}
