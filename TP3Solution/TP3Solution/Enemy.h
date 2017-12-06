#pragma once
#include "Personnage.hpp"
#include "IObservateur.h"
#include "ArmeBase.h"
class INiveau;
class Enemy :
	public Personnage, public IObservateur
{
public:
	virtual void Move(int bitMask, sf::FloatRect bounds);
	Enemy(sf::Texture& texture, const sf::IntRect& rectTexture, int pointsDeVie, Arme* armeEquipe, float vitesse, float modificateurVitesseRecul, TypeWeapon projectiletype);
	~Enemy();
	void notifier(Sujet* sujet) override;
	virtual Personnage::ElementToModify Collisionner(const Personnage& other) override;
	virtual ElementToModify Update(INiveau& game) = 0;
};

