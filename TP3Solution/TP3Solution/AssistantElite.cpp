#include "AssistantElite.h"

const std::string AssistantElite::texturePath = "Ressources\\Sprites\\Enemy\\Regulier\\AssistantAvance\\AssistantAvance_16x16.png";
sf::Texture AssistantElite::texture = sf::Texture();
const float AssistantElite::vitesseDeBase = 1.5f;
const int AssistantElite::pointsVieDeBase = 2;

AssistantElite::AssistantElite() : Assistant(texture, pointsVieDeBase, GetArmeDefaut(), vitesseDeBase)
{
}


AssistantElite::~AssistantElite()
{
}

bool AssistantElite::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}

Personnage::ElementToModify AssistantElite::update(INiveau & game)
{
	Personnage::ElementToModify elemToModify = Assistant::update(game);
	bool fire = CanFire();
	if (fire)
	{
		elemToModify.hasElementToModify = true;
		StructuresDonnees::list<Projectile*>* temp = armeEquipe->Tire(this, type, 180);
		elemToModify.projectilesToAdd.splice(*temp, elemToModify.projectilesToAdd.begin());
		dernierTir = clock.getElapsedTime();
		delete temp;
	}
	return elemToModify;
}
