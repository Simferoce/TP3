#pragma once
#include <vector>

class Composite
{
protected:
	StructuresDonnees::list<Composite*> composites;
public:
	StructuresDonnees::list<Composite*>& GetComposites()
	{
		return composites;
	}
	void AjouterComposite(Composite* composite)
	{
		composites.push_back(composite);
	}
	virtual ~Composite()
	{
		for (Composite* composite : composites)
			delete composite;
	};
};
