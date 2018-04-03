#include "stdafx.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "Exception.h"
#include <string>
#include <queue>
#include "QueueList.h"
#include "Graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	QueueList<int> graphIntQueue;
	QueueList<string> graphStringQueue;

	// std::function<void(Vertex<V, E> vertex)> visit
	auto graphVisitInt = [](Vertex<int, int> vertex)
	{
		graphIntQueue.Enqueue(vertex.GetData());
	};

	auto graphVisitString = [](Vertex<string, int> vertex)
	{
		graphStringQueue.Enqueue(vertex.GetData());
	};

	//std::function<void(Vertex<int, int> vertex)> graphVisitFunc = { graphIntQueue.Enqueue(vertex.GetData()); }

	//void graphVisitFunc(Vertex<int, int> vertex) { graphIntQueue.Enqueue(vertex.GetData()); }

	//void graphVisitFunc(Vertex<string, int> vertex) { graphStringQueue.Enqueue(vertex.GetData()); }

	TEST_CLASS(GraphTest)
	{


	public:

		TEST_METHOD(GraphDefaultCtorTest)
		{
			CrtCheckMemory check;
			try
			{
				Graph<int, int> myGraph;
				Assert::IsTrue(true);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(GraphInsertVertexTest)
		{
			CrtCheckMemory check;
			try
			{
				Graph<int, int> myGraph;
				myGraph.InsertVertex(10);
				myGraph.InsertVertex(20);
				myGraph.InsertVertex(30);
				Assert::IsTrue(myGraph.GetCount() == 3);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(GraphInsertStringVertexTest)
		{
			CrtCheckMemory check;
			try
			{
				Graph<string, int> myStringGraph;
				myStringGraph.InsertVertex("Portland");
				myStringGraph.InsertVertex("Seattle");
				myStringGraph.InsertVertex("Los Angeles");
				Assert::IsTrue(myStringGraph.GetCount() == 3);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(GraphInsertEdgeTest)
		{
			CrtCheckMemory check;
			try
			{
				Graph<int, int> myGraph;
				myGraph.InsertVertex(10);
				myGraph.InsertVertex(20);
				myGraph.InsertEdge(10, 20, 0);
				Assert::IsTrue(myGraph.GetCount() == 2);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(GraphInsertStringEdgeTest)
		{
			CrtCheckMemory check;
			try
			{
				Graph<string, string> myStringGraph;
				myStringGraph.InsertVertex("Portland");
				myStringGraph.InsertVertex("Seattle");
				myStringGraph.InsertEdge("Portland", "Seattle", "4 hours");
				Assert::IsTrue(myStringGraph.GetCount() == 2);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(GraphInsertEdgeExceptionTest)
		{
			CrtCheckMemory check;
			Graph<string, string> myGraph;
			try
			{
				myGraph.InsertEdge("From", "To", "Data");
				Assert::Fail();
			}
			catch (Exception)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(GraphStringCopyCtorTest)
		{
			CrtCheckMemory check;
			try
			{
				Graph<string, string> myStringGraph;
				myStringGraph.InsertVertex("Portland");
				myStringGraph.InsertVertex("Seattle");
				myStringGraph.InsertEdge("Portland", "Seattle", "4 hours");
				Graph<string, string> copyGraph(myStringGraph);
				Assert::IsTrue(copyGraph.GetCount() == 2);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(GraphDeleteVertexTest)
		{
			CrtCheckMemory check;
			try
			{
				Graph<string, string> myStringGraph;
				myStringGraph.InsertVertex("Portland");
				myStringGraph.InsertVertex("Tacoma");
				myStringGraph.InsertVertex("Seattle");
				myStringGraph.InsertEdge("Portland", "Seattle", "4 hours");
				myStringGraph.DeleteVertex("Seattle");
				myStringGraph.InsertEdge("Portland", "Tacoma", "2 hours");
				Assert::IsTrue(myStringGraph.GetCount() == 2);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(GraphDeleteEdgeTest)
		{
			CrtCheckMemory check;
			try
			{
				Graph<string, string> myStringGraph;
				myStringGraph.InsertVertex("Portland");
				myStringGraph.InsertVertex("Seattle");
				myStringGraph.InsertVertex("Scappoose");
				myStringGraph.InsertEdge("Portland", "Seattle", "4 hours");
				myStringGraph.InsertEdge("Portland", "Scappoose", "30 minutes");
				myStringGraph.DeleteEdge("Portland", "Seattle", "4 hours");
				Assert::IsTrue(myStringGraph.GetCount() == 3);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(GraphDepthFirstTraversalTest)
		{
			CrtCheckMemory check;
			string correct[9] = { "A", "X", "G", "P", "H", "E", "M", "J", "Y" };
			bool pass = true;
			try
			{
				Graph<string, int> myGraph;
				myGraph.InsertVertex("A");
				myGraph.InsertVertex("X");
				myGraph.InsertVertex("G");
				myGraph.InsertVertex("H");
				myGraph.InsertVertex("P");
				myGraph.InsertVertex("E");
				myGraph.InsertVertex("Y");
				myGraph.InsertVertex("M");
				myGraph.InsertVertex("J");

				myGraph.InsertEdge("A", "X", 1);
				myGraph.InsertEdge("X", "H", 1);
				myGraph.InsertEdge("X", "G", 1);
				myGraph.InsertEdge("G", "P", 1);
				myGraph.InsertEdge("H", "P", 1);
				myGraph.InsertEdge("H", "E", 1);
				myGraph.InsertEdge("E", "Y", 1);
				myGraph.InsertEdge("E", "M", 1);
				myGraph.InsertEdge("Y", "M", 1);
				myGraph.InsertEdge("M", "J", 1);

				graphStringQueue.Purge();
				myGraph.DepthFirst(graphVisitString);

				for (size_t i = 0; i < 9; i++)
					if (graphStringQueue.Dequeue() != correct[i])
						pass = false;

				graphStringQueue.Purge();
				Assert::IsTrue(pass);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(GraphBreadthFirstTraversalTest)
		{
			CrtCheckMemory check;
			string correct[9] = { "A", "X", "G", "H", "P", "E", "M", "Y", "J" };
			bool pass = true;
			try
			{
				Graph<string, int> myGraph;
				myGraph.InsertVertex("A");
				myGraph.InsertVertex("X");
				myGraph.InsertVertex("G");
				myGraph.InsertVertex("H");
				myGraph.InsertVertex("P");
				myGraph.InsertVertex("E");
				myGraph.InsertVertex("Y");
				myGraph.InsertVertex("M");
				myGraph.InsertVertex("J");

				myGraph.InsertEdge("A", "X", 1);
				myGraph.InsertEdge("X", "H", 1);
				myGraph.InsertEdge("X", "G", 1);
				myGraph.InsertEdge("G", "P", 1);
				myGraph.InsertEdge("H", "P", 1);
				myGraph.InsertEdge("H", "E", 1);
				myGraph.InsertEdge("E", "Y", 1);
				myGraph.InsertEdge("E", "M", 1);
				myGraph.InsertEdge("Y", "M", 1);
				myGraph.InsertEdge("M", "J", 1);

				graphStringQueue.Purge();
				myGraph.BreadthFirst(graphVisitString);

				for (size_t i = 0; i < 9; i++)
					if (graphStringQueue.Dequeue() != correct[i])
						pass = false;

				graphStringQueue.Purge();
				Assert::IsTrue(pass);
			}
			catch (Exception)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(GraphDeleteExceptionTest)
		{
			CrtCheckMemory check;
			try
			{
				Graph<string, string> myGraph;
				myGraph.DeleteVertex("DELETE ME");
				Assert::Fail();
			}
			catch (Exception)
			{
				try
				{
					Graph<string, string> myGraph2;
					myGraph2.DeleteEdge("From", "To", "Data");
					Assert::Fail();
				}
				catch (Exception)
				{
					Assert::IsTrue(true);
				}
			}
		}

		TEST_METHOD(GraphNonUniqueInsertTest)
		{
			CrtCheckMemory check;
			Graph<string, string> myGraph;
			myGraph.InsertVertex("Test String.");
			try
			{
				// attempting to insert the same data, should throw exception
				myGraph.InsertVertex("Test String.");
				Assert::Fail();
			}
			catch (Exception)
			{
				Assert::IsTrue(true);
			}
		}
	};
}