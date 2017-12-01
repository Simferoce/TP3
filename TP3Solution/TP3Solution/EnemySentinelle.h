#pragma once
#include "Enemy.h"

class EnemySentinelle :
	public Enemy
{
	static sf::Texture texture;
	static const std::string texturePath;
	static const int pointsVieDeBase;
	static const float vitesseDeBase;
	static const float modificateurVitesseReculDebase;
	static const int nbreAnimation = 8;
	static const sf::IntRect textureRectBase[nbreAnimation];
	static const int animationDeBase;
	int animateur = animationDeBase;
	sf::Clock animationHorloge = sf::Clock();
	static const sf::Time tempAnimation;
	static Arme* GetArmeDefaut()
	{
		return new ArmeBase();
	}
	static TypeWeapon genererTypeArmeEnemy();
public:
	static bool initTexture();
	EnemySentinelle();
	~EnemySentinelle();
	virtual void Update(const SceneNiveau& game) override;
};

