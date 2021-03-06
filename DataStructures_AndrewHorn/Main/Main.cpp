#include "CrtDbg.h"
#include <iostream>
#include "Pair.h"
#include "Array.h"

#define _CRTDBG_MAP_ALLOC

void TestCopyConstructor();
void TestArrayConstructor();
void TestArrayCopyConstructor();


int main()
{
	{
		TestCopyConstructor();
	}
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();

	std::cin.get();
    return 0;
}

void TestCopyConstructor()
{
	// Arrange
	Pair<int, int> pair1(5, 10);

	// Act
	Pair<int, int> pair2(pair1);


	// Assert
	bool pass = (pair1.GetKey() == pair2.GetKey() && 
				pair1.GetValue() == pair2.GetValue()) 
		? true : false;

	if (pass)
	{
		std::cout << "TestCopyConstructor() PASS" << std::endl;
	}
	else
	{
		std::cout << "TestCopyConstructor() FAIL" << std::endl;
	}

}
