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
	static const int chargeMinimal = 20;
	static const std::string nomArme;
public:
	static bool initTexture();
	StructuresDonnees::list<Projectile*>* Tire(Personnage* tireur, TypeWeapon type, float angle) override;
	void ChargerArme() override;
	std::string GetNomArme() const override;
	ArmeChargee(Vector2f pos);
	~ArmeChargee();
};

