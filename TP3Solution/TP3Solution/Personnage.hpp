#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "ProjectileType.h"
#include "../StructuresDonnees/list.hpp"
#include "Bonus.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Projectile.hpp"
#include "Arme.hpp"

class Personnage
	: public sf::Sprite
{
protected:
	enum Direction { Droite, Gauche, Haut, Bas, Aucun, NbreDirection };
	int pointsDeVie;
	Arme* armeEquipe;
	sf::Time dernierTir;
	sf::Clock clock;
	float vitesse;
	float modificateurVitesseRecul;
	ProjectileType projectiletype;
	StructuresDonnees::list<Bonus> bonus;
public:
	Personnage(sf::Texture& texture, int pointsDeVie, Arme* armeEquipe, float vitesse, float modificateurVitesseRecul, ProjectileType projectiletype)
		: pointsDeVie{pointsDeVie}, armeEquipe{armeEquipe}, vitesse{vitesse},modificateurVitesseRecul{modificateurVitesseRecul}
		, projectiletype{projectiletype}
	{
		setTexture(texture);
	}
	virtual ~Personnage()
	{
		delete armeEquipe;
	}
	bool CanFire() const
	{
		return clock.getElapsedTime().asMilliseconds() - armeEquipe->GetTempsEntreTir().asMilliseconds() > dernierTir.asMilliseconds();
	}
	bool IsDead() const
	{
		return pointsDeVie <= 0;
	}
	virtual StructuresDonnees::list<Projectile*>* Fire()
	{
		dernierTir = clock.getElapsedTime();
		return armeEquipe->Tire(getPosition(), ProjectileType::Player, 0);
	}	
	/// <summary>
	/// Moves the player..
	/// </summary>
	/// <param name="bitMask">The bit mask. WASD</param>
	/// <param name="bounds">World bounds</param>
	virtual void Move(int bitMask, sf::FloatRect bounds)
	{
		switch (bitMask)
		{
		//W
		case 1:
			move(0, -vitesse);
			break;
		//A
		case 2:
			move(-vitesse*modificateurVitesseRecul, 0);
			break;
		//WA
		case 3:
			move(-sqrt(pow(vitesse,2)/2)*modificateurVitesseRecul, -sqrt(pow(vitesse, 2) / 2));
			break;
		//S
		case 4:
			move(0, vitesse);
			break;
		//SA
		case 6:
			move(-sqrt(pow(vitesse, 2) / 2)*modificateurVitesseRecul, sqrt(pow(vitesse, 2) / 2));
			break;
		//D
		case 8:
			move(vitesse, 0);
			break;
		//WD
		case 9:
			move(sqrt(pow(vitesse, 2) / 2), -sqrt(pow(vitesse, 2) / 2));
			break;
		//SD
		case 12:
			move(sqrt(pow(vitesse, 2) / 2), sqrt(pow(vitesse, 2) / 2));
			break;
		default:
			break;
		}
		if (getPosition().y < bounds.top) 
			setPosition(getPosition().x, bounds.top);
		if (getPosition().y + getLocalBounds().height > bounds.top + bounds.height) 
			setPosition(getPosition().x, bounds.top + bounds.height - getLocalBounds().height);
		if (getPosition().x < bounds.left) 
			setPosition(bounds.left, getPosition().y);
		if (getPosition().x + getLocalBounds().width > bounds.left + bounds.width)
			setPosition(bounds.left + bounds.width - getLocalBounds().width, getPosition().y);
	}
};
