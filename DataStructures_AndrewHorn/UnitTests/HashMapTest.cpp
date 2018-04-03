#include "stdafx.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "Exception.h"
#include "Hashmap.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	struct Book
	{
		string title;
		string author;
		int pages;
	};

	static const int TABLE_SIZE = 23;

	TEST_CLASS(HashMapTest)
	{
	public:

		TEST_METHOD(HashMapCtorTest)
		{
			CrtCheckMemory check;
			auto hashFunc = [](int key) {
				return key % TABLE_SIZE;
			};
			HashMap<int, string> hash(TABLE_SIZE, hashFunc);
			Assert::IsTrue(true);
		}

		TEST_METHOD(HashMapInsertTest)
		{
			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};

			CrtCheckMemory check;
			HashMap<int, Book> hashMap(TABLE_SIZE, hashFunc);
			Book book1 = { "Catcher in the Rye", "JD Salinger", 635 };
			Book book2 = { "The Lord of the Rings", "Tolkien", 1200 };
			Book book3 = { "IT", "Stephen King", 1300 };
			hashMap.Insert(970123456, book1);
			hashMap.Insert(970234765, book2);
			hashMap.Insert(970666666, book3);
			Assert::AreEqual(hashMap[970123456].title, book1.title);
			Assert::AreEqual(hashMap[970123456].author, book1.author);
			Assert::AreEqual(hashMap[970123456].pages, book1.pages);
			Assert::AreEqual(hashMap[970234765].title, book2.title);
			Assert::AreEqual(hashMap[970666666].title, book3.title);
		}

		TEST_METHOD(HashMapInsertFailTest)
		{
			CrtCheckMemory check;
			HashMap<int, int> failMap(TABLE_SIZE);
			try
			{
				// Haven't set a hash function yet, so inserting should throw an exception.
				failMap.Insert(5, 25000);
			}
			catch (Exception)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(HashMapCopyCtorTest)
		{
			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};

			CrtCheckMemory check;
			HashMap<int, Book> hashMap(TABLE_SIZE, hashFunc);
			Book book1 = { "Catcher in the Rye", "JD Salinger", 635 };
			Book book2 = { "The Lord of the Rings", "Tolkien", 1200 };
			Book book3 = { "IT", "Stephen King", 1300 };
			hashMap.Insert(970123456, book1);
			hashMap.Insert(970234765, book2);
			hashMap.Insert(970666666, book3);
			HashMap<int, Book> copyHash(hashMap);
			Assert::AreEqual(hashMap[970123456].title, copyHash[970123456].title);
			Assert::AreEqual(hashMap[970234765].title, copyHash[970234765].title);
			Assert::AreEqual(hashMap[970666666].title, copyHash[970666666].title);
		}

		TEST_METHOD(HashMapAssignmentTest)
		{
			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};

			CrtCheckMemory check;
			HashMap<int, Book> hashMap(TABLE_SIZE, hashFunc);
			Book book1 = { "Catcher in the Rye", "JD Salinger", 635 };
			Book book2 = { "The Lord of the Rings", "Tolkien", 1200 };
			Book book3 = { "IT", "Stephen King", 1300 };
			hashMap.Insert(970123456, book1);
			hashMap.Insert(970234765, book2);
			hashMap.Insert(970666666, book3);
			HashMap<int, Book> copyHash(10);
			copyHash = hashMap;
			Assert::AreEqual(hashMap[970123456].title, copyHash[970123456].title);
			Assert::AreEqual(hashMap[970234765].title, copyHash[970234765].title);
			Assert::AreEqual(hashMap[970666666].title, copyHash[970666666].title);
		}

		TEST_METHOD(HashMapSetHashFunctionTest)
		{
			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};

			CrtCheckMemory check;
			HashMap<int, int> hash(TABLE_SIZE);
			hash.SetHashFunc(hashFunc);
			try
			{
				hash.Insert(1111, 90000000);
				Assert::IsTrue(true);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(HashMapSetTableSizeTest)
		{
			CrtCheckMemory check;
			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};

			HashMap<int, int> hash(TABLE_SIZE, hashFunc);
			hash.Insert(10, 9374493);
			hash.Insert(55, 8329298);
			hash.Insert(41, 9823749);
			try
			{
				hash.SetTableSize(31);
				Assert::AreEqual(hash[10], 9374493);
				Assert::AreEqual(hash[55], 8329298);
				Assert::AreEqual(hash[41], 9823749);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(HashMapTraverseTest)
		{
			list<Book> books;

			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};

			auto visitFunc = [&books](Book book)
			{
				books.emplace_front(book);
			};

			CrtCheckMemory check;
			HashMap<int, Book> hashMap(TABLE_SIZE, hashFunc);
			Book book1 = { "Catcher in the Rye", "JD Salinger", 635 };
			Book book2 = { "The Lord of the Rings", "Tolkien", 1200 };
			Book book3 = { "IT", "Stephen King", 1300 };
			hashMap.Insert(970123456, book1);
			hashMap.Insert(970234765, book2);
			hashMap.Insert(970666666, book3);
			hashMap.Traverse(visitFunc);
			Assert::IsTrue(books.size() == 3);
			books.clear();
		}

		TEST_METHOD(HashMapDeleteTest)
		{
			list<Book> books;

			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};

			auto visitFunc = [&books](Book book)
			{
				books.emplace_front(book);
			};

			CrtCheckMemory check;
			HashMap<int, Book> hashMap(TABLE_SIZE, hashFunc);
			Book book1 = { "Catcher in the Rye", "JD Salinger", 635 };
			Book book2 = { "The Lord of the Rings", "Tolkien", 1200 };
			Book book3 = { "IT", "Stephen King", 1300 };
			hashMap.Insert(970123456, book1);
			hashMap.Insert(970234765, book2);
			hashMap.Insert(970666666, book3);
			hashMap.Traverse(visitFunc);

			if (books.size() == 3)
			{
				hashMap.Delete(970123456);
				books.clear();
				hashMap.Traverse(visitFunc);
				Assert::IsTrue(books.size() == 2);
			}
			books.clear();
		}

		TEST_METHOD(HashMapDifficultDeleteTest)
		{
			list<Book> books;

			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};

			auto visitFunc = [&books](Book book)
			{
				books.emplace_front(book);
			};

			CrtCheckMemory check;
			HashMap<int, Book> hashMap(TABLE_SIZE, hashFunc);
			Book book1 = { "Catcher in the Rye", "JD Salinger", 635 };
			Book book2 = { "The Lord of the Rings", "Tolkien", 1200 };
			Book book3 = { "IT", "Stephen King", 1300 };
			Book book4 = { "Holy Bible", "God", 2000 };
			hashMap.Insert(970123456, book1);
			hashMap.Insert(970234765, book2);
			hashMap.Insert(970666666, book3);
			hashMap.Insert(970123134, book4); // will place at same index as Catcher in the Rye
			hashMap.Traverse(visitFunc);

			if (books.size() == 4)
			{
				hashMap.Delete(970123134); // should delete Holy Bible, but leave Catcher in the Rye
				books.clear();
				hashMap.Traverse(visitFunc);
				Assert::IsTrue(books.size() == 3);
			}
			books.clear();
		}

		TEST_METHOD(HashmapDeleteFailTest)
		{
			CrtCheckMemory check;
			HashMap<int, int> hash(TABLE_SIZE);
			try
			{
				hash.Delete(1111111); // no hash function, will throw exception.
				Assert::Fail();
			}
			catch (Exception)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(HashmapDeleteFailTestTwo)
		{
			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};

			CrtCheckMemory check;
			HashMap<int, int> hash(TABLE_SIZE, hashFunc);
			try
			{
				hash.Delete(111111); // no item, should throw exception.
				Assert::Fail();
			}
			catch (Exception)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(HashmapCollisionReturnTest)
		{
			// Will test Hashmap's ability to return correct value when
			// keys have collided during insert.
			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};
			CrtCheckMemory check;
			HashMap<int, int> hash(TABLE_SIZE, hashFunc);
			hash.Insert(10, 99);
			hash.Insert(33, 250);
			hash.Insert(79, 567);
			// Each value placed at same location in hashmap.
			// 10 % 23 = 10, 33 % 23 = 10, 79 % 23 = 10.
			Assert::AreEqual(hash[10], 99);
			Assert::AreEqual(hash[33], 250);
			Assert::AreEqual(hash[79], 567);
		}

		TEST_METHOD(HashmapNonUniqueKeyTest)
		{
			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};

			CrtCheckMemory check;
			HashMap<int, int> hash(TABLE_SIZE, hashFunc);
			hash.Insert(200, 123456);
			try
			{
				hash.Insert(200, 98765);
				Assert::Fail();
			}
			catch (Exception)
			{
				Assert::IsTrue(true);
			}
		}
	};
}
