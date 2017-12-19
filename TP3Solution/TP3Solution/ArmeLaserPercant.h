#pragma once
#include "Arme.hpp"
class ArmeLaserPercant :
	public Arme
{
	static sf::Texture texture;
	static const std::string texturePath;
	static const int munition;
	static const sf::Time delaiEntreLesTirsDeBase;
	static const std::string nomArme;
public:
	static bool initTexture();
	StructuresDonnees::list<Projectile*>* Tire(Personnage* tireur, TypeWeapon type, float angle) override;
	std::string GetNomArme() const override;
	ArmeLaserPercant(Vector2f pos);
	~ArmeLaserPercant();
};

