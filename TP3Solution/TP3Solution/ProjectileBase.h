#pragma once
#include "Projectile.h"
#include <string>

class ProjectileBase :
	public Projectile
{
	static const std::string texturePath;
	static const int dommageDeBase;
	static const float vitesseDeBase;
	static sf::Texture texture;
public:
	static bool initTexture();
	ProjectileBase(TypeWeapon type, Personnage* tireur, float angle);
	~ProjectileBase();
};

