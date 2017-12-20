#pragma once
#include "Bonus.h"
class BombeElectrique :
	public Bonus
{
	static sf::Texture textureActive;
	static const std::string texturePathActive;
public:
	BombeElectrique(Vector2f pos);
	~BombeElectrique();
	static bool initTexture();
};

