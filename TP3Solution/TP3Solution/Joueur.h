#pragma once
#include "Personnage.h"
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
	Arme* armeDefaut = new ArmeBase();
public:
	static bool initTexture();
	Joueur();
	~Joueur();
};

