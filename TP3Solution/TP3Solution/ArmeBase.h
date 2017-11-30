#pragma once
#include "Arme.hpp"
#include <string>
#include <SFML/System/Time.hpp>

class ArmeBase :
	public Arme
{
	static sf::Texture texture;
	static const std::string texturePath;
	static const sf::Time delaiEntreLesTirsDeBase;
public:
	static bool initTexture();
	StructuresDonnees::list<Projectile*>* Tire(sf::Vector2f origineDuTir, ProjectileType type, float angle) override;
	Arme* clone() const override;
	ArmeBase();
	~ArmeBase();
};

