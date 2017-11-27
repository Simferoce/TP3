#include "ArmeBase.h"

const std::string ArmeBase::texturePath = "Gem.png";
sf::Texture ArmeBase::texture = sf::Texture();
const sf::Time ArmeBase::delaiEntreLesTirsDeBase= sf::milliseconds(100);
bool ArmeBase::initTexture()
{
	if(!texture.loadFromFile(texturePath))
		return false;
	return true;
}

StructuresDonnees::list<Projectile*> ArmeBase::Tire()
{
	StructuresDonnees::list<Projectile*> projectiles;
	return projectiles;
}

ArmeBase::ArmeBase() : Arme(texture, delaiEntreLesTirsDeBase)
{
}

ArmeBase::~ArmeBase()
{
}
