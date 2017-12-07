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
	static const int orbitationDistance = 50;
	static const int orbitationDistnaceMinimal = 30;
	int animateur = 0;
	int animationSens = 1;
	sf::Vector2f direction = sf::Vector2f(-vitesseDeBase, 0);
public:
	Assistant();
	virtual ~Assistant();
	Personnage::ElementToModify Update(INiveau& game) override;
	virtual void Move(const Vector2f vectorDistance, const sf::FloatRect bounds);
	virtual void MoveAround(Vector2f pos);
	static Enemy* TrouverLePlusProche(Vector2f pos, StructuresDonnees::list<Enemy*>& enemies);
	static bool initTexture();
};

