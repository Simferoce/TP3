#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "TypeWeapon.h"
#include "../StructuresDonnees/list.hpp"
#include "Bonus.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Projectile.hpp"
#include "Arme.hpp"
#include "../StructuresDonnees/stack.hpp"
#include "Bouclier.hpp"
#include "ArmeBase.h"
#include <algorithm>
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
	TypeWeapon projectiletype;
	StructuresDonnees::list<Bonus> bonus;
	StructuresDonnees::list<Arme*> armes;
	StructuresDonnees::stack<Bouclier*> boucliers;
public:
	Personnage(sf::Texture& texture, const sf::IntRect& rectTexture, int pointsDeVie, Arme* armeEquipe, float vitesse, float modificateurVitesseRecul, TypeWeapon projectiletype)
		: pointsDeVie{pointsDeVie}, armeEquipe{armeEquipe}, vitesse{vitesse},modificateurVitesseRecul{modificateurVitesseRecul}
		, projectiletype{projectiletype}
	{
		setTexture(texture);
		setTextureRect(rectTexture);
		setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
		armes.push_back(armeEquipe);
	}
	virtual ~Personnage()
	{
		for (Arme* arme : armes)
		{
			delete arme;
		}
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
		return armeEquipe->Tire(getPosition(), projectiletype, 0);
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
		if (getPosition().y < bounds.top + getGlobalBounds().height / 2)
			setPosition(getPosition().x, bounds.top + getGlobalBounds().height / 2);
		if (getPosition().y + getLocalBounds().height/2 > bounds.top + bounds.height) 
			setPosition(getPosition().x, bounds.top + bounds.height - getLocalBounds().height/2);
		if (getPosition().x < bounds.left + getGlobalBounds().width/2) 
			setPosition(bounds.left + getGlobalBounds().width / 2, getPosition().y);
		if (getPosition().x + getLocalBounds().width/2 > bounds.left + bounds.width)
			setPosition(bounds.left + bounds.width - getLocalBounds().width/2, getPosition().y);
	}
	virtual void RecoitDommage(TypeWeapon type, int dommage)
	{
		if(boucliers.top()->GetTypeBouclier() == type)
		{
			int dommageRestant = dommage;
			while(pointsDeVie > 0 && dommageRestant > 0)
			{
				if(!boucliers.is_empty())
				{
					dommageRestant = boucliers.top()->RecoitDommage(type, dommage);
					if (boucliers.top()->Detruit())
						boucliers.pop();
				}
				else
				{
					pointsDeVie -= dommageRestant;
					dommageRestant = 0;
				}
			}
		}
		else
		{
			pointsDeVie -= dommage;
		}
	}
	void nextWeapon()
	{
		auto iter = std::find(armes.begin(), armes.end(), armeEquipe);
		if (iter != armes.end() && ++iter != armes.end())
			armeEquipe = *iter;
	}
	void previousWeapon()
	{
		auto iter = std::find(armes.rbegin(), armes.rend(), armeEquipe);
		if (iter != armes.end() && ++iter != armes.end())
			armeEquipe = *iter;
	}
};
