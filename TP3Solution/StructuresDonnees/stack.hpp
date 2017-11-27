#pragma once
namespace StructuresDonnees
{
	template <class T>
	class stack
	{	
		struct Boite
		{
			T valeur;
			Boite* next;
			Boite(T valeur, Boite* next = nullptr) : valeur(valeur), next(next) {};
			~Boite() {};
		};
		using size_t = unsigned long;
		Boite* top_element;
		size_t sz = 0;
	public:
		stack() : top_element(nullptr) {};
		~stack()
		{
			for (Boite* i = top_element; i != nullptr;)
			{
				Boite* temp = i->next;
				delete i;
				i = temp;
			}
		};
		void push(T valeur)
		{
			top_element = new Boite(valeur, top_element);
			sz++;
		}
		void pop()
		{
			Boite* next = top_element->next;
			delete top_element;
			top_element = next;
			sz--;
		}
		size_t size() const
		{
			return sz;
		}
		T& top()
		{
			return top_element->valeur;
		}
		bool is_empty()
		{
			return top_element == nullptr;
		}
		void swap(stack<T>& other) noexcept
		{
			std::swap(other.top_element, top_element);
			std::swap(other.sz, sz);
		}
	};
}