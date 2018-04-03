#include "stdafx.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "Exception.h"
#include <string>
#include "GenTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(GenTreeTest)
	{
	public:

		TEST_METHOD(GenTreeMemoryTest)
		{
			CrtCheckMemory check;
			GenTree tree;
			tree.AddNode(new GenNode("Documents", nullptr, true));
			tree.AddNode(new GenNode("File1.txt", nullptr, false));
			tree.AddNode(new GenNode("MoreDocs", nullptr, true));
			tree.AddNode(new GenNode("AnotherFile.txt", nullptr, false));
			tree.AddNode(new GenNode("AnotherFile2.txt", nullptr, false));
			tree.AddNode(new GenNode("LastDir", nullptr, true));
			Assert::IsTrue(true);
		}

		TEST_METHOD(GenTreeCopyCtorTest)
		{
			CrtCheckMemory check;
			GenTree tree;
			tree.AddNode(new GenNode("Documents", nullptr, true));
			tree.AddNode(new GenNode("File1.txt", nullptr, false));
			tree.AddNode(new GenNode("MoreDocs", nullptr, true));
			tree.AddNode(new GenNode("AnotherFile.txt", nullptr, false));
			tree.AddNode(new GenNode("AnotherFile2.txt", nullptr, false));
			tree.AddNode(new GenNode("LastDir", nullptr, true));
			GenTree copyTree(tree);
			Assert::IsTrue(copyTree.GetCount() == 6);
		}
	};
}
