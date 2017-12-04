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
#include <SFML/Graphics/RenderWindow.hpp>
#include "Projectile.hpp"
class Enemy;
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
	TypeWeapon type;
	StructuresDonnees::list<Bonus> bonus;
	StructuresDonnees::list<Arme*> armes;
	StructuresDonnees::stack<Bouclier*> boucliers;
	void RepositionnerDansLimite(FloatRect bounds)
	{
		if (getPosition().y < bounds.top + getGlobalBounds().height / 2)
			setPosition(getPosition().x, bounds.top + getGlobalBounds().height / 2);
		if (getPosition().y + getLocalBounds().height / 2 > bounds.top + bounds.height)
			setPosition(getPosition().x, bounds.top + bounds.height - getLocalBounds().height / 2);
		if (getPosition().x < bounds.left + getGlobalBounds().width / 2)
			setPosition(bounds.left + getGlobalBounds().width / 2, getPosition().y);
		if (getPosition().x + getLocalBounds().width / 2 > bounds.left + bounds.width)
			setPosition(bounds.left + bounds.width - getLocalBounds().width / 2, getPosition().y);
	}
public:
	struct ElementToAdd
	{
		bool hasElementToAdd = false;
		StructuresDonnees::list<Projectile*> projectiles;
		StructuresDonnees::list<Enemy*> enemies;
		ElementToAdd(bool hasElementToAdd) : hasElementToAdd{ hasElementToAdd } {};
		ElementToAdd& operator=(ElementToAdd& other)
		{
			projectiles.assign(other.projectiles.begin(), other.projectiles.end());
			enemies.assign(other.enemies.begin(), other.enemies.end());
			hasElementToAdd = other.hasElementToAdd;
			return *this;
		}
		ElementToAdd(ElementToAdd& other)
		{
			*this = other;
		};
	};
	Personnage(sf::Texture& texture, const sf::IntRect& rectTexture, int pointsDeVie, Arme* armeEquipe, float vitesse, float modificateurVitesseRecul, TypeWeapon projectiletype)
		: pointsDeVie{pointsDeVie}, armeEquipe{armeEquipe}, vitesse{vitesse},modificateurVitesseRecul{modificateurVitesseRecul}
		, type{projectiletype}
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
		for (int i = 0; i < boucliers.size(); i++)
		{
			delete boucliers.top();
			boucliers.pop();
		}
	}
	bool CanFire() const
	{
		bool armeMunition = armeEquipe->GetMunition() != 0 || armeEquipe->GetArmeCharge() > 0;
		return armeMunition && clock.getElapsedTime().asMilliseconds() - armeEquipe->GetTempsEntreTir().asMilliseconds() > dernierTir.asMilliseconds();
	}
	bool IsDead() const
	{
		return pointsDeVie <= 0;
	}
	virtual StructuresDonnees::list<Projectile*>* Fire()
	{
		dernierTir = clock.getElapsedTime();
		return armeEquipe->Tire(getPosition(), type, 0);
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
		RepositionnerDansLimite(bounds);
	}
	virtual void Move(Direction direction, sf::FloatRect bounds)
	{
		Move(direction, vitesse, bounds);
	}
	virtual void Move(Direction direction, float distance, sf::FloatRect bounds)
	{
		switch (direction)
		{
		case Droite:
			move(distance, 0);
			break;
		case Gauche:
			move(-distance, 0);
			break;
		case Haut:
			move(0, -distance);
			break;
		case Bas:
			move(0, distance);
			break;
		default:
			break;
		}
		RepositionnerDansLimite(bounds);
	}
	virtual void RecoitDommage(TypeWeapon type, int dommage)
	{
		if(type != this->type)
		{
			if (!boucliers.is_empty() && boucliers.top()->GetTypeBouclier() == type)
			{
				int dommageRestant = dommage;
				while (pointsDeVie > 0 && dommageRestant > 0)
				{
					if (!boucliers.is_empty())
					{
						dommageRestant = boucliers.top()->RecoitDommage(type, dommage);
						if (boucliers.top()->Detruit())
						{
							delete boucliers.top();
							boucliers.pop();
						}
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
		if (iter != armes.rend() && ++iter != armes.rend())
			armeEquipe = *iter;
	}
	virtual void chargerArme()
	{
		armeEquipe->ChargerArme();
	}
	Arme::ArmeType GetArmeType() const
	{
		return armeEquipe->GetArmeType();
	}
	void AjouterArme(Arme* arme)
	{
		armes.push_back(arme);
	}
	virtual void Draw(RenderWindow& window)
	{
		window.draw(*this);
		if (!boucliers.is_empty())
			window.draw(*boucliers.top());
	}
	void SetType(TypeWeapon type)
	{
		type = type;
	}
	TypeWeapon GetType() const
	{
		return type;
	}
	int GetVie() const
	{
		return pointsDeVie;
	}
	float GetVitesse() const
	{
		return vitesse;
	}
	float GetVitesseRecule() const
	{
		return vitesse*modificateurVitesseRecul;
	}
	virtual ElementToAdd Collisionner(const Personnage& other) = 0;
};
