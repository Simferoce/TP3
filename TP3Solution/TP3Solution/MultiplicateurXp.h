#pragma once
#include "Bonus.h"
class MultiplicateurXp :
	public Bonus
{
	static sf::Texture textureActive;
	static const std::string texturePathActive;
public:
	MultiplicateurXp(Vector2f pos);
	~MultiplicateurXp();
	static bool initTexture();
};

