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
	static Arme* GetArmeDefaut()
	{
		Arme* arme = new ArmeBase(Vector2f(0, 0));
		arme->SetTempsEntreTir(sf::milliseconds(1000));
		return arme;
	}
	static TypeWeapon genererTypeArmeEnemy();
	static const int tempAnimation;
	int animateur = 0;
	int animationSens = 1;
	float distanceDeplacementHautBasParcourue = 0.0f;
	static const float proportionVitesseHautBas;
	Direction sensDeplacementHautBas = Haut;
protected:
	Personnage::ElementToModify update(INiveau& game) override;
public:
	void SetDirection(Direction direction);
	static bool initTexture();
	EnemySentinelle();
	~EnemySentinelle();
	virtual void Move(Direction direction, float distance, sf::FloatRect bounds) override { Personnage::Move(direction, distance, bounds); };
	virtual void Move(int bitMasks, sf::FloatRect bounds) override { Personnage::Move(bitMasks, bounds); };
	virtual void Move(Direction direction, sf::FloatRect bounds) override { Personnage::Move(direction, bounds); };
	virtual void Move(Direction direction) override { Personnage::Move(direction); }
	virtual void Move(Direction direction, float distance) override { Personnage::Move(direction, distance); }

};

