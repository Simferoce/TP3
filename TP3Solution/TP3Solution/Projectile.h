#pragma once
#include "TypeWeapon.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Personnage;
class Projectile
	: public sf::Sprite
{
protected:
	int dommage;
	float vitesse;
	TypeWeapon type;
	Personnage* tireur;
public:
	Projectile(sf::Texture &texture, TypeWeapon type, float vitesse, Personnage* tireur, float angle, int dommage);
	virtual ~Projectile()
	{
	}
	virtual void Update();
	virtual void Draw(sf::RenderWindow& window);
	TypeWeapon GetType()
	{
		return type;
	}
	virtual int GetDommage()
	{
		return dommage;
	}
};
