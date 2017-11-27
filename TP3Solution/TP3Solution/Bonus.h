#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
class Bonus
	: public sf::Sprite
{
public:
	bool isPickedUp = false;
	bool isDestroyed = false;
	bool isActive = true;
	Bonus(sf::Texture& texture )
	{
		setTexture(texture);
	}
};
