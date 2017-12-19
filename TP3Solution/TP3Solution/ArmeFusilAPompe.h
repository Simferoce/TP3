#pragma once
#include "Arme.hpp"
class ArmeFusilAPompe :
	public Arme
{
	static sf::Texture texture; // La texture de l'arme de base
	static const std::string texturePath; // L'emplacement de la texture de base
	static const int munition; // Le nombre de munition de l'arme de base soit infini
	static const sf::Time delaiEntreLesTirsDeBase; // Delais entre chaque tir avec l'arme de base
	static const std::string nomArme;
	static const int angleSpread = 10;
public:
	static bool initTexture();
	StructuresDonnees::list<Projectile*>* Tire(Personnage* tireur, TypeWeapon type, float angle) override;
	std::string GetNomArme() const override;
	ArmeFusilAPompe(Vector2f pos);
	~ArmeFusilAPompe();
};

