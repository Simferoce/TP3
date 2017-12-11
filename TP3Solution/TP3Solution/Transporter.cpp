#include "Transporter.h"
#include "Joueur.h"
#include "ProjectileBase.h"
#include "INiveau.h"
#include "Personnage.hpp"
#include "EnemySentinelle.h"

const std::string Transporter::texturePath = "Ressources/Sprites/Enemy/Regulier/Transporteur/Transporteur_32x16.png";
sf::Texture Transporter::texture = sf::Texture();
const float Transporter::vitesseDeBase = 0.7f;
const int Transporter::pointsVieDeBase = 1;
const float Transporter::modificateurVitesseReculDebase = 0.0f;
const sf::IntRect Transporter::textureRectBase[nbreAnimation] = { sf::IntRect(0,0,16,16), sf::IntRect(16,0,16,16),
sf::IntRect(32,0,32,16), sf::IntRect(48,0,16,16), sf::IntRect(64,0,16,16), sf::IntRect(80,0,16,16), sf::IntRect(96,0,16,16), sf::IntRect(112,0,16,16) };
const sf::Time Transporter::tempAnimation = sf::milliseconds(300);
const sf::Time Transporter::tempsEntreEnemies = sf::milliseconds(3000);
const int Transporter::animationDeBase = 0;

TypeWeapon Transporter::genererTypeArmeEnemy()
{
	int typeArme = rand() % 2;
	return (TypeWeapon)typeArme;
}

Transporter::Transporter() : Enemy(texture, textureRectBase[animationDeBase], pointsVieDeBase, nullptr, vitesseDeBase, modificateurVitesseReculDebase, genererTypeArmeEnemy())
{
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
}


Transporter::~Transporter()
{
}

Enemy::ElementToModify Transporter::update(INiveau& game)
{
	Move(sensDeplacementHautBas, game.GetBounds());
	if (sensDeplacementHautBas == Bas)
	{
		distanceDeplacementHautBasParcourue += vitesse;
		if (distanceDeplacementHautBasParcourue > distanceDeplacementHautBas)
		{
			sensDeplacementHautBas = Haut;
			Move(sensDeplacementHautBas, distanceDeplacementHautBasParcourue - distanceDeplacementHautBas, game.GetBounds());
		}
	}
	else if (sensDeplacementHautBas == Haut)
	{
		distanceDeplacementHautBasParcourue -= vitesse;
		if (distanceDeplacementHautBasParcourue < -1 * distanceDeplacementHautBas)
		{
			sensDeplacementHautBas = Bas;
			Move(sensDeplacementHautBas, distanceDeplacementHautBasParcourue - -1 * distanceDeplacementHautBas, game.GetBounds());
		}
	}
	bool spawnEnemy = enemiesSpawnClock.getElapsedTime() - tempsDernierSpawnEnemies > tempsEntreEnemies;
	ElementToModify elementToAdd(false);
	if(spawnEnemy)
	{
		elementToAdd.hasElementToModify = true;
		elementToAdd.enemiesToAdd.push_back(FabriqueEnemy());
		tempsDernierSpawnEnemies = enemiesSpawnClock.getElapsedTime();
	}
	return elementToAdd;
}

Enemy * Transporter::FabriqueEnemy()
{
	EnemySentinelle* enemy = new EnemySentinelle();
	enemy->SetType(type);
	enemy->setPosition(getPosition());
	Direction directionEnemy = sensDeplacementHautBas == Haut ? Bas : Haut;
	enemy->SetDirection(directionEnemy);
	return enemy;
}



bool Transporter::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}