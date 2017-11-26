#pragma once
#include <array>
namespace StructuresDonnees
{
	template <class T>
	class Queue
	{
		T* tab;
		size_t sz;
		size_t cap;
		size_t zero;
	public:
		Queue() : tab{ new T[1] }, sz{0}, cap{1}, zero{0}
		{
		}
		~Queue() 
		{
			delete[] tab;
		}
		Queue(const Queue& other)
		{
			tab = new T[other.cap];
			cap = other.cap;
			sz = other.sz;
			zero = 0;
			for (int i = 0; i < other.sz; i++)
				tab[i] = other.tab[zero + i % cap];
		}
		Queue& operator=(const Queue<T>& other)
		{
			delete[] tab;
			tab = new T[other.cap];
			cap = other.cap;
			sz = other.sz;
			zero = 0;
			for (int i = 0; i < other.sz; i++)
				tab[i] = other.tab[zero + i % cap];
			return *this;
		}
		T& operator[](const size_t& index)
		{
			return tab[zero + index % cap];
		}
		T& front() {
			return tab[zero];
		}
		T& back()
		{
			return tab[(zero + sz - 1) % cap];
		}
		const T& front() const
		{
			return tab[(zero + sz - 1) % cap];
		}
		const T& back() const
		{
			return tab[zero];;
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
			if(cap == sz)
			{
				T* temp = new T[cap*2];
				for (int i = 0; i < sz; i++)
					temp[i] = tab[i + zero%cap];
				delete[] tab;
				tab = temp;
				cap = 2 * cap;
				zero = 0;
			}
			tab[(zero + sz) % cap] = value;
			sz++;
		}
		void pop()
		{

			zero = (zero + 1) % cap;
			sz--;
		}
		void swap(Queue& other) noexcept
		{
			std::swap(tab, other.tab);
			std::swap(sz, other.sz);
			std::swap(cap, other.cap);
			std::swap(zero, other.zero);
		}
	};
}
