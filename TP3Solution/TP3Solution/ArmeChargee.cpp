#include "ArmeChargee.h"
#include "ProjectileBase.h"
#include "ProjectileCharge.h"

const std::string ArmeChargee::texturePath = "Gem.png";
sf::Texture ArmeChargee::texture = sf::Texture();
const sf::Time ArmeChargee::delaiEntreLesTirsDeBase = sf::milliseconds(100);
const int ArmeChargee::munition = 2000;

bool ArmeChargee::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}
StructuresDonnees::list<Projectile*>* ArmeChargee::Tire(sf::Vector2f origineDuTir, TypeWeapon type, float angle)
{
	StructuresDonnees::list<Projectile*>* projectiles = new StructuresDonnees::list<Projectile*>;
	projectiles->push_back(new ProjectileCharge(type, origineDuTir, angle,charge, (float)charge/chargeMax > 0.3f ? (float)charge/chargeMax : 0.3f));
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

ArmeChargee::ArmeChargee() : Arme(texture, delaiEntreLesTirsDeBase, munition)
{
	typeArme = Charger;
}

ArmeChargee::~ArmeChargee()
{
}
