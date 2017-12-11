#include "EnemySentinelle.h"
#include "Joueur.h"
#include "ProjectileBase.h"
#include "INiveau.h"
#include "Personnage.hpp"

const std::string EnemySentinelle::texturePath = "Ressources\\Sprites\\Enemy\\Regulier\\Sentinelle\\sentinelle_16x16.png";
sf::Texture EnemySentinelle::texture = sf::Texture();
const float EnemySentinelle::vitesseDeBase = 2.0f;
const int EnemySentinelle::pointsVieDeBase = 1;
const float EnemySentinelle::modificateurVitesseReculDebase = 0.0f;
const sf::IntRect EnemySentinelle::textureRectBase[nbreAnimation] = { sf::IntRect(0,0,16,16), sf::IntRect(16,0,16,16),
sf::IntRect(32,0,16,16), sf::IntRect(48,0,16,16), sf::IntRect(64,0,16,16), sf::IntRect(80,0,16,16), sf::IntRect(96,0,16,16), sf::IntRect(112,0,16,16) };
const int EnemySentinelle::tempAnimation = 100;
const int EnemySentinelle::animationDeBase = 0;
const float EnemySentinelle::proportionVitesseHautBas = 0.7f;
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

Enemy::ElementToModify EnemySentinelle::update(INiveau& game)
{
	ElementToModify elementToModify(false);
	Move(sensDeplacementHautBas, vitesse*proportionVitesseHautBas);
	if (getPosition().x < getOrigin().x)
	{
		elementToModify.deleteObjectReturning = true;
		elementToModify.hasElementToModify = true;
	}
	else
		RepositionnerDansLimite(game.GetBounds());
	Move(Direction::Gauche, vitesse*(1 - proportionVitesseHautBas));
	if (sensDeplacementHautBas == Bas)
	{
		distanceDeplacementHautBasParcourue += vitesse*proportionVitesseHautBas;
		if(distanceDeplacementHautBasParcourue > distanceDeplacementHautBas)
		{
			sensDeplacementHautBas = Haut;
			Move(sensDeplacementHautBas, distanceDeplacementHautBasParcourue - distanceDeplacementHautBas, game.GetBounds());
		}
	}
	else if (sensDeplacementHautBas == Haut)
	{
		distanceDeplacementHautBasParcourue -= vitesse*proportionVitesseHautBas;
		if (distanceDeplacementHautBasParcourue < -1*distanceDeplacementHautBas)
		{
			sensDeplacementHautBas = Bas;
			Move(sensDeplacementHautBas, distanceDeplacementHautBasParcourue - -1*distanceDeplacementHautBas, game.GetBounds());
		}
	}
	bool fire = CanFire();
	if (fire)
	{
		elementToModify.hasElementToModify = true;
		StructuresDonnees::list<Projectile*>* temp = armeEquipe->Tire(this, type, 180);
		elementToModify.projectilesToAdd.splice(*temp, elementToModify.projectilesToAdd.begin());
		dernierTir = clock.getElapsedTime();
		delete temp;
	}
	animateur++;
	if (animationSens > 0 && animateur > nbreAnimation*tempAnimation)
		animationSens = -1;
	else if (animationSens < 0 && abs(animateur) > nbreAnimation*tempAnimation)
		animationSens = 1;
	setTextureRect(textureRectBase[(animateur / tempAnimation) % nbreAnimation]);
	return elementToModify;
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







