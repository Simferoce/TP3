#pragma once
#include "Projectile.h"
class ProjectileLaserPercant :
	public Projectile
{
	static const std::string texturePath;
	static const int dommageDeBase;
	static const float vitesseDeBase;
	static sf::Texture texture;
	static const double dommagePerCharge;
	static const sf::Time duree;
	int charge = 0.0f;
	sf::Time naissance;
	sf::Clock clock;
public:
	static bool initTexture();
	ProjectileLaserPercant(TypeWeapon type, Personnage* tireur, float angle, int charge);
	bool EstPasserDate();
	~ProjectileLaserPercant();
	void Update() override;
	virtual int GetDommage() override;
};


