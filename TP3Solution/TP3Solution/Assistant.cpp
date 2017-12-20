#include "Assistant.h"
#include "INiveau.h"
#include <iostream>
#include "AssistantElite.h"
const std::string Assistant::texturePath = "Ressources\\Sprites\\Enemy\\Regulier\\AssistantBase\\AssistantBase_16x16.png";
sf::Texture Assistant::texture = sf::Texture();
const float Assistant::vitesseDeBase = 2.0f;
const int Assistant::pointsVieDeBase = 1;
const float Assistant::modificateurVitesseReculDebase = 0.0f;
const sf::IntRect Assistant::textureRectBase[nbreAnimation] = { sf::IntRect(0,0,16,16), sf::IntRect(16,0,16,16),
sf::IntRect(32,0,16,16), sf::IntRect(48,0,16,16), sf::IntRect(64,0,16,16), sf::IntRect(80,0,16,16), sf::IntRect(96,0,16,16), sf::IntRect(112,0,16,16) };
const int Assistant::animationDeBase = 0;
TypeWeapon Assistant::genererTypeArmeEnemy()
{
	int typeArme = rand() % 3 + 0;
	return (TypeWeapon)typeArme;
}

Enemy * Assistant::TrouverLePlusProche(Vector2f pos, StructuresDonnees::list<Enemy*>& enemies)
{
	float distanceEnemy = INT32_MAX;
	Enemy* nearestEnemy = nullptr;
	for(auto iter = enemies.begin(); iter != enemies.end(); ++iter)
	{
		int distance = sqrt(pow((*iter)->getPosition().x - pos.x, 2) + pow((*iter)->getPosition().y - pos.y, 2));
		if (typeid(*(*iter)) != typeid(Assistant) && typeid(*(*iter)) != typeid(AssistantElite) && distance < distanceEnemy)
		{
			nearestEnemy = (*iter);
			distanceEnemy = distance;
		}
	}
	return nearestEnemy;
}

Assistant::Assistant() : Enemy(texture, textureRectBase[animationDeBase], pointsVieDeBase, nullptr, vitesseDeBase, modificateurVitesseReculDebase, genererTypeArmeEnemy())
{
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
	valeurPoints = 2;
}

Assistant::Assistant(sf::Texture & texture, int pointsDeVie, Arme * armeEquipe, float vitesse)
	: Enemy(texture, textureRectBase[animationDeBase], pointsDeVie, armeEquipe, vitesse, modificateurVitesseRecul, genererTypeArmeEnemy())
{
}


Assistant::~Assistant()
{
}

Personnage::ElementToModify Assistant::update(INiveau& game)
{
	Personnage::ElementToModify elementToModify = Personnage::ElementToModify(false);
	if(assisteEnemy == nullptr)
	{
		Enemy* nearestEnemy = TrouverLePlusProche(getPosition(), game.GetAllEnemies());
		if (nearestEnemy != nullptr)
		{
			float variationX = nearestEnemy->getPosition().x - getPosition().x;
			float variationY = nearestEnemy->getPosition().y - getPosition().y;
			float distance = sqrtf(powf(variationX, 2) + powf(variationY, 2));
			if (distance < orbitationDistance && distance > orbitationDistnaceMinimal)
			{
				assisteEnemy = nearestEnemy;
				nearestEnemy->AjouterComposite(this);
				elementToModify.hasElementToModify = true;
				elementToModify.removeObject = true;
			}
			else if (distance > orbitationDistnaceMinimal)
			{
				this->direction = sf::Vector2f(variationX / distance, variationY / distance);
				Move(direction);
				RepositionnerDansLimite(game.GetBounds());
			}
		}
	}
	else
	{
		MoveAround(assisteEnemy->getPosition());
	}
	return elementToModify;
}
void Assistant::Move(const Vector2f vectorDirection)
{
	Move(vectorDirection, vitesse);
}
void Assistant::Move(const Vector2f vectorDistance, float vitesse)
{
	float newX = getPosition().x + vectorDistance.x*vitesse;
	float newY = getPosition().y + vectorDistance.y*vitesse;
	setPosition(newX, newY);
}
static double asdf = 0;
void Assistant::MoveAround(Vector2f pos)
{
	double variationX = (pos.x - getPosition().x)*-1;
	double variationY = (pos.y - getPosition().y)*-1;
	float distance = sqrtf(powf(variationX, 2) + powf(variationY, 2));
	double circonference = distance*3.1416;
	double angleCentre = vitesse * (2.0f * 3.1416) / circonference;
	double angleActuel = atan2(variationY, variationX);
	float angleResultant = angleCentre + angleActuel;
	Vector2f vectorDeAngleResultant = Vector2f(cosf(angleResultant), sinf(angleResultant));
	Vector2f newPos = vectorDeAngleResultant*distance + pos;
	setPosition(newPos);
}
bool Assistant::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}
