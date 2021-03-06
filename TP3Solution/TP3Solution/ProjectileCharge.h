#pragma once
#include "Projectile.h"
class ProjectileCharge :
	public Projectile
{
	static const std::string texturePath;
	static const int dommageDeBase;
	static const float vitesseDeBase;
	static sf::Texture texture;
	static const double dommagePerCharge;
	int charge = 0.0f;
public:
	static bool initTexture();
	ProjectileCharge(TypeWeapon type, Personnage* tireur, float angle, int charge, float scale);
	~ProjectileCharge();
	virtual int GetDommage() override;
};
