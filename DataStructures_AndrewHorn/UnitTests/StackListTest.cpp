/*
Name:			Andrew Horn
Date:			2/10/2018
Last Modified:	2/10/2018
Course:			CST211 - Data Structures
Filename:		StackListTest.cpp

Overview:		Tests all functionality of the StackList class. As of last modified date,
				all tests pass. Tests include default ctor (int and string), Push (int 
				and string), Pop (int and string), Peek (int and string), copy ctor, 
				underflow.
*/

#include "stdafx.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "Exception.h"
#include <string>
#include "StackList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(StackListTest)
	{
	public:

		TEST_METHOD(StackListCtorTest)
		{
			CrtCheckMemory check;
			StackList<int> intStack;
			Assert::IsTrue(intStack.Size() == 0);
		}

		TEST_METHOD(StackListStringCtorTest)
		{
			CrtCheckMemory check;
			StackList<string> stringStack;
			Assert::IsTrue(stringStack.Size() == 0);
		}

		TEST_METHOD(StackListPushTest)
		{
			CrtCheckMemory check;

			StackList<int> intStack;
			for (size_t i = 0; i < 10; i++)
				intStack.Push((int)i);

			Assert::IsTrue(intStack.Size() == 10);
		}

		TEST_METHOD(StackListStringPushTest)
		{
			CrtCheckMemory check;

			StackList<string> stringStack;
			for (size_t i = 0; i < 10; i++)
				stringStack.Push("Test String");

			Assert::IsTrue(stringStack.Size() == 10);
		}

		TEST_METHOD(StackListPopTest)
		{
			CrtCheckMemory check;
			bool pass = true;

			StackList<int> intStack;
			for (size_t i = 0; i < 10; i++)
				intStack.Push((int)i);

			for (size_t i = 10; i > 0; i--)
			{
				if (intStack.Pop() != (int)i - 1)
					pass = false;
			}
				
			Assert::IsTrue(pass);
		}

		TEST_METHOD(StackListUnderflowTest)
		{
			CrtCheckMemory check;
			bool underflow = true;

			StackList<int> smallStack;
			for (size_t i = 0; i < 5; i++)
				smallStack.Push((int)i);

			if (smallStack.Size() == 5)
			{
				try
				{
					for (size_t i = 0; i < 6; i++)
						smallStack.Pop();
				}
				catch (Exception)
				{
					Assert::IsTrue(underflow);
				}
			}
		}

		TEST_METHOD(StackListStringPopTest)
		{
			CrtCheckMemory check;
			bool pass = true;

			StackList<string> stringStack;
			for (size_t i = 0; i < 10; i++)
				stringStack.Push(std::to_string(i));

			for (size_t i = 10; i > 0; i--)
				if (stringStack.Pop() != std::to_string(i - 1))
					pass = false;

			Assert::IsTrue(pass);
		}

		TEST_METHOD(StackListPeekTest)
		{
			CrtCheckMemory check;
			bool pass = true;

			StackList<int> intStack;
			for (size_t i = 0; i < 10; i++)
				intStack.Push((int)i);

			for (size_t i = 10; i > 0; i--, intStack.Pop())
				if (intStack.Peek() != (int)i - 1)
					pass = false;

			Assert::IsTrue(pass);
		}

		TEST_METHOD(StackListStringPeekTest)
		{
			CrtCheckMemory check;
			bool pass = true;

			StackList<string> stringStack;
			for (size_t i = 0; i < 10; i++)
				stringStack.Push(std::to_string(i));

			for (size_t i = 10; i > 0; i--, stringStack.Pop())
				if (stringStack.Peek() != std::to_string(i - 1))
					pass = false;

			Assert::IsTrue(pass);
		}

		TEST_METHOD(StackListCopyCtorTest)
		{
			CrtCheckMemory check;
			bool pass = true;
			StackList<int> intStack;
			for (size_t i = 0; i < 10; i++)
				intStack.Push((int)i);

			try
			{
				StackList<int> copyStack(intStack);
				for (size_t i = 0; i < 10; i++)
					if (copyStack.Pop() != intStack.Pop())
						pass = false;

				if (pass)
				{
					intStack.Push(10);
					copyStack.Push(20);
					Assert::IsTrue(intStack.Pop() == 10 && copyStack.Pop() == 20);
				}
			}
			catch (Exception &e)
			{
				cout << e;
			}
		}

		TEST_METHOD(StackListStringCopyCtorTest)
		{
			CrtCheckMemory check;
			bool pass = true;
			StackList<string> stringStack;
			for (size_t i = 0; i < 10; i++)
				stringStack.Push("Test String " + std::to_string(i));

			try
			{
				StackList<string> copyString(stringStack);
				for (size_t i = 0; i < 10; i++)
					if (copyString.Pop() != stringStack.Pop())
						pass = false;

				if (pass)
				{
					copyString.Push("Copy String Test");
					stringStack.Push("String Stack Test");
					Assert::IsTrue(copyString.Pop() == "Copy String Test"
						&& stringStack.Pop() == "String Stack Test");
				}
			}
			catch (Exception &e)
			{
				cout << e;
			}
		}
	};
}
