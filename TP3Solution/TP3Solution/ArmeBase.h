#pragma once
#include "Arme.hpp"
#include <string>
#include <SFML/System/Time.hpp>

class ArmeBase :
	public Arme
{
	static sf::Texture texture;
	static const std::string texturePath;
	static const int munition;
	static const sf::Time delaiEntreLesTirsDeBase;
public:
	static bool initTexture();
	StructuresDonnees::list<Projectile*>* Tire(sf::Vector2f origineDuTir, TypeWeapon type, float angle) override;
	ArmeBase();
	~ArmeBase();
};

