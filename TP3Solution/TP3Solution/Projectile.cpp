#include "Projectile.h"
#include "Personnage.hpp"
Projectile::Projectile(sf::Texture &texture, TypeWeapon type, float vitesse, Personnage* tireur, float angle, int dommage) : type{ type }, vitesse{ vitesse }, dommage(dommage), tireur{tireur}
{
	setTexture(texture);
	if (type == TypeWeapon::EnemyGreen)
		setColor(sf::Color::Green);
	else if (type == TypeWeapon::EnemyRed)
		setColor(sf::Color::Red);
	else if (type == TypeWeapon::EnemyYellow)
		setColor(sf::Color::Yellow);
	setPosition(tireur->getPosition());
	setRotation(angle);
}

void Projectile::Update()
{
	move(cos(getRotation() * (3.1415926 / 180)) * vitesse, sin(getRotation() * (3.1415926 / 180)) * vitesse);
}

void Projectile::Draw(sf::RenderWindow & window)
{
	window.draw(*this);
}
