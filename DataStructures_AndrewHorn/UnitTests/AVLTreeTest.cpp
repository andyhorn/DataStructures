#include "stdafx.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "Exception.h"
#include <string>
#include "AVLTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	QueueList<int> avlIntQueue;
	//QueueList<string> stringQueue;

	void myIntFunc(AVLNode<int> *node)
	{
		cout << node->GetDataRef() << endl;
	}

	void AddIntToQueue(AVLNode<int> *node)
	{
		avlIntQueue.Enqueue(node->GetDataRef());
	}

	TEST_CLASS(AVLTreeTest)
	{
	public:
		TEST_METHOD(AVLTreeDefaultCtorTest)
		{
			CrtCheckMemory check;
			AVLTree<int> myAVLTree;
			Assert::IsTrue(true);
		}

		TEST_METHOD(AVLTreeInsertTest)
		{
			CrtCheckMemory check;
			AVLTree<int> myAVLTree;
			try
			{
				myAVLTree.Insert(25);
				myAVLTree.Insert(30);
				myAVLTree.Insert(20);
				myAVLTree.Insert(35);
				Assert::IsTrue(true);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(AVLTreeNodeCtorTest)
		{
			CrtCheckMemory check;
			try
			{
				AVLTree<int>(25);
				Assert::IsTrue(true);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(AVLTreeSetFunctionTest)
		{
			CrtCheckMemory check;
			try
			{
				AVLTree<int> myTree;
				myTree.SetFunction(myIntFunc);
				Assert::IsTrue(true);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(AVLTreeInOrderTest)
		{
			CrtCheckMemory check;
			int correctOrder[6] = { 6, 12, 21, 25, 50, 99 };
			bool pass = true;
			try
			{
				AVLTree<int> myTree;
				myTree.Insert(25);
				myTree.Insert(50);
				myTree.Insert(12);
				myTree.Insert(21);
				myTree.Insert(99);
				myTree.Insert(6);

				avlIntQueue.Purge();
				myTree.InOrder(AddIntToQueue);

				for (size_t i = 0; i < 6; i++)
					if (avlIntQueue.Dequeue() != correctOrder[i])
						pass = false;

				Assert::IsTrue(pass);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(AVLTreePreOrderTest)
		{
			int correctOrder[6] = { 25, 12, 6, 21, 50, 99 };
			CrtCheckMemory check;
			bool pass = true;
			try
			{
				AVLTree<int> myTree;
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

				avlIntQueue.Purge();
				myTree.PreOrder(AddIntToQueue);

				for (size_t i = 0; i < 6; i++)
					if (avlIntQueue.Dequeue() != correctOrder[i])
						pass = false;

				Assert::IsTrue(pass);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(AVLTreePostOrderTest)
		{
			int correctOrder[6] = { 6, 21, 12, 99, 50, 25 };
			CrtCheckMemory check;
			bool pass = true;
			try
			{
				AVLTree<int> myTree;
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

				avlIntQueue.Purge();
				myTree.PostOrder(AddIntToQueue);

				for (size_t i = 0; i < 6; i++)
					if (avlIntQueue.Dequeue() != correctOrder[i])
						pass = false;

				Assert::IsTrue(pass);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(AVLTreeBreadthFirstTest)
		{
			int correctOrder[6] = { 25, 12, 50, 6, 21, 99 };
			CrtCheckMemory check;
			bool pass = true;
			try
			{
				AVLTree<int> myTree;
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

				avlIntQueue.Purge();
				myTree.BreadthFirst(AddIntToQueue);

				for (size_t i = 0; i < 6; i++)
					if (avlIntQueue.Dequeue() != correctOrder[i])
						pass = false;

				Assert::IsTrue(pass);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(AVLTreeCopyCtorTest)
		{
			CrtCheckMemory check;
			bool pass = true;
			int correctOrder[6] = { 25, 12, 50, 6, 21, 99 };
			AVLTree<int> myTree;
			myTree.Insert(25);
			myTree.Insert(50);
			myTree.Insert(12);
			myTree.Insert(21);
			myTree.Insert(99);
			myTree.Insert(6);
			try
			{
				AVLTree<int> copyTree(myTree);
				avlIntQueue.Purge();
				copyTree.BreadthFirst(AddIntToQueue);

				for (size_t i = 0; i < 6; i++)
					if (avlIntQueue.Dequeue() != correctOrder[i])
						pass = false;

				Assert::IsTrue(pass);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(AVLTreeSimpleRightRotationTest)
		{
			CrtCheckMemory check;
			bool pass = true;
			int correctOrder[5] = { 9, 2, 10, 1, 8 };
			AVLTree<int> myTree;
			myTree.Insert(9);
			myTree.Insert(8);
			myTree.Insert(10);
			myTree.Insert(2);
			myTree.Insert(1);

			avlIntQueue.Purge();
			myTree.BreadthFirst(AddIntToQueue);

			for (size_t i = 0; i < 5; i++)
				if (avlIntQueue.Dequeue() != correctOrder[i])
					pass = false;

			Assert::IsTrue(pass);
		}

		TEST_METHOD(AVLTreeSimpleLeftRotationTest)
		{
			CrtCheckMemory check;
			bool pass = true;
			int correctOrder[5] = { 9, 8, 12, 10, 14 };
			AVLTree<int> myTree;
			myTree.Insert(9);
			myTree.Insert(10);
			myTree.Insert(8);
			myTree.Insert(12);
			myTree.Insert(14);

			avlIntQueue.Purge();
			myTree.BreadthFirst(AddIntToQueue);

			for (size_t i = 0; i < 5; i++)
				if (avlIntQueue.Dequeue() != correctOrder[i])
					pass = false;

			Assert::IsTrue(pass);
		}

		TEST_METHOD(AVLTreeSimpleDeleteTest)
		{
			CrtCheckMemory check;
			bool pass = true;
			int correctOrder[4] = { 9, 8, 12, 14 };
			AVLTree<int> myTree;
			myTree.Insert(9);
			myTree.Insert(10);
			myTree.Insert(8);
			myTree.Insert(12);
			myTree.Insert(14);

			myTree.Delete(10);

			avlIntQueue.Purge();
			myTree.BreadthFirst(AddIntToQueue);

			for (size_t i = 0; i < 4; i++)
				if (avlIntQueue.Dequeue() != correctOrder[i])
					pass = false;
		}
	};
}
