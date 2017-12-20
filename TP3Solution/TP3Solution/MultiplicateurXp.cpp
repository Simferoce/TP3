#include "MultiplicateurXp.h"

sf::Texture MultiplicateurXp::textureActive = Texture();
const std::string MultiplicateurXp::texturePathActive = "Ressources/Sprites/Bonus/Multiplicateur_16x16.png";

MultiplicateurXp::MultiplicateurXp(Vector2f pos) : Bonus(textureActive, BonusType::MultiplicateurDePoints, pos)
{
	setPosition(pos);
	setTexture(textureActive);
	setTextureRect(IntRect(0, 0, 16, 16));
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
}


MultiplicateurXp::~MultiplicateurXp()
{
}

bool MultiplicateurXp::initTexture()
{
	if (!textureActive.loadFromFile(texturePathActive))
		return false;
	return true;
}

