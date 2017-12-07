#pragma once
#include "Bonus.h"
#include <SFML/System/Time.hpp>
#include "../StructuresDonnees/list.hpp"
#include "Projectile.hpp"
class Arme
	:public Bonus // Dérive de la classe bonus, car les armes peuvent être rammassées
{
public:
	enum ArmeType { Charger, Other };
protected:
	sf::Time tempsEntreTir;
	ArmeType typeArme = Other;
	int munition;
	int charge = 0;
public:
	Arme(sf::Texture& texture, sf::Time tempsEntreTir, int munition , Vector2f pos = Vector2f(0, 0) ) : Bonus(texture, ArmeDeBase , pos), tempsEntreTir{tempsEntreTir}, munition{munition}
	{
		setTexture(texture); // On positionne correctement la texture de l'arme
		setPosition(pos); // On positionne la texture à 0,0 par défaut
		setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2); // On centre l'origine de la texture

	}
	virtual ~Arme() // Destructeur de la classe arme
	{
		
	}
	virtual StructuresDonnees::list<Projectile*>* Tire(sf::Vector2f origineDuTir, TypeWeapon type, float angle) = 0; // À caque tir on retourne une liste de balle puisque chaque arme à un comportement différent	
/// <summary>
/// Retourne le temps de tir de l'arme en utilisation
/// </summary>
/// <returns></returns>
	sf::Time GetTempsEntreTir() const
	{
		return tempsEntreTir;
	}
	void SetTempsEntreTir(sf::Time tempsEntreTir) 
	{
		this->tempsEntreTir = tempsEntreTir;
	}
	virtual void ChargerArme()
	{
		
	}
	int GetMunition() const
	{
		return munition;
	}
	ArmeType GetArmeType() const
	{
		return typeArme;
	}
	int GetArmeCharge() const
	{
		return charge;
	}
	virtual std::string GetNomArme() const = 0;
};
