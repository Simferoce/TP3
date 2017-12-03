#pragma once
#include "Enemy.h"

class SceneNiveau;

class EnemySentinelle :
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
	static Arme* GetArmeDefaut()
	{
		Arme* arme = new ArmeBase();
		arme->SetTempsEntreTir(sf::milliseconds(1000));
		return arme;
	}
	static TypeWeapon genererTypeArmeEnemy();
	int animateur = animationDeBase;
	float distanceDeplacementHautBasParcourue = 0.0f;
	Direction sensDeplacementHautBas = Haut;
public:
	void SetDirection(Direction direction);
	static bool initTexture();
	EnemySentinelle();
	~EnemySentinelle();
	virtual ElementToAdd Update(const INiveau& game) override;
	virtual void Move(Direction direction, float distance, sf::FloatRect bounds) override { Personnage::Move(direction, distance, bounds); };
	virtual void Move(int bitMasks, sf::FloatRect bounds) override { Personnage::Move(bitMasks, bounds); };
	virtual void Move(Direction direction, sf::FloatRect bounds) override { Personnage::Move(direction, bounds); };

};

