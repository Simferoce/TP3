#include "BombeElectrique.h"

sf::Texture BombeElectrique::textureActive = Texture();
const std::string BombeElectrique::texturePathActive = "Ressources/Sprites/Bonus/BombesElec_16x16.png";


BombeElectrique::BombeElectrique(Vector2f pos) :Bonus(textureActive, BonusType::BombeElectromagnetique, pos)
{
	setPosition(pos);
	setTexture(textureActive);
	setTextureRect(IntRect(0, 0, 16, 16));
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
}


BombeElectrique::~BombeElectrique()
{
}

bool BombeElectrique::initTexture()
{
	if (!textureActive.loadFromFile(texturePathActive))
		return false;
	return true;
}