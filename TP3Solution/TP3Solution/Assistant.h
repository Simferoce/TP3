#pragma once
#include "Enemy.h"
class INiveau;
class Assistant :
	public Enemy
{
	static sf::Texture texture;
	static const std::string texturePath;
	static const int pointsVieDeBase;
	static const float vitesseDeBase;
	static const int nbreAnimation = 8;
	static const sf::IntRect textureRectBase[nbreAnimation];
	static const float modificateurVitesseReculDebase;
	static const int animationDeBase;
	static TypeWeapon genererTypeArmeEnemy();
	static const int tempAnimation;
	static const int orbitationDistance = 70;
	static const int orbitationDistnaceMinimal = 50;
	int animateur = 0;
	int animationSens = 1;;
protected:
	Personnage::ElementToModify update(INiveau& game) override;
	sf::Vector2f direction = sf::Vector2f(-vitesseDeBase, 0);
	Enemy* assisteEnemy = nullptr;
public:
	Assistant();
	Assistant(sf::Texture& texture, int pointsDeVie, Arme* armeEquipe, float vitesse);
	virtual ~Assistant();
	virtual void Move(const Vector2f vectorDistance); 
	virtual void Move(const Vector2f vectorDistance, float vitesse);
	virtual void MoveAround(Vector2f pos);
	static Enemy* TrouverLePlusProche(Vector2f pos, StructuresDonnees::list<Enemy*>& enemies);
	static bool initTexture();
};

