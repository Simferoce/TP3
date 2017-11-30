#include "stdafx.h"
#include "CppUnitTest.h"
#include "../StructuresDonnees/queue.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestStructureQueue
{		
	TEST_CLASS(TestQueue)
	{
		TEST_METHOD(Size)
		{
			StructuresDonnees::Queue<int> test;
			Assert::IsTrue(test.size() == 0);
		}
		TEST_METHOD(Empty)
		{
			StructuresDonnees::Queue<int> test;
			Assert::IsTrue(test.empty());
		}
		TEST_METHOD(Push_back)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(0);
		}
		TEST_METHOD(Push_front)
		{
			StructuresDonnees::Queue<int> test;
			test.push_front(0);
		}
		TEST_METHOD(Size2Elements)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(0);
			Assert::IsTrue(test.size() == 1);
		}
		TEST_METHOD(EmptyNot)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(0);
			Assert::IsTrue(!test.empty());
		}
		TEST_METHOD(Pop)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(0);
			test.pop_front();
			Assert::IsTrue(test.empty());
		}
		TEST_METHOD(Front)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(0);
			Assert::IsTrue(test.front() == 0);
		}
		TEST_METHOD(Back)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(0);
			Assert::IsTrue(test.back() == 0);
		}
		TEST_METHOD(PushBackWith2Elements)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(0);
			test.push_back(1);
		}
		TEST_METHOD(PushFrontWith2Elements)
		{
			StructuresDonnees::Queue<int> test;
			test.push_front(0);
			test.push_front(1);
		}
		TEST_METHOD(SizeMoreThan2Elements)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(0);
			test.push_back(1);
			Assert::IsTrue(test.size() == 2);
		}
		TEST_METHOD(PopWith2Elements)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(0);
			test.push_back(1);
			test.pop_front();
			Assert::IsTrue(test.size() == 1);
			Assert::IsTrue(test.front() == 1);
		}
		TEST_METHOD(FrontWith2Elements)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(0);
			test.push_back(1);
			Assert::IsTrue(test.front() == 0);
		}
		TEST_METHOD(BackWith2Elements)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(0);
			test.push_back(1);
			Assert::IsTrue(test.back() == 1);
		}
		TEST_METHOD(PushBackWithMoreThan2Elements)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(0);
			test.push_back(1);
			test.push_back(2);
		}
		TEST_METHOD(PushFrontWithMoreThan2Elements)
		{
			StructuresDonnees::Queue<int> test;
			test.push_front(0);
			test.push_front(1);
			test.push_front(2);
			Assert::IsTrue(test.front() == 2);
		}
		TEST_METHOD(SizeWithMoreThan2Elements)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(0);
			test.push_back(1);
			test.push_back(2);
			Assert::IsTrue(test.size() == 3);
		}
		TEST_METHOD(PopWithMoreThan2Elements)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(0);
			test.push_back(1);
			test.push_back(2);
			test.pop_front();
			Assert::IsTrue(test.size() == 2);
			Assert::IsTrue(test.front() == 1);
			Assert::IsTrue(test.back() == 2);
		}
		TEST_METHOD(FrontWithMoreThan2Elements)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(0);
			test.push_back(1);
			test.push_back(2);
			Assert::IsTrue(test.front() == 0);
		}
		TEST_METHOD(BackWithMoreThan2Elements)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(0);
			test.push_back(1);
			test.push_back(2);
			Assert::IsTrue(test.back() == 2);
		}
		TEST_METHOD(Swap)
		{
			StructuresDonnees::Queue<std::string> test;
			test.push_back("test");
			StructuresDonnees::Queue<std::string> test2;
			test2.push_back("test2");

			test.swap(test2);
			Assert::IsTrue(test.front() == "test2");
			Assert::IsTrue(test2.front() == "test");
		}
		TEST_METHOD(SwapWith2Elements)
		{
			StructuresDonnees::Queue<std::string> test;
			test.push_back("test");
			test.push_back("testtest");
			StructuresDonnees::Queue<std::string> test2;
			test2.push_back("test2");
			test2.push_back("test2test2");
			test.swap(test2);
			Assert::IsTrue(test.front() == "test2");
			Assert::IsTrue(test2.front() == "test");
			Assert::IsTrue(test.back() == "test2test2");
			Assert::IsTrue(test2.back() == "testtest");
		}
		TEST_METHOD(SwapNoEqualElements)
		{
			StructuresDonnees::Queue<std::string> test;
			test.push_back("test");
			StructuresDonnees::Queue<std::string> test2;
			test2.push_back("test2");
			test2.push_back("test2test2");
			test.swap(test2);
			Assert::IsTrue(test.front() == "test2");
			Assert::IsTrue(test.back() == "test2test2");
			Assert::IsTrue(test.size() == 2);
			Assert::IsTrue(test2.front() == "test");
			Assert::IsTrue(test2.size() == 1);
		}
		TEST_METHOD(SwapWithMoreThan2Elements)
		{
			StructuresDonnees::Queue<std::string> test;
			test.push_back("test");
			test.push_back("testtest");
			test.push_back("testtesttest");
			StructuresDonnees::Queue<std::string> test2;
			test2.push_back("test2");
			test2.push_back("test2test2");
			test2.push_back("test2test2test2");
			test.swap(test2);
			Assert::IsTrue(test.front() == "test2");
			test.pop_front();
			Assert::IsTrue(test.front() == "test2test2");
			test.pop_front();
			Assert::IsTrue(test.front() == "test2test2test2");
			Assert::IsTrue(test2.front() == "test");
			test2.pop_front();
			Assert::IsTrue(test2.front() == "testtest");
			test2.pop_front();
			Assert::IsTrue(test2.front() == "testtesttest");
		}
		TEST_METHOD(OperatorEqualEmpty)
		{
			StructuresDonnees::Queue<std::string> test;
			StructuresDonnees::Queue<std::string> test2;
			test2 = test;
			Assert::IsTrue(test2.empty());
		}
		TEST_METHOD(OperatorEqual)
		{
			StructuresDonnees::Queue<std::string> test;
			test.push_back("test");
			StructuresDonnees::Queue<std::string> test2;
			test2 = test;
			Assert::IsTrue(test.front() == test2.front());
		}
		TEST_METHOD(OperatorEqualWith2Elements)
		{
			StructuresDonnees::Queue<std::string> test;
			test.push_back("test");
			test.push_back("testtest");
			StructuresDonnees::Queue<std::string> test2;
			test2 = test;
			Assert::IsTrue(test.front() == test2.front());
			Assert::IsTrue(test.back() == test2.back());
		}
		TEST_METHOD(OperatorEqualWithMoreThan2Elements)
		{
			StructuresDonnees::Queue<std::string> test;
			test.push_back("test");
			test.push_back("testtest");
			test.push_back("testtesttest");
			StructuresDonnees::Queue<std::string> test2;
			test2 = test;
			Assert::IsTrue(test.front() == test2.front());
			test.pop_front();
			test2.pop_front();
			Assert::IsTrue(test.front() == test2.front());
			test.pop_front();
			test2.pop_front();
			Assert::IsTrue(test.front() == test2.front());
		}
		TEST_METHOD(Push_Pop)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(1);
			test.push_back(2);
			test.pop_front();
			test.pop_front();
			test.push_back(3);
			Assert::IsTrue(test.front() == 3);
			Assert::IsTrue(test.back() == 3);
		}
		TEST_METHOD(Push_Pop_1)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(1);
			test.push_back(2);
			test.pop_front();
			test.push_back(3);
			test.pop_front();
			Assert::IsTrue(test.front() == 3);
			Assert::IsTrue(test.back() == 3);
		}
		TEST_METHOD(Push_Pop_2)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(1);
			test.push_back(2);
			test.pop_front();
			test.push_back(3);
			test.pop_front();
			test.push_back(4);
			Assert::IsTrue(test.front() == 3);
			Assert::IsTrue(test.back() == 4);
		}
		TEST_METHOD(Push_Pop_3)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(1);
			test.push_back(2);
			test.push_back(3);
			test.pop_front();
			test.pop_front();
			test.push_back(4);
			Assert::IsTrue(test.front() == 3);
			Assert::IsTrue(test.back() == 4);
		}
		TEST_METHOD(OperatorAccessByIndexWithOneElem)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(1);
			Assert::IsTrue(test[0] == 1);
		}
		TEST_METHOD(OperatorAccessByIndexWithTwoElem)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(1); 
			test.push_back(2);
			Assert::IsTrue(test[0] == 1);
			Assert::IsTrue(test[1] == 2);
		}
		TEST_METHOD(OperatorAccessByIndexWithMoreThanTwoElem)
		{
			StructuresDonnees::Queue<int> test;
			test.push_back(1);
			test.push_back(2);
			test.push_back(3);
			Assert::IsTrue(test[0] == 1);
			Assert::IsTrue(test[1] == 2);
			Assert::IsTrue(test[2] == 3);
		}
	};
}