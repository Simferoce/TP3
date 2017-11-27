#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "ProjectileType.h"
#include "../StructuresDonnees/list.hpp"
#include "Bonus.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Projectile.h"
#include "Arme.h"

class Personnage
	: public sf::Sprite
{
protected:
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

	}
	bool CanFire() const
	{
		return clock.getElapsedTime().asMilliseconds() - armeEquipe->GetTempsEntreTir().asMilliseconds() > dernierTir.asMilliseconds();
	}
	bool IsDead() const
	{
		return pointsDeVie <= 0;
	}
	virtual StructuresDonnees::list<Projectile*> Fire()
	{
		return armeEquipe->Tire();
	}
};
