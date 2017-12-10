#include "ProjectileCharge.h"
#include <SFML/Graphics/Texture.hpp>

const std::string ProjectileCharge::texturePath = "Ressources\\Sprites\\Projectiles\\BossBullet_48x16.png";
sf::Texture ProjectileCharge::texture = sf::Texture();
const float ProjectileCharge::vitesseDeBase = 8.0f;
const int ProjectileCharge::dommageDeBase = 1;
const double ProjectileCharge::dommagePerCharge = 0.04;
bool ProjectileCharge::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}

ProjectileCharge::ProjectileCharge(TypeWeapon type, Personnage* tireur, float angle, int charge, float scale) : Projectile(texture, type, vitesseDeBase, tireur, angle, dommageDeBase), charge{charge}
{
	setScale(scale, scale);
}


ProjectileCharge::~ProjectileCharge()
{
}

int ProjectileCharge::GetDommage()
{
	return dommageDeBase + charge*dommagePerCharge;
}
