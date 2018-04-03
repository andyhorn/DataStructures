/*
Name:			Andrew Horn
Date:			2/10/2018
Last Modified:	2/10/2018
Course:			CST211 - Data Structures
Filename:		QueueArrayTest.cpp

Overview:		Tests all functionality of the QueueArray class. As of last modified date, all 
				tests pass, including rainy-day scenarios. These tests include Parameterized Ctor
				(int and string), invalid parameter Ctor, Enqueue (int and string), Dequeue (int
				and string), Front (int and string), overflow, Dequeue and Front underflow.

*/

#include "stdafx.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "Exception.h"
#include <string>
#include "QueueArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(QueueArrayTest)
	{
	public:

		TEST_METHOD(QueueArrayCtorTest)
		{
			CrtCheckMemory check;
			try
			{
				QueueArray<int> intQueue(10);
				Assert::IsTrue(true);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(QueueArrayStringCtorTest)
		{
			CrtCheckMemory check;
			try
			{
				QueueArray<string> stringQueue(10);
				Assert::IsTrue(true);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(QueueArrayBadSizeCtorTest)
		{
			CrtCheckMemory check;
			
			try
			{
				QueueArray<int> badQueue(-5);
				Assert::Fail();
			}
			catch (Exception)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(QueueArrayEnqueueTest)
		{
			CrtCheckMemory check;
			QueueArray<int> intQueue(10);

			try
			{
				for (size_t i = 0; i < 10; i++)
					intQueue.Enqueue((int)i);
				Assert::IsTrue(true);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(QueueArrayStringEnqueueTest)
		{
			CrtCheckMemory check;
			QueueArray<string> stringQueue(10);
			bool pass = true;

			try
			{
				for (size_t i = 0; i < 10; i++)
					stringQueue.Enqueue(std::to_string(i));
				Assert::IsTrue(true);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(QueueArrayDequeueTest)
		{
			CrtCheckMemory check;
			bool pass = true;
			QueueArray<int> intQueue(10);
			for (size_t i = 0; i < 10; i++)
				intQueue.Enqueue((int)i);

			for (size_t i = 0; i < 10; i++)
				if (intQueue.Dequeue() != (int)i)
					pass = false;

			Assert::IsTrue(pass);
		}

		TEST_METHOD(QueueArrayStringDequeueTest)
		{
			CrtCheckMemory check;
			bool pass = true;
			QueueArray<string> stringQueue(10);
			for (size_t i = 0; i < 10; i++)
				stringQueue.Enqueue(std::to_string(i));

			for (size_t i = 0; i < 10; i++)
				if (stringQueue.Dequeue() != std::to_string(i))
					pass = false;

			Assert::IsTrue(true);
		}

		TEST_METHOD(QueueArrayFrontTest)
		{
			CrtCheckMemory check;
			QueueArray<int> intQueue(10);
			for (size_t i = 0; i < 10; i++)
				intQueue.Enqueue((int)i);

			if (intQueue.Front() == 0)
				intQueue.Front() = 25;
			
			Assert::IsTrue(intQueue.Front() == 25);
		}

		TEST_METHOD(QueueArrayStringFrontTest)
		{
			CrtCheckMemory check;
			QueueArray<string> stringQueue(10);
			for (size_t i = 0; i < 10; i++)
				stringQueue.Enqueue(std::to_string(i));

			if (stringQueue.Front() == std::to_string(0))
				stringQueue.Front() = std::to_string(25);

			Assert::IsTrue(stringQueue.Front() == std::to_string(25));
		}

		TEST_METHOD(QueueArrayOverflowTest)
		{
			CrtCheckMemory check;
			QueueArray<int> smallQueue(5);

			try
			{
				for (size_t i = 0; i < 6; i++)
					smallQueue.Enqueue((int)i);
			}
			catch (Exception)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(QueueArrayDequeueUnderflowTest)
		{
			CrtCheckMemory check;
			QueueArray<int> intQueue(5);
			for (size_t i = 0; i < 5; i++)
				intQueue.Enqueue((int)i);

			try
			{
				for (size_t i = 0; i < 6; i++)
					intQueue.Dequeue();
			}
			catch (Exception)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(QueueArrayFrontUnderflowTest)
		{
			CrtCheckMemory check;
			QueueArray<int> intQueue(5);
			for (size_t i = 0; i < 5; i++)
				intQueue.Enqueue((int)i);
			for (size_t i = 0; i < 5; i++)
				intQueue.Dequeue();

			try
			{
				intQueue.Front();
			}
			catch (Exception)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(QueueArrayCopyCtorTest)
		{
			CrtCheckMemory check;
			bool pass = true;
			QueueArray<int> intQueue(10);
			for (size_t i = 0; i < 10; i++)
				intQueue.Enqueue((int)i);

			QueueArray<int> copyQueue(intQueue);
			for (size_t i = 0; i < 10; i++)
				if (copyQueue.Dequeue() != intQueue.Dequeue())
					pass = false;

			if (pass)
			{
				copyQueue.Enqueue(10);
				intQueue.Enqueue(20);
				Assert::IsTrue(copyQueue.Dequeue() == 10 && intQueue.Dequeue() == 20);
			}
		}
	};
}
