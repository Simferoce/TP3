#pragma once
#include "Arme.hpp"
class ArmeChargee :
	public Arme
{
	static sf::Texture texture;
	static const std::string texturePath;
	static const int munition;
	static const sf::Time delaiEntreLesTirsDeBase;
	static const int chargeMax = 100;
public:
	static bool initTexture();
	StructuresDonnees::list<Projectile*>* Tire(sf::Vector2f origineDuTir, TypeWeapon type, float angle) override;
	void ChargerArme() override;
	ArmeChargee();
	~ArmeChargee();
};

