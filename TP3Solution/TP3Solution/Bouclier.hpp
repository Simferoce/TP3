#pragma once
#include "Bonus.h"
#include "TypeWeapon.h"

class Bouclier :
	public Bonus
{
protected:
	int ptsVie;
	TypeWeapon type;
public:
	Bouclier::Bouclier(sf::Texture& texture, int ptsVie, TypeWeapon type) : Bonus(texture), ptsVie{ ptsVie }, type{ type }
	{
		if (type == TypeWeapon::EnemyGreen)
			setColor(sf::Color::Green);
		else if (type == TypeWeapon::EnemyRed)
			setColor(sf::Color::Red);
		else if (type == TypeWeapon::EnemyYellow)
			setColor(sf::Color::Yellow);
	}
	TypeWeapon GetTypeBouclier() const { return type; };
	virtual ~Bouclier(){};	
	/// <summary>
	/// Recoit le dommage.
	/// </summary>
	/// <param name="type">Le type de dommage</param>
	/// <param name="dommage">Le dommage</param>
	/// <returns>Le nbre de dommage non absorbé.</returns>
	virtual int RecoitDommage(TypeWeapon type, int dommage)
	{
		if (this->type == type)
			ptsVie -= dommage;
		return ptsVie < 0 ? ptsVie * -1 : ptsVie;
	};
	bool Detruit() const { return ptsVie <= 0; };
};

