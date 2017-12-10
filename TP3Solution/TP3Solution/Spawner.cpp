#include "Spawner.h"
#include "EnemySentinelle.h"
#include "Kamikaze.h"
#include "Transporter.h"
#include "Assistant.h"
#include "AssistantElite.h"
const std::string Spawner::texturePath = "";
Texture Spawner::texture = Texture();
bool Spawner::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}
Spawner::Spawner(sf::Vector2f pos)
{
	setPosition(pos);
}

Spawner::Spawner()
{
}

Enemy * Spawner::FabriquerEnemy(EnemiesEnum enemy) const
{
	Enemy* temp = nullptr;
	switch (enemy)
	{
	case SentinelleEnum:
		temp = new EnemySentinelle();
		temp->setPosition(getPosition());
		break;
	case KamikazeEnum:
		temp = new Kamikaze();
		temp->setPosition(getPosition());
		break;
	case TransporteurEnum:
		temp = new Transporter();
		temp->setPosition(getPosition());
		break;
	case AssistantEnum:
		temp = new Assistant();
		temp->setPosition(getPosition());
		break;
	case AssistantEliteEnum:
		temp = new AssistantElite();
		temp->setPosition(getPosition());
		break;
	default:
		break;
	}
	return temp;
}
