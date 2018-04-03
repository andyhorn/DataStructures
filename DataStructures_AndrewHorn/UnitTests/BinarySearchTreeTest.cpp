#include "stdafx.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "Exception.h"
#include <string>
#include "BinarySearchTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{

	QueueList<int> bsIntQueue;
	QueueList<string> stringQueue;

	void myIntFunc(BinarySearchNode<int> *node)
	{
		cout << node->GetDataRef() << endl;
	}

	void AddIntToQueue(BinarySearchNode<int> *node)
	{
		bsIntQueue.Enqueue(node->GetDataRef());
	}

	TEST_CLASS(BinarySearchTreeTest)
	{
	public:

		TEST_METHOD(BinarySearchTreeDefaultCtorTest)
		{
			CrtCheckMemory check;
			try
			{
				BinarySearchTree<int> myTree;
				Assert::IsTrue(true);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(BinarySearchTreeNodeCtorTest)
		{
			CrtCheckMemory check;
			try
			{
				BinarySearchTree<int>(10);
				Assert::IsTrue(true);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(BinarySearchTreeSetFunctionTest)
		{
			CrtCheckMemory check;
			try
			{
				BinarySearchTree<int> myTree;
				myTree.SetFunction(myIntFunc);
				Assert::IsTrue(true);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(BinarySearchTreeInsertTest)
		{
			CrtCheckMemory check;
			try
			{
				BinarySearchTree<int> myTree;
				myTree.Insert(25);
				myTree.Insert(50);
				myTree.Insert(12);
				myTree.Insert(99);
				myTree.Insert(6);
				Assert::IsTrue(1);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(BinarySearchTreeInOrderVisitTest)
		{
			int correctArray[6] = { 6, 12, 21, 25, 50, 99 };
			CrtCheckMemory check;
			bool pass = true;
			try
			{
				BinarySearchTree<int> myTree;
				myTree.Insert(25);
				myTree.Insert(50);
				myTree.Insert(12);
				myTree.Insert(21);
				myTree.Insert(99);
				myTree.Insert(6);
				/*
							 25
						  12    50
						6   21     99
				*/

				bsIntQueue.Purge();
				myTree.InOrder(AddIntToQueue);

				for (size_t i = 0; i < 6; i++)
					if (bsIntQueue.Dequeue() != correctArray[i])
						pass = false;

				Assert::IsTrue(pass);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(BinarySearchTreePreOrderTest)
		{
			int correctArray[6] = { 25, 12, 6, 21, 50, 99 };
			CrtCheckMemory check;
			bool pass = true;
			try
			{
				BinarySearchTree<int> myTree;
				myTree.Insert(25);
				myTree.Insert(50);
				myTree.Insert(12);
				myTree.Insert(21);
				myTree.Insert(99);
				myTree.Insert(6);
				/*
							 25
						  12    50
						6   21     99
				*/

				bsIntQueue.Purge();
				myTree.PreOrder(AddIntToQueue);

				for (size_t i = 0; i < 6; i++)
					if (bsIntQueue.Dequeue() != correctArray[i])
						pass = false;

				Assert::IsTrue(pass);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(BinarySearchTreePostOrderTest)
		{
			int correctArray[6] = { 6, 21, 12, 99, 50, 25 };
			CrtCheckMemory check;
			bool pass = true;
			try
			{
				BinarySearchTree<int> myTree;
				myTree.Insert(25);
				myTree.Insert(50);
				myTree.Insert(12);
				myTree.Insert(21);
				myTree.Insert(99);
				myTree.Insert(6);
				/*
					25
				 12    50
			   6   21     99
				*/

				bsIntQueue.Purge();
				myTree.PostOrder(AddIntToQueue);

				for (size_t i = 0; i < 6; i++)
					if (bsIntQueue.Dequeue() != correctArray[i])
						pass = false;

				Assert::IsTrue(pass);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(BinarySearchTreeBreadthFirstTest)
		{
			int correctArray[6] = { 25, 12, 50, 6, 21, 99 };
			CrtCheckMemory check;
			bool pass = true;
			try
			{
				BinarySearchTree<int> myTree;
				myTree.Insert(25);
				myTree.Insert(50);
				myTree.Insert(12);
				myTree.Insert(21);
				myTree.Insert(99);
				myTree.Insert(6);
				/*
					25
				 12    50
			   6   21     99
				*/

				bsIntQueue.Purge();
				myTree.BreadthFirst(AddIntToQueue);

				for (size_t i = 0; i < 6; i++)
					if (bsIntQueue.Dequeue() != correctArray[i])
						pass = false;

				Assert::IsTrue(pass);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(BinarySearchTreeCopyCtorTest)
		{
			int correctArray[6] = { 25, 12, 50, 6, 21, 99 };
			bool pass = true;
			CrtCheckMemory check;
			BinarySearchTree<int> myTree;

			myTree.Insert(25);
			myTree.Insert(50);
			myTree.Insert(12);
			myTree.Insert(21);
			myTree.Insert(99);
			myTree.Insert(6);

			BinarySearchTree<int> copyTree(myTree);
			bsIntQueue.Purge();
			copyTree.BreadthFirst(AddIntToQueue);

			for (size_t i = 0; i < 6; i++)
				if (bsIntQueue.Dequeue() != correctArray[i])
					pass = false;

			Assert::IsTrue(pass);
		}

		TEST_METHOD(BinarySearchTreeDeleteTest)
		{
			int correctArray[5] = { 6, 21, 25, 50, 99 };
			CrtCheckMemory check;
			bool pass = true;
			try
			{
				BinarySearchTree<int> myTree;
				myTree.Insert(25);
				myTree.Insert(50);
				myTree.Insert(12);
				myTree.Insert(21);
				myTree.Insert(99);
				myTree.Insert(6);
				/*
					25
				 12    50
			   6   21     99
				*/
				myTree.Delete(12);

				/*
					25
				 6	   50
				  21	  99
				*/
				bsIntQueue.Purge();
				myTree.InOrder(AddIntToQueue);
				for (size_t i = 0; i < 5; i++)
					if (bsIntQueue.Dequeue() != correctArray[i])
						pass = false;

				Assert::IsTrue(pass);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(BinarySearchTreeDeleteTest2)
		{
			int correctOrder[10] = { 25, 6, 50, 5, 21, 99, 3, 22, 105, 4 };
			bool pass = true;
			CrtCheckMemory check;
			try
			{
				BinarySearchTree<int> myTree;
				myTree.Insert(25);
				myTree.Insert(50);
				myTree.Insert(12);
				myTree.Insert(21);
				myTree.Insert(99);
				myTree.Insert(105);
				myTree.Insert(6);
				myTree.Insert(5);
				myTree.Insert(22);
				myTree.Insert(3);
				myTree.Insert(4);
				/*
					25
				12    50
			  6   21     99
			5		 22		105
		  3
			4
				*/

				myTree.Delete(12);

/*
					25
				6		50
			 5	  21		99
		   3		22		  105
		     4
*/
				bsIntQueue.Purge();
				myTree.BreadthFirst(AddIntToQueue);
				for (size_t i = 0; i < 10; i++)
					if (bsIntQueue.Dequeue() != correctOrder[i])
						pass = false;

				Assert::IsTrue(pass);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(BinarySearchTreeDeleteTest3)
		{
			int correctOrder[10] = { 22, 12, 50, 6, 21, 99, 5, 105, 3, 4 };
			bool pass = true;
			CrtCheckMemory check;
			try
			{
				BinarySearchTree<int> myTree;
				myTree.Insert(25);
				myTree.Insert(50);
				myTree.Insert(12);
				myTree.Insert(21);
				myTree.Insert(99);
				myTree.Insert(105);
				myTree.Insert(6);
				myTree.Insert(5);
				myTree.Insert(22);
				myTree.Insert(3);
				myTree.Insert(4);
				/*
					25
				 12    50
			   6   21     99
			 5		 22		105
		   3
			 4
				*/

				myTree.Delete(25);

				/*
					22
				 12		50
			   6	21	   99
			 5		    	  105
		   3
			 4
				*/
				bsIntQueue.Purge();
				myTree.BreadthFirst(AddIntToQueue);
				for (size_t i = 0; i < 10; i++)
					if (bsIntQueue.Dequeue() != correctOrder[i])
						pass = false;

				Assert::IsTrue(pass);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(BinarySearchTreeHeightTest)
		{
			CrtCheckMemory check;
			try
			{
				BinarySearchTree<int> myTree;
				myTree.Insert(25);
				myTree.Insert(50);
				myTree.Insert(12);
				myTree.Insert(21);
				myTree.Insert(99);
				myTree.Insert(105);
				myTree.Insert(6);
				myTree.Insert(5);
				myTree.Insert(22);
				myTree.Insert(3);
				myTree.Insert(4);
				/*
					25
				 12    50
			   6   21     99
			 5		 22		105
		   3
			4
				*/

				Assert::IsTrue(myTree.Height() == 6);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}


	};
}