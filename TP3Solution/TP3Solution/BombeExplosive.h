#pragma once
#include "Bonus.h"
class BombeExplosive :
	public Bonus
{
	static sf::Texture textureActive;
	static const std::string texturePathActive;
public:
	BombeExplosive(Vector2f pos);
	~BombeExplosive();
	static bool initTexture();
};

