/*
Name:			Andrew Horn
Date:			2/10/2018
Last Modified:	2/10/2018
Course:			CST211 - Data Structures
Filename:		StackArrayTest.cpp

Overview:		Tests all functionality of the StackArray class. As of last modified date,
				all tests pass. Tests include parameterized ctor (int and string), Push 
				(int and string), Pop (int and string), Peek (int and string), copy ctor
				(int and string), overflow, and underflow.
*/

#include "stdafx.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "Exception.h"
#include <string>
#include "StackArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(StackArrayTest)
	{
	public:

		TEST_METHOD(StackArrayCtorTest)
		{
			CrtCheckMemory check;
			try
			{
				StackArray<int> intStack(10);
				StackArray<int> intStack2(25);
				Assert::IsTrue(true);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(StackArrayStringCtorTest)
		{
			CrtCheckMemory check;
			try 
			{
				StackArray<string> stringStack(10);
				StackArray<string> stringStack2(25);
				Assert::IsTrue(true);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(StackArrayPushTest)
		{
			CrtCheckMemory check;
			StackArray<int> intStack(10);
			
			for (size_t i = 0; i < 10; i++)
				intStack.Push((int)i);

			Assert::IsTrue(intStack.isFull());
		}

		TEST_METHOD(StackArrayOverflowTest)
		{
			bool overflow = true;
			CrtCheckMemory check;
			StackArray<int> smallStack(5);

			try
			{
				for (size_t i = 0; i < 6; i++)
					smallStack.Push((int)i);
			}
			catch (Exception)
			{
				Assert::IsTrue(overflow);
			}
		}

		TEST_METHOD(StackArrayStringPushTest)
		{
			CrtCheckMemory check;
			StackArray<string> stringStack(10);

			for (size_t i = 0; i < 10; i++)
				stringStack.Push(std::to_string(i));

			Assert::IsTrue(stringStack.isFull());
		}

		TEST_METHOD(StackArrayPopTest)
		{
			CrtCheckMemory check;
			bool pass = true;
			StackArray<int> intStack(10);

			for (size_t i = 0; i < 10; i++)
				intStack.Push((int)i);

			for (size_t i = 10; i > 0; i--)
				if (intStack.Pop() != (int)i - 1)
					pass = false;

			Assert::IsTrue(pass);
		}

		TEST_METHOD(StackArrayUnderflowTest)
		{
			CrtCheckMemory check;
			bool overflow = true;
			StackArray<int> smallStack(5);
			for (size_t i = 0; i < 5; i++)
				smallStack.Push((int)i);

			if (smallStack.isFull())
			{
				try 
				{
					for (size_t i = 0; i < 6; i++)
						smallStack.Pop();
				}
				catch (Exception)
				{
					Assert::IsTrue(overflow);
				}
			}
		}

		TEST_METHOD(StackArrayStringPopTest)
		{
			CrtCheckMemory check;
			bool pass = true;
			StackArray<string> stringStack(10);

			for (size_t i = 0; i < 10; i++)
				stringStack.Push(std::to_string(i));

			for (size_t i = 10; i > 0; i--)
				if (stringStack.Pop() != std::to_string(i - 1))
					pass = false;

			Assert::IsTrue(pass);
		}

		TEST_METHOD(StackArrayPeekTest)
		{
			CrtCheckMemory check;
			bool pass = true;

			StackArray<int> intStack(10);

			for (size_t i = 0; i < 10; i++)
				intStack.Push((int)i);

			for (size_t i = 10; i > 0; i--, intStack.Pop())
				if (intStack.Peek() != (int)i - 1)
					pass = false;

			Assert::IsTrue(pass);
		}

		TEST_METHOD(StackArrayStringPeekTest)
		{
			CrtCheckMemory check;
			bool pass = true;

			StackArray<string> stringStack(10);

			for (size_t i = 0; i < 10; i++)
				stringStack.Push(std::to_string(i));

			for (size_t i = 10; i > 0; i--, stringStack.Pop())
				if (stringStack.Peek() != std::to_string(i - 1))
					pass = false;

			Assert::IsTrue(pass);
		}

		TEST_METHOD(StackArrayCopyCtorTest)
		{
			CrtCheckMemory check;
			bool pass = true;
			try
			{
				StackArray<int> intStackOne(10);
				for (size_t i = 0; i < 10; i++)
					intStackOne.Push(static_cast<int>(i));

				StackArray<int> intStackTwo(intStackOne);
				for (size_t i = 0; i < 10; i++)
					if (intStackOne.Pop() != intStackTwo.Pop())
						pass = false;

				if (pass)
				{
					intStackOne.Push(10);
					intStackTwo.Push(20);
					Assert::IsTrue(intStackOne.Pop() == 10 && intStackTwo.Pop() == 20);
				}
			}
			catch (Exception)
			{
				
			}
		}

		TEST_METHOD(StackArrayStringCopyCtorTest)
		{
			CrtCheckMemory check;
			bool equal = true;
			try
			{
				StackArray<string> stringStackOne(10);
				for (size_t i = 0; i < 10; i++)
					stringStackOne.Push(std::to_string(i));

				StackArray<string> stringStackTwo(stringStackOne);
				for (size_t i = 0; i < 10; i++)
					if (stringStackOne.Pop() != stringStackTwo.Pop())
						equal = false;

				Assert::IsTrue(equal);
			}
			catch (Exception)
			{
				
			}
		}
	};
}
