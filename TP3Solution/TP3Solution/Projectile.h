#pragma once
#include "ProjectileType.h"
#include <SFML/Graphics/Sprite.hpp>
class Projectile
	: public sf::Sprite
{
protected:
	float vitesse;
	ProjectileType type;
public:
	Projectile(sf::Texture &texture, ProjectileType type, float vitesse) : type{type}, vitesse {vitesse}
	{
	}
	virtual ~Projectile()
	{
	}
	virtual void Update()
	{
		move(cos(getRotation() * (180 /3.14)) * vitesse, sin(getRotation() * (180 / 3.14)) * vitesse);
	}
};
