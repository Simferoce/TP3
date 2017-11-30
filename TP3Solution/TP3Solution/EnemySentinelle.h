#pragma once
#include "Enemy.h"
class EnemySentinelle :
	public Enemy
{
	static sf::Texture texture; // Texture de l'ennemi
	static const std::string texturePath; // Texture de l'ennemi
	static const int pointsVieDeBase;
	static const float vitesseDeBase;
	static const float modificateurVitesseReculDebase;
	static const TypeWeapon projectileTypeDeBase;
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
public:
	static bool initTexture();
	EnemySentinelle();
	~EnemySentinelle();
	void virtual Move(int bitMask, sf::FloatRect bounds) override;
};

