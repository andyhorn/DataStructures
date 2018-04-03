#include "stdafx.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "Array2DP.h"
#include "Exception.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(Array2DPTest)
	{
	public:
		
		TEST_METHOD(Array2DPDefaultCtorTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray;
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DPStringDefaultCtorTest)
		{
			CrtCheckMemory check;
			Array2DP<string> myStringArray;
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DPParameterCtorGoodTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			Assert::IsTrue(myArray.getCol() == 3 && myArray.getRow() == 3);
		}

		TEST_METHOD(Array2DPStringParameterCtorGoodTest)
		{
			CrtCheckMemory check;
			Array2DP<string> myStringArray(3, 3);
			Assert::IsTrue(myStringArray.getCol() == 3 && myStringArray.getRow() == 3);
		}

		TEST_METHOD(Array2DPParameterCtorBadRowTest)
		{
			CrtCheckMemory check;
			try
			{
				Array2DP<int> myArray(-1, 3);
			}
			catch (Exception)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DPParameterCtorBadColTest)
		{
			CrtCheckMemory check;
			try
			{
				Array2DP<int> myArray(3, -1);
			}
			catch (Exception)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DPCopyCtorTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			Array2DP<int> copyArray(myArray);
			Assert::IsTrue(copyArray.getRow() == 3 && copyArray.getCol() == 3);
		}

		TEST_METHOD(Array2DPStringCopyCtorTest)
		{
			CrtCheckMemory check;
			Array2DP<string> myStringArray(3, 3);
			Array2DP<string> copyStringArray(myStringArray);
			Assert::IsTrue(copyStringArray.getRow() == 3 && copyStringArray.getCol() == 3);
		}

		TEST_METHOD(Array2DPAssignmentOpTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			for (int row = 0, count = 0; row < 3; row++)
				for (int col = 0; col < 3; col++)
					myArray[row][col] = count++;
			Array2DP<int> copyArray;
			copyArray = myArray;
			Assert::IsTrue(copyArray.getRow() == 3 && copyArray.getCol() == 3);
		}

		TEST_METHOD(Array2DPStringAssignmentOpTest)
		{
			CrtCheckMemory check;
			Array2DP<string> myStringArray(3, 3);
			Array2DP<string> copyStringArray;
			copyStringArray = myStringArray;
			Assert::IsTrue(copyStringArray.getRow() == 3 && copyStringArray.getCol() == 3);
		}

		TEST_METHOD(Array2DPSubscriptOpTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			myArray[0][0] = 1;
			Assert::IsTrue(myArray[0][0] == 1);
		}

		TEST_METHOD(Array2DPStringSubscriptOpTest)
		{
			CrtCheckMemory check;
			Array2DP<string> myStringArray(3, 3);
			myStringArray[0][0] = "Test String.";
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DPSubscriptOpBadRowTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			try
			{
				myArray[-1][0] = 1;
			}
			catch (Exception)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DPSubscriptOpBadColTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			try
			{
				myArray[0][-1] = 1;
			}
			catch (Exception)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DPSetRowTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			myArray.setRow(4);
			Assert::IsTrue(myArray.getRow() == 4);
		}

		TEST_METHOD(Array2DPSetColTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			myArray.setCol(4);
			Assert::IsTrue(myArray.getCol() == 4);
		}

		TEST_METHOD(Array2DPSetRowDataLossTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			int count = 0;
			for (int row = 0; row < 3; row++)
				for (int col = 0; col < 3; col++)
					myArray[row][col] = count++;
			// 0 1 2 
			// 3 4 5
			// 6 7 8
			// Total = 36

			myArray.setRow(2);
			// 0 1 2
			// 3 4 5
			// Total = 15
			count = 0;
			for (int row = 0; row < myArray.getRow(); row++)
				for (int col = 0; col < myArray.getCol(); col++)
					count += myArray[row][col];
			Assert::IsTrue(count == 15);
		}

		TEST_METHOD(Array2DPSetColDataLossTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			int count = 0;
			for (int row = 0; row < 3; row++)
				for (int col = 0; col < 3; col++)
					myArray[row][col] = count++;
			// 0 1 2
			// 3 4 5
			// 6 7 8
			// Total = 36

			myArray.setCol(2);
			// 0 1
			// 3 4
			// 6 7
			// Total = 21

			count = 0;
			for (int row = 0; row < myArray.getRow(); row++)
				for (int col = 0; col < myArray.getCol(); col++)
					count += myArray[row][col];

			Assert::IsTrue(count == 21);
		}

		TEST_METHOD(Array2DPResizeDataLossTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(5, 5);
			int count = 0;
			for (int row = 0; row < 5; row++)
				for (int col = 0; col < 5; col++)
					myArray[row][col] = count++;
			// 0 1 2 3 4
			// 5 6 7 8 9
			// 10 11 12 13 14
			// 15 16 17 18 19
			// 20 21 22 23 24
			// Total = 300

			myArray.setRow(3);
			myArray.setCol(3);
			// 0 1 2
			// 5 6 7
			// 10 11 12
			// Total = 54
			count = 0;
			for (int row = 0; row < myArray.getRow(); row++)
				for (int col = 0; col < myArray.getCol(); col++)
					count += myArray[row][col];

			Assert::IsTrue(count == 54);
		}

		TEST_METHOD(Array2DPSetRowGrowthTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			myArray.setRow(5);
			myArray[4][0] = 1;
			Assert::IsTrue(myArray.getRow() == 5 && myArray[4][0] == 1);
		}

		TEST_METHOD(Array2DPSetColGrowthTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			myArray.setCol(5);
			myArray[0][4] = 1;
			Assert::IsTrue(myArray.getCol() == 5 && myArray[0][4] == 1);
		}

		TEST_METHOD(Array2DPSetRowBadTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			try
			{
				myArray.setRow(-1);
			}
			catch (Exception)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DPSetColBadTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			try
			{
				myArray.setCol(-1);
			}
			catch (Exception)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DPSelectTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			myArray[0][0] = 1;
			Assert::IsTrue(myArray.Select(0, 0));
		}
	};
}
