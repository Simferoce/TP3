#pragma once
#include <exception>
#include <iterator>
namespace StructuresDonnees
{
	class EmptyList
		: public std::exception
	{
	public:
		EmptyList() : std::exception() {}
		EmptyList(char const* message) : std::exception(message) {}
	};
	template< class T>
	class list
	{
		class NoValueBox
		{
		public:
			NoValueBox* avant;
			NoValueBox* apres;
			NoValueBox(NoValueBox* avant = nullptr, NoValueBox* apres = nullptr) : avant{ avant }, apres{ apres } {}
			virtual ~NoValueBox(){};
		};
		class Box
			: public NoValueBox
		{
		public:
			T value;
			Box(T value = {}, NoValueBox* avant = nullptr, NoValueBox* apres = nullptr) : NoValueBox(avant,apres), value{ value } {}
		};
		using size_t = unsigned long int;
		NoValueBox* apresFin;
		NoValueBox* avantDebut;
		size_t sz;
	public:
		class iterator
		{
			friend list;
		private:
			NoValueBox* pos;
		public:
			iterator(NoValueBox* pos = nullptr) : pos{pos} {}
			~iterator() = default;
			T operator*()
			{
				if(auto posAsBox = dynamic_cast<Box*>(pos))
					return posAsBox->value;
				throw std::out_of_range("Déréférence un itérateur pointant sur une zone qui ne contient pas de données concrètes");
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
		private:
			NoValueBox* pos;
		public:
			reverse_iterator(NoValueBox* pos = nullptr) : pos{ pos } {}
			~reverse_iterator() = default;
			T operator*()
			{
				if(auto posAsBox = dynamic_cast<Box*>(pos))
					return posAsBox->value;
				throw std::out_of_range("Déréférence un itérateur pointant sur une zone qui ne contient pas de données concrètes");
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
		list() : apresFin{ new NoValueBox() }, avantDebut{ new NoValueBox() }, sz{ 0 }
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
			NoValueBox* elementToDelete = avantDebut->apres;
			for (int i = 0; i < size(); i++)
			{
				NoValueBox* temp = elementToDelete->apres;
				delete elementToDelete;
				elementToDelete = temp;
			}
				avantDebut->apres = apresFin;
				apresFin->avant = avantDebut;
			sz = 0;
		}
		void insert(const iterator& position, T value)
		{
			NoValueBox* temp = position.pos->avant;
			temp->apres = position.pos->avant = new Box(value, temp, position.pos);
			sz++;
		}
		T erase(iterator position)
		{
			if (is_empty())
				throw EmptyList("Tentative de suppression d'un élément dans une liste vide.");
			if (!dynamic_cast<Box*>(position.pos))
				throw std::out_of_range("Suppression d'un element invalide.");
			T value = reinterpret_cast<Box*>(position.pos)->value;
			position.pos->avant->apres = position.pos->apres;
			position.pos->apres->avant = position.pos->avant;
			delete position.pos;
			position.pos = nullptr;
			sz--;
			return value;
		}
		void push_back(T value)
		{
			insert(end(),value);
		}
		void push_front(T value)
		{
			insert(begin(), value);
		}
		T pop_back()
		{
			return erase(--end());
		}
		T pop_front()
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
		T front() const
		{
			if (auto firstBox = dynamic_cast<Box*>(avantDebut->apres))
				return firstBox->value;
			throw EmptyList("Essaie d'accéder au première élément d'une liste vide.");
		}
		T back() const
		{
			if (auto lastBox = dynamic_cast<Box*>(apresFin->avant))
				return lastBox->value;
			throw EmptyList("Essaie d'accéder au dernier élément d'une liste vide.");
		}
		void swap(list<T>& other) noexcept
		{
			std::swap(avantDebut, other.avantDebut);
			std::swap(apresFin, other.apresFin);
			std::swap(sz, other.sz);
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
