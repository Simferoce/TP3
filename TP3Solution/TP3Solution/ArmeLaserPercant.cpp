#include "ArmeLaserPercant.h"
#include "ProjectileLaserPercant.h"
const std::string ArmeLaserPercant::texturePath = "Ressources/Sprites/Bonus/RayonLaser_16x16.png";
sf::Texture ArmeLaserPercant::texture = sf::Texture();
const sf::Time ArmeLaserPercant::delaiEntreLesTirsDeBase = sf::milliseconds(2500);
const int ArmeLaserPercant::munition = 5;
const std::string ArmeLaserPercant::nomArme = "Destroyer?";
bool ArmeLaserPercant::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}
StructuresDonnees::list<Projectile*>* ArmeLaserPercant::Tire(Personnage* tireur, TypeWeapon type, float angle)
{
	StructuresDonnees::list<Projectile*>* projectiles = new StructuresDonnees::list<Projectile*>;
	projectiles->push_back(new ProjectileLaserPercant(type, tireur, angle, charge));
	--Arme::munition;
	return projectiles;
}

std::string ArmeLaserPercant::GetNomArme() const
{
	return nomArme;
}

ArmeLaserPercant::ArmeLaserPercant(Vector2f pos) : Arme(texture, delaiEntreLesTirsDeBase, munition, ArmeSpecialeRayonLaser, pos)
{
	typeArme = Other;
}

ArmeLaserPercant::~ArmeLaserPercant()
{
}
