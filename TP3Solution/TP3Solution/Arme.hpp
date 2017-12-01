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
	int munition;
public:
	Arme(sf::Texture& texture, sf::Time tempsEntreTir, int munition , Vector2f pos = Vector2f(0, 0) ) : Bonus(texture , pos), tempsEntreTir{tempsEntreTir}, munition{munition}
	{
		setTexture(texture);
		setPosition(pos);
		setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);

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
