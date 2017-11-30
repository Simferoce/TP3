#pragma once
#include "Personnage.hpp"
#include <string>
#include "ArmeBase.h"

class Joueur :
	public Personnage
{
	static sf::Texture texture;
	static const std::string texturePath;
	static const int pointsVieDeBase;
	static const float vitesseDeBase;
	static const float modificateurVitesseReculDebase;
	static const ProjectileType projectileTypeDeBase;
	static Arme* GetArmeDefaut()
	{
		return new ArmeBase();
	}
public:
	static bool initTexture();
	Joueur();
	~Joueur();
};

