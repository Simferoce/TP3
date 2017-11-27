#pragma once
#include "Arme.h"
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
	StructuresDonnees::list<Projectile*> Tire() override;
	ArmeBase();
	~ArmeBase();
};

