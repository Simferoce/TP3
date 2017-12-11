#include "ProjectileBase.h"
#include <SFML/Graphics/Texture.hpp>

const std::string ProjectileBase::texturePath = "Ressources\\Sprites\\Projectiles\\Bullet_16x4.png";
sf::Texture ProjectileBase::texture = sf::Texture();
const float ProjectileBase::vitesseDeBase = 8.0f;
const int ProjectileBase::dommageDeBase = 1;
bool ProjectileBase::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}

ProjectileBase::ProjectileBase(TypeWeapon type, Personnage* tireur, float angle) : Projectile(texture, type, vitesseDeBase, tireur, angle, dommageDeBase)
{
}


ProjectileBase::~ProjectileBase()
{
}
