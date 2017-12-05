#include "EnemySentinelle.h"
#include "Joueur.h"
#include "ProjectileBase.h"
#include "INiveau.h"
#include "Personnage.hpp"

const std::string EnemySentinelle::texturePath = "Ressources\\Sprites\\Enemy\\Regulier\\Sentinelle\\sentinelle_16x16.png";
sf::Texture EnemySentinelle::texture = sf::Texture();
const float EnemySentinelle::vitesseDeBase = 1.0f;
const int EnemySentinelle::pointsVieDeBase = 1;
const float EnemySentinelle::modificateurVitesseReculDebase = 0.0f;
const sf::IntRect EnemySentinelle::textureRectBase[nbreAnimation] = { sf::IntRect(0,0,16,16), sf::IntRect(16,0,16,16),
sf::IntRect(32,0,16,16), sf::IntRect(48,0,16,16), sf::IntRect(64,0,16,16), sf::IntRect(80,0,16,16), sf::IntRect(96,0,16,16), sf::IntRect(112,0,16,16) };
const int EnemySentinelle::tempAnimation = 100;
const int EnemySentinelle::animationDeBase = 0;

TypeWeapon EnemySentinelle::genererTypeArmeEnemy()
{
	int typeArme = rand() % 3 + 0;
	return (TypeWeapon)typeArme;
}

EnemySentinelle::EnemySentinelle() : Enemy(texture, textureRectBase[animationDeBase], pointsVieDeBase, GetArmeDefaut(), vitesseDeBase, modificateurVitesseReculDebase, genererTypeArmeEnemy())
{
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
}


EnemySentinelle::~EnemySentinelle()
{
}

Enemy::ElementToAdd EnemySentinelle::Update(const INiveau& game)
{
	Move(sensDeplacementHautBas, game.GetBounds());
	if (sensDeplacementHautBas == Bas)
	{
		distanceDeplacementHautBasParcourue += vitesse;
		if(distanceDeplacementHautBasParcourue > distanceDeplacementHautBas)
		{
			sensDeplacementHautBas = Haut;
			Move(sensDeplacementHautBas, distanceDeplacementHautBasParcourue - distanceDeplacementHautBas, game.GetBounds());
		}
	}
	else if (sensDeplacementHautBas == Haut)
	{
		distanceDeplacementHautBasParcourue -= vitesse;
		if (distanceDeplacementHautBasParcourue < -1*distanceDeplacementHautBas)
		{
			sensDeplacementHautBas = Bas;
			Move(sensDeplacementHautBas, distanceDeplacementHautBasParcourue - -1*distanceDeplacementHautBas, game.GetBounds());
		}
	}
	bool fire = CanFire();
	ElementToAdd elementToAdd(fire);
	if (fire)
	{
		StructuresDonnees::list<Projectile*>* temp = armeEquipe->Tire(getPosition(), type, 180);
		elementToAdd.projectiles.splice(*temp, elementToAdd.projectiles.begin());
		dernierTir = clock.getElapsedTime();
		delete temp;
	}
	animateur++;
	if (animationSens > 0 && animateur > nbreAnimation*tempAnimation)
		animationSens = -1;
	else if (animationSens < 0 && abs(animateur) > nbreAnimation*tempAnimation)
		animationSens = 1;
	setTextureRect(textureRectBase[(animateur / tempAnimation) % nbreAnimation]);
	return elementToAdd;
}

void EnemySentinelle::SetDirection(Direction direction)
{
	sensDeplacementHautBas = direction;
}



bool EnemySentinelle::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}







