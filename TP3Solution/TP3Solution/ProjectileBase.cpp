#include "ProjectileBase.h"
#include <SFML/Graphics/Texture.hpp>

const std::string ProjectileBase::texturePath = "Gem.png";
sf::Texture ProjectileBase::texture = sf::Texture();
const float ProjectileBase::vitesseDeBase = 8.0f;
bool ProjectileBase::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}

ProjectileBase::ProjectileBase(ProjectileType type, sf::Vector2f pos, float angle) : Projectile(texture, type, vitesseDeBase, pos, angle)
{
}


ProjectileBase::~ProjectileBase()
{
}
