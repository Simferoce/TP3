#pragma once
namespace StructuresDonnees
{
	template <class T>
	struct Boite
	{
		T valeur;
		Boite* next;
		Boite(T valeur, Boite* next = nullptr) : valeur(valeur), next(next) {};
		~Boite() {};
	};
	template <class T>
	class stack
	{
		using size_t = unsigned long;
		Boite<T>* top_element;
	public:
		stack() : top_element(nullptr) {};
		~stack()
		{
			for (Boite<T>* i = top_element; i != nullptr;)
			{
				Boite<T>* temp = i->next;
				delete i;
				i = temp;
			}
		};
		void push(T valeur)
		{
			top_element = new Boite<T>(valeur, top_element);
		}
		T pop()
		{
			T valeur = top->valeur;
			Boite<T>* next = top->next;
			delete top_element;
			top = next;
			return valeur;
		}
		size_t size() const
		{
			size_t size = 0;
			for (Boite<T>* element; element != nullptr; element->next)
			{
				size++;
			}
			return size;
		}
		Boite<T>* top()
		{
			return top_element;
		}
		bool is_empty()
		{
			return top_element == nullptr;
		}
	};
}