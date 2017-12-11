#pragma once
#include "Enemy.h"
class Kamikaze :
	public Enemy
{
	static sf::Texture texture;
	static const std::string texturePath;
	static const int pointsVieDeBase;
	static const float vitesseDeBase;
	static const float modificateurVitesseReculDebase;
	static const int distanceDeplacementHautBas = 100;
	static const int nbreAnimation = 8;
	static const sf::IntRect textureRectBase[nbreAnimation];
	static const int animationDeBase;
	static const int tempAnimation;
	static TypeWeapon genererTypeArmeEnemy();
	int animateur = 0;
	int animationSens = 1;
	Vector2f direction = Vector2f(-vitesseDeBase,0);
protected:
	Personnage::ElementToModify update(INiveau& game) override;
public:
	static bool initTexture();
	Kamikaze();
	~Kamikaze();
	virtual void Move(Direction direction, float distance, sf::FloatRect bounds) override { Personnage::Move(direction, distance, bounds); };
	virtual void Move(int bitMasks, sf::FloatRect bounds) override { Personnage::Move(bitMasks, bounds); };
	virtual void Move(Direction direction, sf::FloatRect bounds) override { Personnage::Move(direction, bounds); };
	virtual void Move(const Vector2f vectorDistance, const sf::FloatRect bounds);
	virtual Personnage::ElementToModify Collisionner(const Personnage& other) override;
};

