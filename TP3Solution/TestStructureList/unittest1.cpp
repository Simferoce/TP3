#include "stdafx.h"
#include "CppUnitTest.h"
#include "../StructuresDonnees/list.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestStructuresDonnees
{
	TEST_CLASS(EmptyList)
	{
		TEST_METHOD(constructeur)
		{
			StructuresDonnees::list<int> test;
		}
		TEST_METHOD(size)
		{
			StructuresDonnees::list<int> test;
			Assert::IsTrue(0 == test.size());
		}
		TEST_METHOD(is_empty)
		{
			StructuresDonnees::list<int> test;
			Assert::IsTrue(test.is_empty());
		}
		TEST_METHOD(push_back)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			Assert::IsTrue(test.size() == 1);
		}
		TEST_METHOD(push_front)
		{
			StructuresDonnees::list<int> test;
			test.push_front(1);
			Assert::IsTrue(test.size() == 1);
		}
		TEST_METHOD(iteratorBegin)
		{
			StructuresDonnees::list<std::string> test;
			Assert::IsTrue(test.begin() == test.end());
		}
		TEST_METHOD(r_iteratorBegin)
		{
			StructuresDonnees::list<std::string> test;
			Assert::IsTrue(test.rbegin() == test.rend());
		}
		TEST_METHOD(iteratorEnd)
		{
			StructuresDonnees::list<std::string> test;
			Assert::IsTrue(test.end() == test.begin());
		}
		TEST_METHOD(r_iteratorEnd)
		{
			StructuresDonnees::list<std::string> test;
			Assert::IsTrue(test.rend() == test.rbegin());
		}
		TEST_METHOD(iteratorInegality)
		{
			StructuresDonnees::list<std::string> test;
			Assert::IsFalse(test.begin() != test.end());
		}
		TEST_METHOD(r_iteratorInegality)
		{
			StructuresDonnees::list<std::string> test;
			Assert::IsFalse(test.rbegin() != test.rend());
		}
		TEST_METHOD(iteratorAssignation)
		{
			StructuresDonnees::list<std::string> test;
			StructuresDonnees::list<std::string>::iterator test2;
			test2 = test.begin();
			Assert::IsFalse(test.begin() != test2);
		}
		TEST_METHOD(r_iteratorAssignation)
		{
			StructuresDonnees::list<std::string> test;
			StructuresDonnees::list<std::string>::reverse_iterator test2;
			test2 = test.rbegin();
			Assert::IsFalse(test.rbegin() != test2);
		}
		TEST_METHOD(iteratorCopieConstructeur)
		{
			StructuresDonnees::list<std::string> test;
			StructuresDonnees::list<std::string>::iterator test2 = test.begin();
			Assert::IsFalse(test.begin() != test2);
		}
		TEST_METHOD(r_iteratorCopieConstructeur)
		{
			StructuresDonnees::list<std::string> test;
			StructuresDonnees::list<std::string>::reverse_iterator test2 = test.rbegin();
			Assert::IsFalse(test.rbegin() != test2);
		}
		TEST_METHOD(insert_begin)
		{
			StructuresDonnees::list<int> test;
			test.insert(test.begin(), 1);
			Assert::IsTrue(test.front() == 1);
		}
		TEST_METHOD(insert_end)
		{
			StructuresDonnees::list<int> test;
			test.insert(test.end(), 1);
			Assert::IsTrue(test.back() == 1);
		}
		TEST_METHOD(clear)
		{
			StructuresDonnees::list<int> test;
			test.clear();
			Assert::IsTrue(test.is_empty());
		}
		TEST_METHOD(swap)
		{
			StructuresDonnees::list<int> test;
			StructuresDonnees::list<int> test2;
			test.swap(test2);
			Assert::IsTrue(test2.is_empty());
			Assert::IsTrue(test.is_empty());
		}
		TEST_METHOD(reverse)
		{
			StructuresDonnees::list<int> test;
			test.reverse();
			Assert::IsTrue(test.is_empty());
		}
		TEST_METHOD(contains)
		{
			StructuresDonnees::list<int> test;
			Assert::IsFalse(test.contains(0));
		}
		TEST_METHOD(assign)
		{
			StructuresDonnees::list<std::string> test;
			test.assign(1, "Allo");
			Assert::IsTrue(test.size() == 1);
		}
	};
	TEST_CLASS(OneElementList)
	{
		TEST_METHOD(size_1)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			Assert::IsTrue(test.size() == 1);
		}
		TEST_METHOD(is_empty_1)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			Assert::IsFalse(test.is_empty());
		}
		TEST_METHOD(front_1)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			Assert::IsTrue(test.front() == 1);
		}
		TEST_METHOD(back_1)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			Assert::IsTrue(test.back() == 1);
		}
		TEST_METHOD(pop_back_1)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.pop_back();
			Assert::IsTrue(test.is_empty());
		}
		TEST_METHOD(pop_front_1)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.pop_front();
			Assert::IsTrue(test.is_empty());
		}
		TEST_METHOD(push_back_1)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.push_back(2);
			Assert::IsTrue(test.front() == 1);
			Assert::IsTrue(test.back() == 2);
			Assert::IsTrue(test.size() == 2);
		}
		TEST_METHOD(push_front_1)
		{
			StructuresDonnees::list<int> test;
			test.push_front(1);
			test.push_front(2);
			Assert::IsTrue(test.front() == 2);
			Assert::IsTrue(test.back() == 1);
			Assert::IsTrue(test.size() == 2);
		}
		TEST_METHOD(iteratorIncrementation_1)
		{
			StructuresDonnees::list<std::string> test;
			test.push_back("First");
			auto test2 = test.begin();
			++test2;
			Assert::IsFalse(test2 != test.end());
		}
		TEST_METHOD(r_iteratorIncrementation_1)
		{
			StructuresDonnees::list<std::string> test;
			test.push_back("First");
			auto test2 = test.rbegin();
			++test2;
			Assert::IsFalse(test2 != test.rend());
		}
		TEST_METHOD(iteratorDereferencement_1)
		{
			StructuresDonnees::list<std::string> test;
			test.push_back("First");
			Assert::IsTrue(*test.begin() == "First");
		}
		TEST_METHOD(r_iteratorDereferencement_1)
		{
			StructuresDonnees::list<std::string> test;
			test.push_back("First");
			Assert::IsTrue(*test.rbegin() == "First");
		}
		TEST_METHOD(insert_begin_1)
		{
			StructuresDonnees::list<int> test;
			test.push_back(0);
			test.insert(test.begin(), 1);
			Assert::IsTrue(test.front() == 1);
		}
		TEST_METHOD(insert_between_1)
		{

			StructuresDonnees::list<int> test;
			test.push_back(0);
			test.insert(++test.begin(), 1);
			Assert::IsTrue(test.back() == 1);
		}
		TEST_METHOD(insert_end_1)
		{
			StructuresDonnees::list<int> test;
			test.push_back(0);
			test.insert(test.end(), 1);
			Assert::IsTrue(test.back() == 1);
		}
		TEST_METHOD(erase_1)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.erase(test.begin());
			Assert::IsTrue(test.is_empty());
		}
		TEST_METHOD(swap_1)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			StructuresDonnees::list<int> test2;
			test.swap(test2);
			Assert::IsTrue(test2.size() == 1);
			Assert::IsTrue(test.is_empty());
		}
		TEST_METHOD(splice_1)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			StructuresDonnees::list<int> test2;
			test2.splice(test,test2.begin());
			Assert::IsTrue(test2.size() == 1);
			Assert::IsTrue(test2.front() == 1);
		}
		TEST_METHOD(reverse_1)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.reverse();
			Assert::IsTrue(test.front() == 1);
			Assert::IsTrue(test.back() == 1);
		}
		TEST_METHOD(contains_1)
		{
			StructuresDonnees::list<int> test;
			test.push_back(0);
			Assert::IsTrue(test.contains(0));
		}
		TEST_METHOD(contains_false_1)
		{
			StructuresDonnees::list<int> test;
			test.push_back(0);
			Assert::IsFalse(test.contains(1));
		}
		TEST_METHOD(remove_1)
		{
			StructuresDonnees::list<int> test;
			test.push_back(0);
			test.remove(0);
			Assert::IsTrue(test.is_empty());
		}
	};
	TEST_CLASS(TwoElementsList)
	{
		TEST_METHOD(is_empty_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.push_back(2);
			Assert::IsTrue(!test.is_empty());
		}
		TEST_METHOD(size_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.push_back(2);
			Assert::IsTrue(test.size() == 2);
		}
		TEST_METHOD(front_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.push_back(2);
			Assert::IsTrue(test.front() == 1);
		}
		TEST_METHOD(back_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.push_back(2);
			Assert::IsTrue(test.back() == 2);
		}
		TEST_METHOD(push_back_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.push_back(2);
			test.push_back(3);
			Assert::IsTrue(test.front() == 1);
			Assert::IsTrue(test.back() == 3);
			Assert::IsTrue(test.size() == 3);
		}
		TEST_METHOD(push_front_2)
		{
			StructuresDonnees::list<int> test;
			test.push_front(1);
			test.push_front(2);
			test.push_front(3);
			Assert::IsTrue(test.front() == 3);
			Assert::IsTrue(test.back() == 1);
			Assert::IsTrue(test.size() == 3);
		}
		TEST_METHOD(pop_back_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.push_back(2);
			test.pop_back();
			Assert::IsTrue(test.size() == 1);
		}
		TEST_METHOD(pop_front_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.push_back(2);
			test.pop_front();
			Assert::IsTrue(test.size() == 1);
		}
		TEST_METHOD(iteratorDereferencement_2)
		{
			StructuresDonnees::list<std::string> test;
			test.push_back("First");
			test.push_back("Second");
			Assert::IsTrue(*test.begin() == "First");
		}
		TEST_METHOD(r_iteratorDereferencement_2)
		{
			StructuresDonnees::list<std::string> test;
			test.push_back("First");
			test.push_back("Second");
			Assert::IsTrue(*test.rbegin() == "Second");
		}
		TEST_METHOD(iteratorIncrementation_2)
		{
			StructuresDonnees::list<std::string> test;
			test.push_back("First");
			test.push_back("Second");
			auto test2 = test.begin();
			++test2;
			Assert::IsTrue(*test2 == "Second");
		}
		TEST_METHOD(r_iteratorIncrementation_2)
		{
			StructuresDonnees::list<std::string> test;
			test.push_back("First");
			test.push_back("Second");
			auto test2 = test.rbegin();
			++test2;
			Assert::IsTrue(*test2 == "First");
		}
		TEST_METHOD(iteratorDecrementation_2)
		{
			StructuresDonnees::list<std::string> test;
			test.push_back("First");
			test.push_back("Second");
			auto test2 = test.end();
			--test2;
			Assert::IsTrue(*test2 == "Second");
		}
		TEST_METHOD(r_iteratorDecrementation_2)
		{
			StructuresDonnees::list<std::string> test;
			test.push_back("First");
			test.push_back("Second");
			auto test2 = test.rend();
			--test2;
			Assert::IsTrue(*test2 == "First");
		}
		TEST_METHOD(insert_begin_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(0);
			test.push_back(0);
			test.insert(test.begin(), 1);
			Assert::IsTrue(test.front() == 1);
		}
		TEST_METHOD(insert_between_2)
		{

			StructuresDonnees::list<int> test;
			test.push_back(0);
			test.push_back(0);
			test.insert(++test.begin(), 1);
			Assert::IsTrue(*(--(--test.end())) == 1);
		}
		TEST_METHOD(insert_between2_2)
		{

			StructuresDonnees::list<int> test;
			test.push_back(0);
			test.push_back(0);
			test.insert(++(++test.begin()), 1);
			Assert::IsTrue(*(--test.end()) == 1);
		}
		TEST_METHOD(insert_end_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(0);
			test.push_back(0);
			test.insert(test.end(), 1);
			Assert::IsTrue(test.back() == 1);
		}
		TEST_METHOD(erase_begin_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.push_back(2);
			test.erase(test.begin());
			Assert::IsTrue(test.size() == 1);
			Assert::IsTrue(test.front() == 2);
		}
		TEST_METHOD(erase_end_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.push_back(2);
			test.erase(--test.end());
			Assert::IsTrue(test.size() == 1);
			Assert::IsTrue(test.front() == 1);
		}
		TEST_METHOD(clear_2)
		{
			StructuresDonnees::list<int> test;
			test.clear();
			Assert::IsTrue(test.is_empty());
		}
		TEST_METHOD(swap_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.push_back(2);
			StructuresDonnees::list<int> test2;
			test2.push_back(3);
			test.swap(test2);
			Assert::IsTrue(test2.size() == 2);
			Assert::IsTrue(test2.front() == 1);
			Assert::IsTrue(test2.back() == 2);
			Assert::IsTrue(test.size() == 1);
			Assert::IsTrue(test.front() == 3);
		}
		TEST_METHOD(splice_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.push_back(2);
			StructuresDonnees::list<int> test2;
			test2.splice(test, test2.begin());
			Assert::IsTrue(test2.size() == 2);
			Assert::IsTrue(test2.front() == 1);
			Assert::IsTrue(test2.back() == 2);
		}
		TEST_METHOD(splice_withOneBegin_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.push_back(2);
			StructuresDonnees::list<int> test2;
			test2.push_back(3);
			test.splice(test2, test.begin());
			Assert::IsTrue(test.size() == 3);
			Assert::IsTrue(test.front() == 3);
			Assert::IsTrue(test.back() == 2);
		}
		TEST_METHOD(splice_withOneBetween_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.push_back(2);
			StructuresDonnees::list<int> test2;
			test2.push_back(3);
			test.splice(test2, ++test.begin());
			Assert::IsTrue(test.size() == 3);
			Assert::IsTrue(test.front() == 1);
			Assert::IsTrue(test.back() == 2);
		}
		TEST_METHOD(splice_withOneEnd_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.push_back(2);
			StructuresDonnees::list<int> test2;
			test2.push_back(3);
			test.splice(test2, test.end());
			Assert::IsTrue(test.size() == 3);
			Assert::IsTrue(test.front() == 1);
			Assert::IsTrue(test.back() == 3);
		}
		TEST_METHOD(reverse_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.push_back(2);
			test.reverse();
			Assert::IsTrue(test.front() == 2);
			Assert::IsTrue(test.back() == 1);
		}
		TEST_METHOD(contains_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(0);
			test.push_back(1);
			Assert::IsTrue(test.contains(0));
		}
		TEST_METHOD(contains_false_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(0);
			test.push_back(-1);
			Assert::IsFalse(test.contains(1));
		}
		TEST_METHOD(unique_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(0);
			test.push_back(0);
			test.unique();
			Assert::IsTrue(test.size() == 1);
			Assert::IsTrue(test.front() == 0);
			Assert::IsTrue(test.back() == 0);
		}
		TEST_METHOD(unique_unique_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(0);
			test.push_back(1);
			test.unique();
			Assert::IsTrue(test.size() == 2);
			Assert::IsTrue(test.front() == 0);
			Assert::IsTrue(test.back() == 1);
		}
		TEST_METHOD(remove_oneElement_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(0);
			test.push_back(1);
			test.remove(0);
			Assert::IsTrue(test.size() == 1);
		}
		TEST_METHOD(remove_twoElement_2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(0);
			test.push_back(0);
			test.remove(0);
			Assert::IsTrue(test.is_empty());
		}

	};
	TEST_CLASS(MoreThanTwoElementsList)
	{
		TEST_METHOD(reverse_more2)
		{
			StructuresDonnees::list<int> test;
			test.push_back(1);
			test.push_back(2);
			test.push_back(3);
			test.push_back(4);
			test.push_back(5);
			test.push_back(6);
			test.reverse();
			Assert::IsFalse(true);
		}
	};
}