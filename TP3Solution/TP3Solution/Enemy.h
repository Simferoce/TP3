#pragma once
#include "Personnage.hpp"
#include "IObservateur.h"
#include "ArmeBase.h"
class INiveau;
class Enemy :
	public Personnage, public IObservateur
{
public:
	struct ElementToAdd
	{
		bool hasElementToAdd = false;
		StructuresDonnees::list<Projectile*> projectiles;
		ElementToAdd(bool hasElementToAdd = false) : hasElementToAdd{hasElementToAdd} {};
		ElementToAdd& operator=(ElementToAdd& other)
		{
			projectiles.assign(other.projectiles.begin(), other.projectiles.end());
			hasElementToAdd = other.hasElementToAdd;  
			return *this;
		}
		ElementToAdd(ElementToAdd& other)
		{
			*this = other;
		};
	};
	virtual void Move(int bitMask, sf::FloatRect bounds);
	Enemy(sf::Texture& texture, const sf::IntRect& rectTexture, int pointsDeVie, Arme* armeEquipe, float vitesse, float modificateurVitesseRecul, TypeWeapon projectiletype);
	~Enemy();
	void notifier(Sujet* sujet) override;
	virtual ElementToAdd Update(const INiveau& game) = 0;
};

