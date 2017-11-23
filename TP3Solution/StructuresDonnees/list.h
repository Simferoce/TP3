#pragma once
#include <iterator>
namespace StructuresDonnees
{
	template< class T>
	class list
	{
		class Box
		{
		public:
			Box* avant;
			Box* apres;
			T* value;
			Box(T& value, Box* avant = nullptr, Box* apres = nullptr): value { &value }, avant{ avant }, apres{ apres } {}
			Box(T* value = nullptr, Box* avant = nullptr, Box* apres = nullptr) :value{ value }, avant{ avant }, apres{apres} {}
		};
		using size_t = unsigned long int;
		Box* apresFin;
		Box* avantDebut;
		size_t sz;
	public:
		class iterator :
			public std::iterator<T,T>
		{
			friend list;
			Box* pos;
		public:
			iterator(Box* pos = nullptr) : pos{pos} {}
			~iterator() = default;
			T& operator*()
			{
				return *(pos->value);
			}
			bool operator!=(const iterator& other)
			{
				return !(other.pos->apres == pos->apres && other.pos->avant == pos->avant);
			}
			iterator operator++()
			{
				return pos = pos->apres;
			}
			iterator operator--()
			{
				return pos = pos->avant;
			}
			iterator* operator=(const iterator& other)
			{
				pos = other.pos;
				return this;
			}
			bool operator==(const iterator& other) const
			{
				return pos == other.pos;
			}
			iterator(const iterator& other)
			{
				*this = other;
			}
		};
		class reverse_iterator
		{
			friend list;
			Box* pos;
		public:
			reverse_iterator(Box* pos = nullptr) : pos{ pos } {}
			~reverse_iterator() = default;
			T& operator*()
			{
					return *(pos->value);
			}
			bool operator!=(const reverse_iterator& other)
			{
				return !(other.pos->apres == pos->apres && other.pos->avant == pos->avant);
			}
			reverse_iterator operator++()
			{
				return pos=pos->avant;
			}
			reverse_iterator operator--()
			{
				return pos=pos->apres;
			}
			reverse_iterator* operator=(const reverse_iterator& other)
			{
				pos = other.pos;
				return this;
			}
			bool operator==(const reverse_iterator& other) const
			{
				return pos == other.pos;
			}
			reverse_iterator(const reverse_iterator& other)
			{
				this = *other;
			}
		};
		list() : apresFin{ new Box() }, avantDebut{ new Box() }, sz{ 0 }
		{
			apresFin->avant = avantDebut;
			avantDebut->apres = apresFin;
		}
		~list()
		{
			clear();
			delete avantDebut;
			delete apresFin;
		}
		void clear()
		{
			Box* elementToDelete = avantDebut->apres;
			for (int i = 0; i < size(); i++)
			{
				Box* temp = elementToDelete->apres;
				delete elementToDelete->value;
				delete elementToDelete;
				elementToDelete = temp;
			}
				avantDebut->apres = apresFin;
				apresFin->avant = avantDebut;
			sz = 0;
		}
		void insert(const iterator& position, T &&value)
		{
			Box* temp = position.pos->avant;
			temp->apres = position.pos->avant = new Box(*(new T(value)), temp, position.pos);
			sz++;
		}
		void insert(const iterator& position, T &value)
		{
			Box* temp = position.pos->avant;
			temp->apres = position.pos->avant = new Box(value, temp, position.pos);
			sz++;
		}
		void erase(iterator position)
		{
			position.pos->avant->apres = position.pos->apres;
			position.pos->apres->avant = position.pos->avant;
			delete position.pos->value;
			delete position.pos;
			sz--;
		}
		void push_back( T &value)
		{
			insert(end(),value);
		}
		void push_front( T &value)
		{
			insert(begin(), value);
		}
		void push_back(T &&value)
		{
			Box* temp = apresFin->avant;
			temp->apres = apresFin->avant = new Box(*(new T(value)), temp, apresFin);
			sz++;
		}
		void push_front(T &&value)
		{
			Box* temp = avantDebut->apres;
			temp->avant = avantDebut->apres = new Box(*(new T(value)), avantDebut, temp);
			sz++;
		}
		void pop_back()
		{
			return erase(--end());
		}
		void pop_front()
		{
			return erase(begin());
		}
		bool is_empty() const
		{
			return sz == 0;
		}
		size_t size() const
		{
			return sz;
		}
		T& front() const
		{
				return *(avantDebut->apres->value);
		}
		T& back() const
		{
	
				return *(apresFin->avant->value);
		
		}
		void swap(list<T>& other) noexcept
		{
			std::swap(avantDebut, other.avantDebut);
			std::swap(apresFin, other.apresFin);
			std::swap(sz, other.sz);
		}
		void splice(list<T>& other, iterator position)
		{
			position.pos->avant->apres = other.avantDebut->apres;
			other.avantDebut->apres->avant = position.pos->avant;
			position.pos->avant = other.apresFin->avant;
			other.apresFin->avant->apres = position.pos;
			sz += other.size();
			other.sz = 0;
			other.avantDebut->apres = other.apresFin;
			other.apresFin->avant = other.avantDebut;
		}
		void reverse()
		{
			Box* elementToChange = avantDebut;
			for(int i = 0; i < sz + 2; i++)
			{
				Box* temp = elementToChange->apres;
				std::swap(elementToChange->avant, elementToChange->apres);
				elementToChange = temp;
			}
			std::swap(avantDebut, apresFin);
		}
		bool contains(const T& value)
		{
			for(auto iter=begin(); iter != end(); ++iter)
			{
				if (*iter == value)
					return true;
			}
			return false;
		}
		void unique()
		{
			//TO DO

			for(auto iter = begin();  iter != end(); ++iter)
			{
				if(iter.pos->avant != avantDebut && *(iter.pos->avant->value) == *iter)
				{
					auto iter2 = --iter;
					++iter;
					erase(iter2);
				}
			}
		}
		iterator begin() const
		{
			return iterator(avantDebut->apres);
		}
		iterator end() const
		{
			return iterator(apresFin);
		}
		reverse_iterator rbegin() const
		{
			return reverse_iterator(apresFin->avant);
		}
		reverse_iterator rend() const
		{
			return reverse_iterator(avantDebut);
		}
	};
}
