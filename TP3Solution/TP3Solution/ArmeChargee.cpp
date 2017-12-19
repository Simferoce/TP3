#include "ArmeChargee.h"
#include "ProjectileBase.h"
#include "ProjectileCharge.h"
#include "Personnage.hpp"
const std::string ArmeChargee::texturePath = "Ressources/Sprites/Bonus/HyperBullet_16x16.png";
sf::Texture ArmeChargee::texture = sf::Texture();
const sf::Time ArmeChargee::delaiEntreLesTirsDeBase = sf::milliseconds(100);
const int ArmeChargee::munition = 2000;
const std::string ArmeChargee::nomArme = "Master Laser";
bool ArmeChargee::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}
StructuresDonnees::list<Projectile*>* ArmeChargee::Tire(Personnage* tireur, TypeWeapon type, float angle)
{
	StructuresDonnees::list<Projectile*>* projectiles = new StructuresDonnees::list<Projectile*>;
	if(charge < chargeMinimal)
	{
		Arme::munition -= chargeMinimal - charge;
		if (Arme::munition < 0)
			Arme::munition = 0;
		charge = chargeMinimal;
	}
	projectiles->push_back(new ProjectileCharge(type, tireur, angle,charge, (float)charge/chargeMax > 0.3f ? (float)charge/chargeMax : 0.3f));
	charge = 0;
	return projectiles;
}

void ArmeChargee::ChargerArme()
{
	if (charge < chargeMax && Arme::munition > 0)
	{
		charge++;
		--Arme::munition;
	}
}

std::string ArmeChargee::GetNomArme() const
{
	return nomArme;
}

ArmeChargee::ArmeChargee(Vector2f pos) : Arme(texture, delaiEntreLesTirsDeBase, munition, ArmeSpecialeSurpuissante ,pos)
{
	typeArme = Charger;
}

ArmeChargee::~ArmeChargee()
{
}
