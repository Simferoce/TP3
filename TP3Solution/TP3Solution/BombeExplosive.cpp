#include "BombeExplosive.h"

sf::Texture BombeExplosive::textureActive = Texture();
const std::string BombeExplosive::texturePathActive = "Ressources/Sprites/Bonus/BombeExp_16x16.png";



BombeExplosive::BombeExplosive(Vector2f pos) : Bonus(textureActive, BonusType::BombeExplosive, pos)
{
		setPosition(pos);
		setTexture(textureActive);
		setTextureRect(IntRect(0, 0, 16, 16));
		setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
}


BombeExplosive::~BombeExplosive()
{
}

bool BombeExplosive::initTexture()
{
	if (!textureActive.loadFromFile(texturePathActive))
		return false;
	return true;
}


