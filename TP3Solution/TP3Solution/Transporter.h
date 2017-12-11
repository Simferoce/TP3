#pragma once
#include "Enemy.h"
class Transporter :
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
	sf::Clock animationHorloge = sf::Clock();
	static const sf::Time tempAnimation;
	static TypeWeapon genererTypeArmeEnemy();
	static const sf::Time tempsEntreEnemies;
	sf::Clock enemiesSpawnClock;
	sf::Time tempsDernierSpawnEnemies = sf::milliseconds(0);
	int animateur = animationDeBase;
	float distanceDeplacementHautBasParcourue = 0.0f;
	Direction sensDeplacementHautBas = Haut;
protected:
	Personnage::ElementToModify update(INiveau& game) override;
public:
	static bool initTexture();
	Transporter();
	~Transporter();
	virtual void Move(Direction direction, float distance, sf::FloatRect bounds) override { Personnage::Move(direction, distance, bounds); };
	virtual void Move(int bitMasks, sf::FloatRect bounds) override { Personnage::Move(bitMasks, bounds); };
	virtual void Move(Direction direction, sf::FloatRect bounds) override { Personnage::Move(direction, bounds); };
	virtual Enemy* FabriqueEnemy();
};
