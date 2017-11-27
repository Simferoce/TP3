#include "stdafx.h"
#include "CppUnitTest.h"
#include "../StructuresDonnees/stack.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestStructureStack
{		
	TEST_CLASS(EmptyStack)
	{
		TEST_METHOD(is_empty)
		{
			StructuresDonnees::stack<int> test;
			Assert::IsTrue(test.is_empty());
		}
		TEST_METHOD(size)
		{
			StructuresDonnees::stack<int> test;
			Assert::IsTrue(test.size() == 0);
		}
		TEST_METHOD(push)
		{
			StructuresDonnees::stack<int> test;
			test.push(1);
		}
	};
	TEST_CLASS(OneElemStack)
	{
		TEST_METHOD(top)
		{
			StructuresDonnees::stack<int> test;
			test.push(1);
			Assert::IsTrue(test.top() == 1);
		}
		TEST_METHOD(is_empty_false)
		{
			StructuresDonnees::stack<int> test;
			test.push(1);
			Assert::IsTrue(!test.is_empty());
		}
		TEST_METHOD(size_1)
		{
			StructuresDonnees::stack<int> test;
			test.push(1);
			Assert::IsTrue(test.size() == 1);
		}
		TEST_METHOD(push_1)
		{
			StructuresDonnees::stack<int> test;
			test.push(1);
			test.push(2);
			Assert::IsTrue(test.size() == 2);
		}
		TEST_METHOD(pop_1)
		{
			StructuresDonnees::stack<int> test;
			test.push(1);
			test.pop();
			Assert::IsTrue(test.size() == 0);
		}
		TEST_METHOD(swap_1)
		{
			StructuresDonnees::stack<int> test;
			test.push(1);
			StructuresDonnees::stack<int> test2;
			test.swap(test2);
			Assert::IsTrue(test2.size() == 1);
			Assert::IsTrue(test.size() == 0);
		}
	};
	TEST_CLASS(TwoElemStack)
	{
		TEST_METHOD(top_2)
		{
			StructuresDonnees::stack<int> test;
			test.push(1);
			test.push(2);
			Assert::IsTrue(test.top() == 2);
		}
		TEST_METHOD(size_2)
		{
			StructuresDonnees::stack<int> test;
			test.push(1);
			test.push(2);
			Assert::IsTrue(test.size() == 2);
		}
		TEST_METHOD(push_2)
		{
			StructuresDonnees::stack<int> test;
			test.push(1);
			test.push(2);
			test.push(3);
			Assert::IsTrue(test.size() == 3);
		}
		TEST_METHOD(pop_2)
		{
			StructuresDonnees::stack<int> test;
			test.push(1);
			test.push(2);
			test.pop();
			Assert::IsTrue(test.size() == 1);
			Assert::IsTrue(test.top() == 1);
		}
		TEST_METHOD(swap_2)
		{
			StructuresDonnees::stack<int> test;
			test.push(1);
			test.push(2);
			StructuresDonnees::stack<int> test2;
			test2.push(3);
			test.swap(test2);
			Assert::IsTrue(test2.size() == 2);
			Assert::IsTrue(test2.top() == 2);
			Assert::IsTrue(test.size() == 1);
			Assert::IsTrue(test.top() == 3);
		}
	};
}