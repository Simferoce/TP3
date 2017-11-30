#pragma once
#include "Projectile.hpp"
#include <string>

class ProjectileBase :
	public Projectile
{
	static const std::string texturePath;
	static const float vitesseDeBase;
	static sf::Texture texture;
public:
	static bool initTexture();
	ProjectileBase(ProjectileType type, sf::Vector2f pos, float angle);
	~ProjectileBase();
};

