#pragma once
#include "TypeWeapon.h"
#include <SFML/Graphics/Sprite.hpp>
class Projectile
	: public sf::Sprite
{
protected:
	float vitesse;
	TypeWeapon type;
public:
	Projectile(sf::Texture &texture, TypeWeapon type, float vitesse, sf::Vector2f pos, float angle) : type{type}, vitesse {vitesse}
	{
		setTexture(texture);
		if (type == TypeWeapon::EnemyGreen)
			setColor(sf::Color::Green);
		else if (type == TypeWeapon::EnemyRed)
			setColor(sf::Color::Red);
		else if (type == TypeWeapon::EnemyYellow)
			setColor(sf::Color::Yellow);
		setPosition(pos);
		setRotation(angle);
	}
	virtual ~Projectile()
	{
	}
	virtual void Update()
	{
		move(cos(getRotation() * (180 /3.14)) * vitesse, sin(getRotation() * (180 / 3.14)) * vitesse);
	}
};
