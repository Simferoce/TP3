#pragma once
#include "Bonus.h"
#include <SFML/System/Time.hpp>
#include "../StructuresDonnees/list.hpp"
#include "Projectile.hpp"
class Arme
	:public Bonus
{
protected:
	sf::Time tempsEntreTir;
public:
	Arme(sf::Texture& texture, sf::Time tempsEntreTir) : Bonus(texture), tempsEntreTir{tempsEntreTir}
	{
		setTexture(texture);
	}
	virtual ~Arme()
	{
		
	}
	virtual StructuresDonnees::list<Projectile*>* Tire(sf::Vector2f origineDuTir, TypeWeapon type, float angle) = 0;
	sf::Time GetTempsEntreTir() const
	{
		return tempsEntreTir;
	}
};
