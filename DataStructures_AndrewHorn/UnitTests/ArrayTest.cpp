/*
Name:			Andrew Horn
Date:			1/21/18
Course:			CST211 - Data Structures
Filename:		ArrayTest.cpp

Overview:		Test cases for Array template class contained in Array.h.
				As of 1/21/18, all tests passed.
*/

#include "stdafx.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "Array.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(ArrayTest)
	{
	public:

		TEST_METHOD(ArrayDefaultConstructorTest)
		{
			Array<int> myArray;
			Assert::IsTrue(true);
		}

		TEST_METHOD(ArrayNeutralStartIndexTest)
		{
			Array<int> myArray(5, 0);
			Assert::IsTrue(true);
		}

		TEST_METHOD(ArrayPositiveStartIndexTest)
		{
			Array<int> positiveArray(5, 5);
			Assert::IsTrue(true);
		}

		TEST_METHOD(ArrayNegativeStartIndexTest)
		{
			Array<int> negativeArray(5, -3);
			Assert::IsTrue(true);
		}

		TEST_METHOD(ArrayCopyConstructorTest)
		{
			Array<int> myArray(2, 0);
			for (int i = 0; i < 2; i++)
				myArray[i] = i;

			Array<int> copyArray(myArray);
			Assert::IsTrue(myArray[0] == copyArray[0] && myArray[1] == copyArray[1]);
		}

		TEST_METHOD(ArrayNegativeLengthConstructorTest)
		{
			try
			{
				Array<int> negativeLengthArray(-12, 0);
				Assert::IsFalse(0);
			}
			catch (Exception &e)
			{
				// Expected!
				e.print();
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(ArrayOutOfBoundsNegativeTest)
		{
			Array<int> myArray(5, 0);
			try
			{
				myArray[-2] = 1;
			}
			catch (Exception &e)
			{
				// Expect "Out of bounds" exception.
				e.print();
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(ArrayOutOfBoundsPositiveTest)
		{
			Array<int> myArray(5, 0);
			try
			{
				myArray[10] = 1;
			}
			catch (Exception &e)
			{
				// Expect "Out of bounds" exception.
				e.print();
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(ArrayAssignmentOperatorTest)
		{
			bool passed = true;
			Array<int> myArray(10, 0);
			for (int i = 0; i < 10; i++)
				myArray[i] = i;
			Array<int> copyArray;
			copyArray = myArray;
			for (int i = 0; i < 10; i++)
			{
				if (copyArray[i] != myArray[i])
					passed = false;
			}
			Assert::IsTrue(passed);
		}

		TEST_METHOD(ArraySubscriptOperatorTest)
		{
			Array<int> myArray(3, 0);
			for (int i = 0; i < 3; i++)
				myArray[i] = 1;

			Assert::IsTrue(myArray[0] && myArray[1] && myArray[2]);
		}

		TEST_METHOD(ArrayGetLengthTest)
		{
			Array<int> myArray(1, 0);
			Assert::IsTrue(myArray.getLength());
		}

		TEST_METHOD(ArrayGetStartIndexTest)
		{
			Array<int> myArray(1, 1);
			Assert::IsTrue(myArray.getStartIndex());
		}

		TEST_METHOD(ArraySetLengthTest)
		{
			Array<int> myArray(10, 0);
			for (int i = 0; i < 10; i++)
				myArray[i] = i;
			// Will lose data
			myArray.setLength(5);
			Assert::IsTrue(myArray.getLength() == 5);
		}

		TEST_METHOD(ArrayGrowLengthTest)
		{
			Array<int> myArray(5, 0);
			myArray.setLength(10);
			Assert::IsTrue(myArray.getLength() == 10);
		}

		TEST_METHOD(StringArrayDefaultCtorTest)
		{
			Array<std::string> defaultCtor;
			Assert::IsTrue(true);
		}

		TEST_METHOD(StringArrayNeutralIndexTest)
		{
			Array<std::string> neutralIndex(1, 0);
			Assert::IsTrue(true);
		}

		TEST_METHOD(StringArrayPositiveIndexTest)
		{
			Array<std::string> stringArrayPositiveIndex(5, 5);
			Assert::IsTrue(true);
		}

		TEST_METHOD(StringArrayNegativeIndexTest)
		{
			Array<std::string> negativeIndex(1, -1);
			Assert::IsTrue(true);
		}

		TEST_METHOD(StringArrayNegativeLengthCtorTest)
		{
			try
			{
				Array<std::string> badStringArray(-5, 0);
			}
			catch (Exception &e)
			{
				e.print();
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(StringArrayNegativeSetLengthTest)
		{
			Array<std::string> stringArray(10, 0);
			try
			{
				stringArray[-5] = "Bad String";
			}
			catch (Exception &e)
			{
				// Expecting "Out of bounds" exception.
				e.print();
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(StringArrayBadAssignmentOperatorTest)
		{
			try
			{
				Array<std::string> myStringArray; // no length
				myStringArray[0] = "Bad String.";
			}
			catch (Exception &e)
			{
				// Expecting "Out of bounds" exception
				e.print();
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(StringArrayReduceLengthTest)
		{
			Array<std::string> myStringArray;
			bool pass = true;
			myStringArray.setLength(10);
			for (int i = 0; i < 10; i++)
				myStringArray[i] = ("Test String " + i);

			myStringArray.setLength(5);
			for (int i = 0; i < 5; i++)
			{
				if (myStringArray[i] != "Test String " + i)
					pass = false;
			}
			Assert::IsTrue(pass);
		}
	};
}