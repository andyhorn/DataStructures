/*
Name:			Andrew Horn
Date:			1/31/2018
Course:			CST211 - Data Structures
Filename:		ForwardIteratorTest.cpp

Overview:		Provides unit tests for all methods of the ForwardIterator template class. Tests with int, size_t, and strings.
				As of 1/31/2018, all tests pass.
*/

#include "stdafx.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "ForwardIterator.h"
#include "Exception.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(ForwardIteratorTest)
	{
	public:

		TEST_METHOD(ForwardIteratorGetCurrentTest)
		{
			CrtCheckMemory check;
			DList<size_t> intList;
			intList.Append(5);
			ForwardIterator<size_t> listIterator;
			listIterator = intList.getHead();
			Assert::IsTrue(listIterator.GetCurrent() == 5);
		}

		TEST_METHOD(ForwardIteratorGetCurrentStringTest)
		{
			CrtCheckMemory check;
			DList<string> stringList;
			stringList.Append("String 1");
			stringList.Append("String 2");
			ForwardIterator<string> stringListIterator;
			stringListIterator = stringList.getHead();
			Assert::IsTrue(stringListIterator.GetCurrent() == "String 1");
		}

		TEST_METHOD(ForwardIteratorDereferenceTest)
		{
			CrtCheckMemory check;
			DList<size_t> intList;
			intList.Append(10);
			ForwardIterator<size_t> listIterator;
			listIterator = intList.getHead();
			Assert::IsTrue(*listIterator == 10);
		}

		TEST_METHOD(ForwardIteratorStringDereferenceTest)
		{
			CrtCheckMemory check;
			DList<string> stringList;
			stringList.Append("Test String");
			ForwardIterator<string> stringIterator;
			stringIterator = stringList.getHead();
			Assert::IsTrue(*stringIterator == "Test String");
		}

		TEST_METHOD(ForwardIteratorMoveNextTest)
		{
			CrtCheckMemory check;
			DList<size_t> intList;
			for (size_t i = 0; i < 10; i++)
				intList.Append(i);
			ForwardIterator<size_t> listIterator;
			listIterator = intList.getHead();
			for (size_t i = 0; i < 10; i++)
				listIterator.MoveNext();
			Assert::IsTrue(listIterator.GetCurrent() == 9);
		}

		TEST_METHOD(ForwardIteratorStringMoveNextTest)
		{
			CrtCheckMemory check;
			DList<string> stringList;
			stringList.Append("String 1");
			stringList.Append("String 2");
			ForwardIterator<string> stringListIterator;
			stringListIterator = stringList.getHead();
			stringListIterator.MoveNext();
			Assert::IsTrue(stringListIterator.GetCurrent() == "String 2");
		}

		TEST_METHOD(ForwardIteratorIsDoneTest)
		{
			CrtCheckMemory check;
			DList<int> intList;
			intList.Append(1);
			ForwardIterator<int> listIterator;
			listIterator = intList.getHead();

			Assert::IsTrue(listIterator.GetCurrent() == 1 && listIterator.IsDone());
		}

		TEST_METHOD(ForwardIteratorStringIsDoneTest)
		{
			CrtCheckMemory check;
			DList<string> stringList;
			stringList.Append("Test String");
			ForwardIterator<string> stringIterator;
			stringIterator = stringList.getHead();

			Assert::IsTrue(stringIterator.GetCurrent() == "Test String" && stringIterator.IsDone());
		}

		TEST_METHOD(ForwardIteratorResetTest)
		{
			CrtCheckMemory check;
			DList<size_t> intList;
			for (size_t i = 0; i < 10; i++)
				intList.Append(i);
			ForwardIterator<size_t> listIterator;
			listIterator = intList.getHead();
			for (size_t i = 0; !listIterator.IsDone(); i++)
				listIterator.MoveNext();
			if (listIterator.GetCurrent() == 9)
			{
				listIterator.Reset();
				Assert::IsTrue(listIterator.GetCurrent() == 0);
			}
		}

		TEST_METHOD(ForwardIteratorStringResetTest)
		{
			CrtCheckMemory check;
			DList<string> stringList;
			for (size_t i = 0; i < 10; i++)
				stringList.Append("String " + std::to_string(i));
			ForwardIterator<string> stringIterator;
			stringIterator = stringList.getHead();
			for (size_t i = 0; !stringIterator.IsDone(); i++)
				stringIterator.MoveNext();
			if (stringIterator.GetCurrent() == "String 9")
			{
				stringIterator.Reset();
				Assert::IsTrue(stringIterator.GetCurrent() == "String 0");
			}
		}

		TEST_METHOD(ForwardIteratorAssignmentOperatorTest)
		{
			CrtCheckMemory check;
			DList<size_t> intList;
			intList.Append(10);
			ForwardIterator<size_t> listIterator;
			listIterator = intList.getHead();
			Assert::IsTrue(listIterator.GetCurrent() == 10);
		}

		TEST_METHOD(ForwardIteratorStringAssignmentOperatorTest)
		{
			CrtCheckMemory check;
			DList<string> stringList;
			stringList.Append("Test String");
			ForwardIterator<string> stringIterator;
			stringIterator = stringList.getHead();
			Assert::IsTrue(stringIterator.GetCurrent() == "Test String");
		}

		TEST_METHOD(ForwardIteratorIncrementTest)
		{
			CrtCheckMemory check;
			DList<size_t> intList;
			intList.Append(5);
			intList.Append(10);
			intList.Append(15);
			ForwardIterator<size_t> listIterator;
			listIterator = intList.getHead();
			if (listIterator.GetCurrent() == 5)
				listIterator++;
			if (listIterator.GetCurrent() == 10)
				listIterator++;
			if (listIterator.GetCurrent() == 15)
				Assert::IsTrue(true);
		}

		TEST_METHOD(ForwardIteratorStringIncrementTest)
		{
			CrtCheckMemory check;
			DList<string> stringList;
			for (size_t i = 0; i < 3; i++)
				stringList.Append("String " + std::to_string(i));
			ForwardIterator<string> stringIterator;
			stringIterator = stringList.getHead();
			if (stringIterator.GetCurrent() == "String 0")
				stringIterator++;
			if (stringIterator.GetCurrent() == "String 1")
				stringIterator++;
			if (stringIterator.GetCurrent() == "String 2")
				Assert::IsTrue(true);
		}

		TEST_METHOD(ForwardIteratorComprehensiveTest)
		{
			CrtCheckMemory check;
			DList<int> intList;
			for (size_t i = 0; i < 100; i++)
				intList.Append(static_cast<int>(i));
			ForwardIterator<int> listIterator;
			listIterator = intList.getHead();
			if (*listIterator == 0)
				while (!listIterator.IsDone())
					listIterator++;
			if (listIterator.GetCurrent() == 99)
				listIterator.Reset();
			listIterator.MoveNext();
			Assert::IsTrue(*listIterator == 1);
		}
	};
}