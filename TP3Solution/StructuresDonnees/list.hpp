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
			Box(T* value = nullptr, Box* avant = nullptr, Box* apres = nullptr) :value{ value }, avant{ avant }, apres{apres} {}
		};
		using size_t = unsigned long int;
		Box apresFin;
		Box avantDebut;
		size_t sz;
	public:
		class iterator : public std::iterator<std::bidirectional_iterator_tag, T>
		{
		protected:
			friend list;
			Box* pos;
		public:
			iterator(Box* x = nullptr) :pos(x) {}
			iterator(const iterator& mit) : pos(mit.pos) {}
			iterator& operator++() { pos = pos->apres; return *this; }
			iterator operator++(int) { iterator tmp(*this); operator++(); return tmp; }
			iterator& operator--() { pos = pos->avant; return *this; }
			iterator operator--(int) { iterator tmp(*this); operator++(); return tmp; }
			bool operator==(const iterator& rhs) const { return pos == rhs.pos; }
			bool operator!=(const iterator& rhs) const { return pos != rhs.pos; }
			T& operator*() { return *(pos->value); }
		};
		class reverse_iterator
			: public iterator
		{
		public:
			reverse_iterator(Box* pos = nullptr) :iterator(pos) {}
			reverse_iterator operator++(){ return pos=pos->avant; }
			reverse_iterator operator++(int) { reverse_iterator tmp(*this); operator++(); return tmp; }
			reverse_iterator operator--(){ return pos=pos->apres; }
			reverse_iterator operator--(int) { reverse_iterator tmp(*this); operator++(); return tmp; }
		};

		list() : apresFin{ Box() }, avantDebut{ Box() }, sz{ 0 }
		{
			apresFin.avant = &avantDebut;
			avantDebut.apres = &apresFin;
		}
		~list()
		{
			clear();
		}
		void clear()
		{
			Box* elementToDelete = avantDebut.apres;
			for (int i = 0; i < size(); i++)
			{
				Box* temp = elementToDelete->apres;
				delete elementToDelete->value;
				delete elementToDelete;
				elementToDelete = temp;
			}
			avantDebut.apres = &apresFin;
			apresFin.avant = &avantDebut;
			sz = 0;
		}
		void insert(const iterator& position, T &&value)
		{
			Box* temp = position.pos->avant;
			temp->apres = position.pos->avant = new Box(new T(value), temp, position.pos);
			sz++;
		}
		void insert(const iterator& position, const T &value)
		{
			Box* temp = position.pos->avant;
			temp->apres = position.pos->avant = new Box(new T(value), temp, position.pos);
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
		void push_back(T &value)
		{
			insert(end(),value);
		}
		void push_front(T &value)
		{
			insert(begin(), value);
		}
		void push_back(T &&value)
		{
			insert(end(), value);
		}
		void push_front(T &&value)
		{
			insert(begin(), value);
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
				return *(avantDebut.apres->value);
		}
		T& back() const
		{
				return *(apresFin.avant->value);
		}
		void swap(list<T>& other) noexcept
		{
			std::swap(avantDebut, other.avantDebut);
			std::swap(apresFin, other.apresFin);
			std::swap(sz, other.sz);
		}
		void splice(list<T>& other, const iterator& position)
		{
			position.pos->avant->apres = other.avantDebut.apres;
			other.avantDebut.apres->avant = position.pos->avant;
			position.pos->avant = other.apresFin.avant;
			other.apresFin.avant->apres = position.pos;
			sz += other.size();
			other.sz = 0;
			other.avantDebut.apres = &other.apresFin;
			other.apresFin.avant = &other.avantDebut;
		}
		void reverse()
		{
			Box* elementToChange = &avantDebut;
			for(int i = 0; i < sz+2; i++)
			{
				Box* temp = elementToChange;
				std::swap(elementToChange->avant, elementToChange->apres);
				elementToChange = temp->avant;
			}
			std::swap(apresFin.apres->avant, avantDebut.avant->apres);
			std::swap(apresFin, avantDebut);
		}
		void unique()
		{
			for(auto iter = begin();  iter != end(); ++iter)
			{
				if(iter.pos->avant != &avantDebut && *(iter.pos->avant->value) == *iter)
				{
					erase(iter.pos->avant);
				}
			}
		}
		void remove(const T& value)
		{
			for (auto iter = begin(); iter != end();)
			{
				if (*iter == value)
				{
					++iter;
					erase(iter.pos->avant);
				}
				else
				{
					++iter;
				}	
			}
		}
		void assign(const size_t numberOfElement, const T& value)
		{
			clear();
			for(int i = 0; i < numberOfElement; i++)
				push_back(value);
		}
		void assign(const size_t numberOfElement, T&& value)
		{
			clear();
			for (int i = 0; i < numberOfElement; i++)
			{
				insert(end(),value);
			}
		}
		void assign(const iterator& first, const iterator& last)
		{
			for (auto iter = first; iter != last; ++iter)
				push_back(T(*iter));
		}
		iterator begin() 
		{
			return iterator(avantDebut.apres);
		}
		iterator end() 
		{
			return iterator(&apresFin);
		}
		reverse_iterator rbegin() 
		{
			return reverse_iterator(apresFin.avant);
		}
		reverse_iterator rend()
		{
			return reverse_iterator(&avantDebut);
		}
	};
}
