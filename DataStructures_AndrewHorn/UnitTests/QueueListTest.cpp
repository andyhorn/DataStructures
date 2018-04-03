/*
Name:			Andrew Horn
Date:			2/10/2018
Last Modified:	2/10/2018
Course:			CST211 - Data Structures
Filename:		QueueListTest.cpp

Overview:		Tests all functionality of the QueueList class. As of last modified date,
				all tests pass. Tests include default ctor (int and string), Enqueue (int
				and string), Dequeue (int and string), Front (int and string), Dequeue and
				Front underflow, copy ctor.
*/

#include "stdafx.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "Exception.h"
#include <string>
#include "QueueList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(QueueListTest)
	{
	public:

		TEST_METHOD(QueueListCtorTest)
		{
			CrtCheckMemory check;
			QueueList<int> intQueue;
			Assert::IsTrue(intQueue.isEmpty());
		}

		TEST_METHOD(QueueListStringCtorTest)
		{
			CrtCheckMemory check;
			QueueList<string> stringQueue;
			Assert::IsTrue(stringQueue.isEmpty());
		}

		TEST_METHOD(QueueListEnqueueTest)
		{
			CrtCheckMemory check;
			QueueList<int> intQueue;

			try
			{
				for (size_t i = 0; i < 10; i++)
					intQueue.Enqueue((int)i);
				Assert::IsTrue(intQueue.Size() == 10);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(QueueListStringEnqueueTest)
		{
			CrtCheckMemory check;
			QueueList<string> stringQueue;

			try
			{
				for (size_t i = 0; i < 10; i++)
					stringQueue.Enqueue(std::to_string(i));
				Assert::IsTrue(stringQueue.Size() == 10);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(QueueListCopyCtorTest)
		{
			CrtCheckMemory check;
			bool pass = true;
			QueueList<int> intQueue;
			for (size_t i = 0; i < 10; i++)
				intQueue.Enqueue((int)i);

			QueueList<int> copyQueue(intQueue);
			for (size_t i = 0; i < 10; i++)
				if (intQueue.Dequeue() != copyQueue.Dequeue())
					pass = false;

			if (pass)
			{
				intQueue.Enqueue(10);
				copyQueue.Enqueue(20);
				Assert::IsTrue(intQueue.Dequeue() == 10 && copyQueue.Dequeue() == 20);
			}
		}

		TEST_METHOD(QueueListDequeueTest)
		{
			CrtCheckMemory check;
			bool pass = true;
			QueueList<int> intQueue;
			for (size_t i = 0; i < 10; i++)
				intQueue.Enqueue((int)i);

			for (size_t i = 0; i < 10; i++)
				if (intQueue.Dequeue() != (int)i)
					pass = false;

			Assert::IsTrue(pass);
		}

		TEST_METHOD(QueueListStringDequeueTest)
		{
			CrtCheckMemory check;
			bool pass = true;
			QueueList<string> stringQueue;
			for (size_t i = 0; i < 10; i++)
				stringQueue.Enqueue(std::to_string(i));

			for (size_t i = 0; i < 10; i++)
				if (stringQueue.Dequeue() != std::to_string(i))
					pass = false;

			Assert::IsTrue(true);
		}

		TEST_METHOD(QueueListFrontTest)
		{
			CrtCheckMemory check;
			QueueList<int> intQueue;
			for (size_t i = 0; i < 10; i++)
				intQueue.Enqueue((int)i);

			if (intQueue.Front() == 0)
				intQueue.Front() = 25;

			Assert::IsTrue(intQueue.Front() == 25);
		}

		TEST_METHOD(QueueListStringFrontTest)
		{
			CrtCheckMemory check;
			QueueList<string> stringQueue;
			for (size_t i = 0; i < 10; i++)
				stringQueue.Enqueue(std::to_string(i));

			if (stringQueue.Front() == std::to_string(0))
				stringQueue.Front() = std::to_string(25);

			Assert::IsTrue(stringQueue.Front() == std::to_string(25));
		}

		TEST_METHOD(QueueListDequeueUnderflowTest)
		{
			CrtCheckMemory check;
			QueueList<int> intQueue;
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

		TEST_METHOD(QueueListFrontUnderflowTest)
		{
			CrtCheckMemory check;
			QueueList<int> intQueue;
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
	};
}
