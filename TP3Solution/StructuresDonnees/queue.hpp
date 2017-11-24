#pragma once
#include <array>
namespace StructuresDonnees
{
	template <class T>
	class CircularQueue
	{
		struct Box
		{
			T value;
			Box* next;
			Box(const T& value, Box* next) :value(value), next(next) {}
		};
		CircularQueue(const CircularQueue&) = delete;
		Box *last;
		size_t sz;
	public:
		CircularQueue() : last(nullptr), sz(0)
		{
		};
		~CircularQueue() 
		{
			Box* temp = last;
			if (last != nullptr)
			{
				for (auto iter = last->next; iter != last;)
				{
					temp = iter;
					iter = iter->next;
					delete temp;
				}
			}
		}
		CircularQueue& operator=(const CircularQueue<T>& other)
		{
			Box* i = other.last;
			if (i != nullptr)
				do
				{
					push(i->next->value);
					i = i->next;
				} while (i != other.last);
				return *this;
		}
		T& front() {
			return last->next->value;
		}
		T& back()
		{
			return last->value;
		}
		const T& front() const
		{
			return last->next->value;
		}
		const T& back() const
		{
			return last->value;
		}
		bool empty() const
		{
			return sz == 0;
		};
		size_t size() const
		{
			return sz;
		};
		void push(const T& value)
		{
			if (last != nullptr)
			{
				last = last->next = new Box(value, last->next);
			}
			else
			{
				last = new Box(value, nullptr);
				last->next = last;
			}
			sz++;
		}
		void pop()
		{
			if (last != nullptr)
			{
				Box* temp = last->next;
				last->next = last->next->next;
				if (temp == last)
					last = nullptr;
				delete temp;
				temp = nullptr;
				sz--;
			}
		};
		void swap(CircularQueue& other) noexcept
		{
			std::swap(last, other.last);
			std::swap(sz, other.sz);
		};
	};
}
