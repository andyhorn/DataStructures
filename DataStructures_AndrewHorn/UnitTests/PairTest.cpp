#include "stdafx.h"
#include "CppUnitTest.h"

#include "CrtCheckMemory.h"
#include "Pair.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{		
	TEST_CLASS(PairTest)
	{
	public:
		
		TEST_METHOD(PairCopyConstructorTest)
		{
			// Arrange
			CrtCheckMemory check;
			Pair<int, int> pair1(5, 10);

			// Act
			Pair<int, int> pair2(pair1);

			// Assert
			pair1.SetKey(1);
			pair1.SetValue(2);
			Assert::IsTrue(pair1.GetKey() != pair2.GetKey() && pair1.GetValue() != pair2.GetValue());
		}

		TEST_METHOD(PairAssignmentOpTest)
		{
			CrtCheckMemory check;
			Pair<int, int> pair1(5, 10);
			Pair<int, int> pair2;

			pair2 = pair1;
			pair1.SetKey(1);
			pair1.SetValue(1);
			Assert::IsTrue(pair1.GetKey() != pair2.GetKey() && pair1.GetValue() != pair2.GetValue());
		}

		TEST_METHOD(PairIsEqualTest)
		{
			CrtCheckMemory check;
			Pair<int, int> pair1(5, 10);
			Pair<int, int> pair2(5, 10);

			Assert::IsTrue(pair1 == pair2);
		}

		TEST_METHOD(PairStringCopyConstructorTest)
		{
			CrtCheckMemory check;
			Pair<string, string> stringPair1("String1", "String2");
			Pair<string, string> stringPair2(stringPair1);

			stringPair1.SetKey("New String 1");
			stringPair1.SetValue("New String 2");

			Assert::IsTrue(stringPair1.GetKey() != stringPair2.GetKey() && stringPair1.GetValue() != stringPair2.GetValue());
		}

		TEST_METHOD(PairStringAssignmentOpTest)
		{
			CrtCheckMemory check;
			Pair<string, string> stringPair1("String 1", "String 2");
			Pair<string, string> stringPair2;

			stringPair2 = stringPair1;
			
			Assert::IsTrue(stringPair1.GetKey() == stringPair2.GetKey() && stringPair1.GetValue() == stringPair2.GetValue());
		}

		TEST_METHOD(PairStringIsEqualTest)
		{
			CrtCheckMemory check;
			Pair<string, string> stringPair1("String 1", "String 2");
			Pair<string, string> stringPair2("String 3", "String 4");

			Assert::IsTrue(!(stringPair1 == stringPair2));
		}

		TEST_METHOD(PairDoubleStringPairSetTest)
		{
			CrtCheckMemory check;
			Pair<string, string> stringPair1("String 1", "String 2");
			Pair<string, string> stringPair2("String 3", "String 4");
			Pair<Pair<string, string>, Pair<string, string>> inceptionStringPair;
			inceptionStringPair.SetKey(stringPair1);
			inceptionStringPair.SetValue(stringPair2);


			Assert::IsTrue(inceptionStringPair.GetKey() == stringPair1 && inceptionStringPair.GetValue() == stringPair2);
		}

		TEST_METHOD(PairMemoryLeakTest)
		{
			CrtCheckMemory check;
			Pair<int, int> *pairPointer1 = new Pair<int, int>;
			Pair<string, string> *pairPointer2 = new Pair<string, string>;
			delete pairPointer1;
			delete pairPointer2;
			Assert::IsTrue(true);
		}
	};
}