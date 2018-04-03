/*
Name:			Andrew Horn
Date:			1/31/2018
Last Modified:	2/2/2018
Course:			CST211 - Data Structures
Filename:		BackwardIteratorTest.cpp

Overview:		Provides test cases for the BackwardIterator template class. Tests with int, size_t, and string.
				As of 1/31/2018 all tests pass.
*/

#include "stdafx.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "BackwardIterator.h"
#include "Exception.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(BackwardIteratorTest)
	{
	public:

		TEST_METHOD(BackwardIteratorGetCurrentTest)
		{
			CrtCheckMemory check;
			DList<size_t> intList;
			intList.Append(5);
			BackwardIterator<size_t> listIterator;
			listIterator = intList.getTail();
			Assert::IsTrue(listIterator.GetCurrent() == 5);
		}

		TEST_METHOD(BackwardIteratorGetCurrentStringTest)
		{
			CrtCheckMemory check;
			DList<string> stringList;
			stringList.Append("String 1");
			stringList.Append("String 2");
			BackwardIterator<string> stringListIterator;
			stringListIterator = stringList.getTail();
			Assert::IsTrue(stringListIterator.GetCurrent() == "String 2");
		}

		TEST_METHOD(BackwardIteratorDereferenceTest)
		{
			CrtCheckMemory check;
			DList<size_t> intList;
			intList.Append(10);
			BackwardIterator<size_t> listIterator;
			listIterator = intList.getTail();
			Assert::IsTrue(*listIterator == 10);
		}

		TEST_METHOD(BackwardIteratorStringDereferenceTest)
		{
			CrtCheckMemory check;
			DList<string> stringList;
			stringList.Append("Test String");
			BackwardIterator<string> stringIterator;
			stringIterator = stringList.getTail();
			Assert::IsTrue(*stringIterator == "Test String");
		}

		TEST_METHOD(BackwardIteratorMoveNextTest)
		{
			CrtCheckMemory check;
			DList<size_t> intList;
			for (size_t i = 0; i < 10; i++)
				intList.Append(i);
			BackwardIterator<size_t> listIterator;
			listIterator = intList.getTail();
			for (size_t i = 0; i < 10; i++)
				listIterator.MoveNext();
			Assert::IsTrue(listIterator.GetCurrent() == 0);
		}

		TEST_METHOD(BackwardIteratorStringMoveNextTest)
		{
			CrtCheckMemory check;
			DList<string> stringList;
			stringList.Append("String 1");
			stringList.Append("String 2");
			BackwardIterator<string> stringListIterator;
			stringListIterator = stringList.getTail();
			stringListIterator.MoveNext();
			Assert::IsTrue(stringListIterator.GetCurrent() == "String 1");
		}

		TEST_METHOD(BackwardIteratorIsDoneTest)
		{
			CrtCheckMemory check;
			DList<size_t> intList;
			intList.Append(1);
			BackwardIterator<size_t> listIterator;
			listIterator = intList.getTail();
			
			Assert::IsTrue(listIterator.IsDone());
		}

		TEST_METHOD(BackwardIteratorStringIsDoneTest)
		{
			CrtCheckMemory check;
			DList<string> stringList;
			stringList.Append("Test String");
			BackwardIterator<string> stringIterator;
			stringIterator = stringList.getTail();

			Assert::IsTrue(stringIterator.GetCurrent() == "Test String" && stringIterator.IsDone());
		}

		TEST_METHOD(BackwardIteratorResetTest)
		{
			CrtCheckMemory check;
			DList<size_t> intList;
			for (size_t i = 0; i < 10; i++)
				intList.Append(i);
			BackwardIterator<size_t> listIterator;
			listIterator = intList.getTail();
			for (size_t i = 0; !listIterator.IsDone(); i++)
				listIterator.MoveNext();
			if (listIterator.GetCurrent() == 0)
			{
				listIterator.Reset();
				Assert::IsTrue(listIterator.GetCurrent() == 9);
			}
		}

		TEST_METHOD(BackwardIteratorStringResetTest)
		{
			CrtCheckMemory check;
			DList<string> stringList;
			for (size_t i = 0; i < 10; i++)
				stringList.Append("String " + std::to_string(i));
			BackwardIterator<string> stringIterator;
			stringIterator = stringList.getTail();
			for (size_t i = 0; !stringIterator.IsDone(); i++)
				stringIterator.MoveNext();
			if (stringIterator.GetCurrent() == "String 0")
			{
				stringIterator.Reset();
				Assert::IsTrue(stringIterator.GetCurrent() == "String 9");
			}
		}

		TEST_METHOD(BackwardIteratorAssignmentOperatorTest)
		{
			CrtCheckMemory check;
			DList<size_t> intList;
			intList.Append(10);
			BackwardIterator<size_t> listIterator;
			listIterator = intList.getTail();
			Assert::IsTrue(listIterator.GetCurrent() == 10);
		}

		TEST_METHOD(BackwardIteratorStringAssignmentOperatorTest)
		{
			CrtCheckMemory check;
			DList<string> stringList;
			stringList.Append("Test String");
			BackwardIterator<string> stringIterator;
			stringIterator = stringList.getTail();
			Assert::IsTrue(stringIterator.GetCurrent() == "Test String");
		}

		TEST_METHOD(BackwardIteratorIncrementTest)
		{
			CrtCheckMemory check;
			DList<size_t> intList;
			intList.Append(5);
			intList.Append(10);
			intList.Append(15);
			BackwardIterator<size_t> listIterator;
			listIterator = intList.getTail();
			if (listIterator.GetCurrent() == 15)
				listIterator++;
			if (listIterator.GetCurrent() == 10)
				listIterator++;
			if (listIterator.GetCurrent() == 5)
				Assert::IsTrue(true);
		}

		TEST_METHOD(BackwardIteratorStringIncrementTest)
		{
			CrtCheckMemory check;
			DList<string> stringList;
			for (size_t i = 0; i < 3; i++)
				stringList.Append("String " + std::to_string(i));
			BackwardIterator<string> stringIterator;
			stringIterator = stringList.getTail();
			if (stringIterator.GetCurrent() == "String 2")
				stringIterator++;
			if (stringIterator.GetCurrent() == "String 1")
				stringIterator++;
			if (stringIterator.GetCurrent() == "String 0")
				Assert::IsTrue(true);
		}

		TEST_METHOD(BackwardIteratorComprehensiveTest)
		{
			CrtCheckMemory check;
			DList<int> intList;
			for (size_t i = 0; i < 100; i++)
				intList.Append(static_cast<int>(i));
			BackwardIterator<int> listIterator;
			listIterator = intList.getTail();
			if (*listIterator == 99)
				while (!listIterator.IsDone())
					listIterator++;
			if (listIterator.GetCurrent() == 0)
				listIterator.Reset();
			listIterator.MoveNext();
			Assert::IsTrue(*listIterator == 98);
		}
	};
}