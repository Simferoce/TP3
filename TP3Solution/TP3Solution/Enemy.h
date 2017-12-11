#pragma once
#include "Personnage.hpp"
#include "IObservateur.h"
#include "ArmeBase.h"
#include "Composite.h"
class INiveau;
class Enemy :
	public Personnage, public IObservateur, public Composite
{
protected:
	virtual ElementToModify update(INiveau& game) = 0;
public:
	virtual void Move(int bitMask, sf::FloatRect bounds);
	Enemy(sf::Texture& texture, const sf::IntRect& rectTexture, int pointsDeVie, Arme* armeEquipe, float vitesse, float modificateurVitesseRecul, TypeWeapon projectiletype);
	~Enemy();
	void notifier(Sujet* sujet) override;
	virtual Personnage::ElementToModify Collisionner(const Personnage& other) override;
	ElementToModify Update(INiveau& game);
	virtual void Draw(RenderWindow& window) override;
};

