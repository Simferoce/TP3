#pragma once
#include "TypeWeapon.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
class Projectile
	: public sf::Sprite
{
protected:
	int dommage;
	float vitesse;
	TypeWeapon type;
public:
	Projectile(sf::Texture &texture, TypeWeapon type, float vitesse, sf::Vector2f pos, float angle, int dommage) : type{type}, vitesse {vitesse}, dommage(dommage)
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
		move(cos(getRotation() * (3.1415926 / 180)) * vitesse, sin(getRotation() * (3.1415926 / 180)) * vitesse);
	}
	virtual void Draw(sf::RenderWindow& window)
	{
		window.draw(*this);
	}
	TypeWeapon GetType()
	{
		return type;
	}
	virtual int GetDommage()
	{
		return dommage;
	}
};
