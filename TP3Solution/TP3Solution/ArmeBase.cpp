#include "ArmeBase.h"
#include "ProjectileBase.h"

const std::string ArmeBase::texturePath = "Gem.png";
sf::Texture ArmeBase::texture = sf::Texture();
const sf::Time ArmeBase::delaiEntreLesTirsDeBase= sf::milliseconds(100);
bool ArmeBase::initTexture()
{
	if(!texture.loadFromFile(texturePath))
		return false;
	return true;
}
StructuresDonnees::list<Projectile*>* ArmeBase::Tire(sf::Vector2f origineDuTir, TypeWeapon type, float angle)
{
	StructuresDonnees::list<Projectile*>* projectiles = new StructuresDonnees::list<Projectile*>;
	projectiles->push_back(new ProjectileBase(type, origineDuTir, angle));
	return projectiles;
}

ArmeBase::ArmeBase() : Arme(texture, delaiEntreLesTirsDeBase)
{
}

ArmeBase::~ArmeBase()
{
}
