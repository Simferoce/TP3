#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include "Enemy.h"


class Spawner
	: public sf::Sprite
{	
	static sf::Texture texture;
	static const std::string texturePath;
public:
	enum EnemiesEnum
	{
		SentinelleEnum,
		KamikazeEnum,
		TransporteurEnum,
		NumEnemies
	};
	static bool initTexture();
	Spawner(sf::Vector2f pos);
	Spawner();
	Enemy* FabriquerEnemy(EnemiesEnum enemy) const;
};
