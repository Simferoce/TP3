#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Sujet.h"

class Bonus
	: public sf::Sprite, public Sujet
{
public:
	bool isPickedUp = false;
	bool isDestroyed = false;
	bool isActive = false;
	Bonus(sf::Texture& texture )
	{
		setTexture(texture);
	}	
	/// <summary>
	/// Détermine si le bonus est actif
	/// </summary>
	/// <returns>
	///   <c>true</c> si le bonus est actif; sinon, <c>false</c>.
	/// </returns>
	bool IsActive() 
	{
		notifierTousLesObservateurs();
		return isActive;
	}
	/// <summary>
	/// Détermine si le bonus est détruit (pris par un ennemi) 
	/// </summary>
	/// <returns>
	///   <c>true</c> si le bonus est actif; sinon, <c>false</c>.
	/// </returns>
	bool IsDestroyed()
	{
		notifierTousLesObservateurs();
		return isDestroyed;
	}
	/// <summary>
	/// Détermine si le bonus est actif (pris par le joueur)
	/// </summary>
	/// <returns>
	///   <c>true</c> si le bonus est actif; sinon, <c>false</c>.
	/// </returns>
	bool IsPickedUp()
	{
		notifierTousLesObservateurs();
		return isPickedUp;
	}

};
