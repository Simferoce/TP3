#include "ProjectileLaserPercant.h"
#include <SFML/Graphics/Texture.hpp>
#include "Personnage.hpp"
const std::string ProjectileLaserPercant::texturePath = "Ressources\\Sprites\\Projectiles\\Laser_1280x32.png";
sf::Texture ProjectileLaserPercant::texture = sf::Texture();
const float ProjectileLaserPercant::vitesseDeBase = 0.0f;
const int ProjectileLaserPercant::dommageDeBase = 1;
const sf::Time ProjectileLaserPercant::duree = sf::milliseconds(2000);
bool ProjectileLaserPercant::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}

ProjectileLaserPercant::ProjectileLaserPercant(TypeWeapon type, Personnage* tireur, float angle, int charge) : Projectile(texture, type, vitesseDeBase, tireur, angle, dommageDeBase), charge{ charge }
{
	setOrigin(0, getGlobalBounds().height / 2);
	clock.restart();
	naissance = clock.getElapsedTime();
}

bool ProjectileLaserPercant::EstPasserDate()
{

	return clock.getElapsedTime() - naissance > duree;
}


ProjectileLaserPercant::~ProjectileLaserPercant()
{
}

void ProjectileLaserPercant::Update()
{
	setPosition(tireur->getPosition());
}

int ProjectileLaserPercant::GetDommage()
{
	return dommageDeBase;
}
