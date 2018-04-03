#include <crtdbg.h>
#include "Windows.h"
#include <cassert>
#include <iostream>
#include "DList.h"  // Change to your Linked List Header
#include "Exception.h"

#define _CRTDBG_MAP_ALLOC

const size_t GREEN = 10;
const size_t RED = 12;
const size_t WHITE = 23;
static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void RunTests();
void PrintTestHeader(const char *);
void PrintTestPass(const char *);
void PrintTestFail(const char *, const char *);
void TestConstructor();
void TestCopyConstructor();
void TestAppend();
void TestFirstAndLast();
void TestPrepend();
void TestPurge();
void TestInsertBefore();
void TestInsertAfter();
void TestExtract();
void TestAssignmentOperator();
void TestAccessors();

int main()
{
	RunTests();

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();

	system("pause");
	return 0;
}

void RunTests()
{
	SetConsoleTextAttribute(hConsole, WHITE);
	TestConstructor();
	TestCopyConstructor();
	TestAppend();
	TestFirstAndLast();
	TestPrepend();
	TestPurge();
	TestInsertBefore();
	TestInsertAfter();
	TestExtract();
	TestAssignmentOperator();
	TestAccessors();
}

void PrintTestHeader(const char *testName)
{
	std::cout << "\n********** " << testName << " **********" << std::endl;
}

void PrintTestPass(const char * test)
{
	SetConsoleTextAttribute(hConsole, GREEN);
	std::cout << "\t" << test << ": TEST PASS" << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
}

void PrintTestFail(const char * test, const char * message)
{
	SetConsoleTextAttribute(hConsole, RED);
	std::cerr << message << std::endl;
	std::cerr << "\t" << test << ": TEST FAIL" << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
}

void TestConstructor()
{
	const char * test = "Constructor";
	PrintTestHeader(test);

	try
	{
		DList<int> list;

		assert(list.isEmpty() == true);
		assert(list.getHead() == nullptr);

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestCopyConstructor()
{
	const char * test = "Copy Constructor";
	PrintTestHeader(test);

	try
	{
		DList<int> aList;
		aList.Append(5);

		DList<int> bList(aList);

		assert(bList.isEmpty() != true);
		assert(bList.First() == 5);

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestAssignmentOperator()
{
	const char * test = "Assignment Operator";
	PrintTestHeader(test);

	try
	{
		DList<size_t> aList;
		DList<size_t> bList;

		size_t i;

		size_t values[] = { 5, 15, 25, 35, 45 };

		for (i = 0; i < 5; ++i)
		{
			aList.Append(values[i]);
		}

		bList = aList;

		i = 0;
		for (DLNode<size_t> * node = bList.getHead(); node != nullptr; node = node->getNext())
		{
			assert(node->getData() == values[i++]);
		}

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestAccessors()
{
	const char * test = "Accessors";
	PrintTestHeader(test);

	try
	{
		DList<size_t> aList;
		size_t i;

		size_t values[] = { 5, 15, 25, 35, 45 };
		for (i = 0; i < 5; ++i)
		{
			aList.Append(values[i]);
		}

		assert(aList.getHead()->getData() == 5);
		assert(aList.getTail()->getData() == 45);

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestAppend()
{
	const char * test = "Append";
	PrintTestHeader(test);

	try
	{
		DList<size_t> aList;
		size_t i;

		size_t values[] = { 5, 15, 25, 35, 45 };
		for (i = 0; i < 5; ++i)
		{
			aList.Append(values[i]);
		}

		i = 0;
		for (DLNode<size_t> * node = aList.getHead(); node != nullptr; node = node->getNext())
		{
			assert(node->getData() == values[i++]);
		}

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestFirstAndLast()
{
	const char * test = "First and Last";
	PrintTestHeader(test);

	try
	{
		DList<size_t> aList;

		size_t values[] = { 5, 15, 25, 35, 45 };
		for (size_t i = 0; i < 5; ++i)
		{
			aList.Append(values[i]);
		}

		assert(aList.First() == 5);
		assert(aList.Last() == 45);

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestPrepend()
{
	const char * test = "Prepend";
	PrintTestHeader(test);

	try
	{
		DList<size_t> aList;
		size_t i;

		size_t values[] = { 5, 15, 25, 35, 45 };
		for (i = 0; i < 5; ++i)
		{
			aList.Prepend(values[i]);
		}

		i = 5;
		for (DLNode<size_t> * node = aList.getHead(); node != nullptr; node = node->getNext())
		{
			assert(node->getData() == values[--i]);
		}

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestPurge()
{
	const char * test = "Purge";
	PrintTestHeader(test);

	try
	{
		DList<size_t> aList;

		size_t values[] = { 5, 15, 25, 35, 45 };
		for (size_t i = 0; i < 5; ++i)
		{
			aList.Append(values[i]);
		}

		aList.Purge();

		assert(aList.getHead() == nullptr);
		assert(aList.getTail() == nullptr);
		assert(aList.isEmpty() == true);

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestInsertBefore()
{
	const char * test = "InsertBefore";
	PrintTestHeader(test);

	try
	{
		DList<size_t> aList;
		int i;

		size_t values[] = { 5, 15, 25, 35, 45 };

		aList.Append(values[4]);
		for (i = 3; i >= 0; --i)
		{
			aList.InsertBefore(values[i], values[i + 1]);
		}

		i = 0;
		for (DLNode<size_t> * node = aList.getHead(); node != nullptr; node = node->getNext())
		{
			assert(node->getData() == values[i++]);
		}

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestInsertAfter()
{
	const char * test = "InsertAfter";
	PrintTestHeader(test);

	try
	{
		DList<size_t> aList;
		int i;

		size_t values[] = { 5, 15, 25, 35, 45 };

		aList.Append(values[0]);
		for (i = 1; i < 5; ++i)
		{
			aList.InsertAfter(values[i], values[i - 1]);
		}

		i = 0;
		for (DLNode<size_t> * node = aList.getHead(); node != nullptr; node = node->getNext())
		{
			assert(node->getData() == values[i++]);
		}

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestExtract()
{
	const char * test = "Extract";
	PrintTestHeader(test);

	try
	{
		DList<size_t> list;

		list.Append(5);
		list.Extract(5);

		assert(list.isEmpty() == true);
		assert(list.getHead() == nullptr);

		list.Append(5);
		list.Append(10);
		list.Append(15);

		list.Extract(10);

		assert(list.First() == 5);
		assert(list.Last() == 15);

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}