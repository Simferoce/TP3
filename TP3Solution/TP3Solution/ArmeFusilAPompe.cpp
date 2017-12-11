#include "ArmeFusilAPompe.h"
#include "ProjectileBase.h"
#include "Personnage.hpp"
const std::string ArmeFusilAPompe::texturePath = "Gem.png";
sf::Texture ArmeFusilAPompe::texture = sf::Texture();
const sf::Time ArmeFusilAPompe::delaiEntreLesTirsDeBase = sf::milliseconds(300);
const int ArmeFusilAPompe::munition = 50;
const std::string ArmeFusilAPompe::nomArme = "Fusil A Pompe";
bool ArmeFusilAPompe::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}
StructuresDonnees::list<Projectile*>* ArmeFusilAPompe::Tire(Personnage* tireur, TypeWeapon type, float angle)
{
	StructuresDonnees::list<Projectile*>* projectiles = new StructuresDonnees::list<Projectile*>;
	projectiles->push_back(new ProjectileBase(type, tireur, angle));
	--Arme::munition;
	if(Arme::munition != 0)
	{
		projectiles->push_back(new ProjectileBase(type, tireur, angle - angleSpread));
		--Arme::munition;
	}
	if (Arme::munition != 0)
	{
		projectiles->push_back(new ProjectileBase(type, tireur, angle + angleSpread));
		--Arme::munition;
	}
	return projectiles;
}

std::string ArmeFusilAPompe::GetNomArme() const
{
	return nomArme;
}

ArmeFusilAPompe::ArmeFusilAPompe() : Arme(texture, delaiEntreLesTirsDeBase, munition)
{
}

ArmeFusilAPompe::~ArmeFusilAPompe()
{
}

