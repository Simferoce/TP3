#include "ProjectileBase.h"
#include <SFML/Graphics/Texture.hpp>

const std::string ProjectileBase::texturePath = "Gem.png";
sf::Texture ProjectileBase::texture = sf::Texture();
const float ProjectileBase::vitesseDeBase = 0.0f;
bool ProjectileBase::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}

ProjectileBase::ProjectileBase(ProjectileType type) : Projectile(texture, type, vitesseDeBase)
{
}


ProjectileBase::~ProjectileBase()
{
}
