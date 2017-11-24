#include "stdafx.h"
#include "CppUnitTest.h"
#include "../StructuresDonnees/queue.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestStructureQueue
{		
	TEST_CLASS(TestCircularQueue)
	{
		TEST_METHOD(Size)
		{
			StructuresDonnees::CircularQueue<int> test;
			Assert::IsTrue(test.size() == 0);
		}
		TEST_METHOD(Empty)
		{
			StructuresDonnees::CircularQueue<int> test;
			Assert::IsTrue(test.empty());
		}
		TEST_METHOD(Push)
		{
			StructuresDonnees::CircularQueue<int> test;
			test.push(0);
		}
		TEST_METHOD(Size2Elements)
		{
			StructuresDonnees::CircularQueue<int> test;
			test.push(0);
			Assert::IsTrue(test.size() == 1);
		}
		TEST_METHOD(EmptyNot)
		{
			StructuresDonnees::CircularQueue<int> test;
			test.push(0);
			Assert::IsTrue(!test.empty());
		}
		TEST_METHOD(Pop)
		{
			StructuresDonnees::CircularQueue<int> test;
			test.push(0);
			test.pop();
			Assert::IsTrue(test.empty());
		}
		TEST_METHOD(Front)
		{
			StructuresDonnees::CircularQueue<int> test;
			test.push(0);
			Assert::IsTrue(test.front() == 0);
		}
		TEST_METHOD(Back)
		{
			StructuresDonnees::CircularQueue<int> test;
			test.push(0);
			Assert::IsTrue(test.back() == 0);
		}
		TEST_METHOD(PushWith2Elements)
		{
			StructuresDonnees::CircularQueue<int> test;
			test.push(0);
			test.push(1);
		}
		TEST_METHOD(SizeMoreThan2Elements)
		{
			StructuresDonnees::CircularQueue<int> test;
			test.push(0);
			test.push(1);
			Assert::IsTrue(test.size() == 2);
		}
		TEST_METHOD(PopWith2Elements)
		{
			StructuresDonnees::CircularQueue<int> test;
			test.push(0);
			test.push(1);
			test.pop();
			Assert::IsTrue(test.size() == 1);
			Assert::IsTrue(test.front() == 1);
		}
		TEST_METHOD(FrontWith2Elements)
		{
			StructuresDonnees::CircularQueue<int> test;
			test.push(0);
			test.push(1);
			Assert::IsTrue(test.front() == 0);
		}
		TEST_METHOD(BackWith2Elements)
		{
			StructuresDonnees::CircularQueue<int> test;
			test.push(0);
			test.push(1);
			Assert::IsTrue(test.back() == 1);
		}
		TEST_METHOD(PushWithMoreThan2Elements)
		{
			StructuresDonnees::CircularQueue<int> test;
			test.push(0);
			test.push(1);
			test.push(2);
		}
		TEST_METHOD(SizeWithMoreThan2Elements)
		{
			StructuresDonnees::CircularQueue<int> test;
			test.push(0);
			test.push(1);
			test.push(2);
			Assert::IsTrue(test.size() == 3);
		}
		TEST_METHOD(PopWithMoreThan2Elements)
		{
			StructuresDonnees::CircularQueue<int> test;
			test.push(0);
			test.push(1);
			test.push(2);
			test.pop();
			Assert::IsTrue(test.size() == 2);
			Assert::IsTrue(test.front() == 1);
			Assert::IsTrue(test.back() == 2);
		}
		TEST_METHOD(FrontWithMoreThan2Elements)
		{
			StructuresDonnees::CircularQueue<int> test;
			test.push(0);
			test.push(1);
			test.push(2);
			Assert::IsTrue(test.front() == 0);
		}
		TEST_METHOD(BackWithMoreThan2Elements)
		{
			StructuresDonnees::CircularQueue<int> test;
			test.push(0);
			test.push(1);
			test.push(2);
			Assert::IsTrue(test.back() == 2);
		}
		TEST_METHOD(Swap)
		{
			StructuresDonnees::CircularQueue<std::string> test;
			test.push("test");
			StructuresDonnees::CircularQueue<std::string> test2;
			test2.push("test2");

			test.swap(test2);
			Assert::IsTrue(test.front() == "test2");
			Assert::IsTrue(test2.front() == "test");
		}
		TEST_METHOD(SwapWith2Elements)
		{
			StructuresDonnees::CircularQueue<std::string> test;
			test.push("test");
			test.push("testtest");
			StructuresDonnees::CircularQueue<std::string> test2;
			test2.push("test2");
			test2.push("test2test2");
			test.swap(test2);
			Assert::IsTrue(test.front() == "test2");
			Assert::IsTrue(test2.front() == "test");
			Assert::IsTrue(test.back() == "test2test2");
			Assert::IsTrue(test2.back() == "testtest");
		}
		TEST_METHOD(SwapNoEqualElements)
		{
			StructuresDonnees::CircularQueue<std::string> test;
			test.push("test");
			StructuresDonnees::CircularQueue<std::string> test2;
			test2.push("test2");
			test2.push("test2test2");
			test.swap(test2);
			Assert::IsTrue(test.front() == "test2");
			Assert::IsTrue(test.back() == "test2test2");
			Assert::IsTrue(test.size() == 2);
			Assert::IsTrue(test2.front() == "test");
			Assert::IsTrue(test2.size() == 1);
		}

		TEST_METHOD(SwapWithMoreThan2Elements)
		{
			StructuresDonnees::CircularQueue<std::string> test;
			test.push("test");
			test.push("testtest");
			test.push("testtesttest");
			StructuresDonnees::CircularQueue<std::string> test2;
			test2.push("test2");
			test2.push("test2test2");
			test2.push("test2test2test2");
			test.swap(test2);
			Assert::IsTrue(test.front() == "test2");
			test.pop();
			Assert::IsTrue(test.front() == "test2test2");
			test.pop();
			Assert::IsTrue(test.front() == "test2test2test2");
			Assert::IsTrue(test2.front() == "test");
			test2.pop();
			Assert::IsTrue(test2.front() == "testtest");
			test2.pop();
			Assert::IsTrue(test2.front() == "testtesttest");
		}
		TEST_METHOD(OperatorEqualEmpty)
		{
			StructuresDonnees::CircularQueue<std::string> test;
			StructuresDonnees::CircularQueue<std::string> test2;
			test2 = test;
			Assert::IsTrue(test2.empty());
		}
		TEST_METHOD(OperatorEqual)
		{
			StructuresDonnees::CircularQueue<std::string> test;
			test.push("test");
			StructuresDonnees::CircularQueue<std::string> test2;
			test2 = test;
			Assert::IsTrue(test.front() == test2.front());
		}
		TEST_METHOD(OperatorEqualWith2Elements)
		{
			StructuresDonnees::CircularQueue<std::string> test;
			test.push("test");
			test.push("testtest");
			StructuresDonnees::CircularQueue<std::string> test2;
			test2 = test;
			Assert::IsTrue(test.front() == test2.front());
			Assert::IsTrue(test.back() == test2.back());
		}
		TEST_METHOD(OperatorEqualWithMoreThan2Elements)
		{
			StructuresDonnees::CircularQueue<std::string> test;
			test.push("test");
			test.push("testtest");
			test.push("testtesttest");
			StructuresDonnees::CircularQueue<std::string> test2;
			test2 = test;
			Assert::IsTrue(test.front() == test2.front());
			test.pop();
			test2.pop();
			Assert::IsTrue(test.front() == test2.front());
			test.pop();
			test2.pop();
			Assert::IsTrue(test.front() == test2.front());
		}
	};
}