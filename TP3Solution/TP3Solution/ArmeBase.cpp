#include "ArmeBase.h"
#include "ProjectileBase.h"

const std::string ArmeBase::texturePath = "Gem.png";
sf::Texture ArmeBase::texture = sf::Texture();
const sf::Time ArmeBase::delaiEntreLesTirsDeBase= sf::milliseconds(300);
const int ArmeBase::munition = -1;
const std::string ArmeBase::nomArme = "Arme de base";
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

std::string ArmeBase::GetNomArme() const
{
	return nomArme;
}

ArmeBase::ArmeBase() : Arme(texture, delaiEntreLesTirsDeBase, munition)
{
}

ArmeBase::~ArmeBase()
{
}
