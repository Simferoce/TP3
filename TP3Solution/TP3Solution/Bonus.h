#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Sujet.h"

using namespace sf;

class Bonus
	: public Sprite, public Sujet
{
public:
	bool isPickedUp = false; // Si le joueur prend le bonus
	bool isDestroyed = false; // Si un ennemi prend le bonus avant le joueur
	bool isActive = false; // Si le bonus est sur le jeu
	
/// <summary>
/// Création d'un bonus
/// </summary>
/// <param name="texture">La texture.</param>
/// <param name="pos">La position.</param>
	Bonus(Texture& texture, Vector2f pos)
	{
		setTexture(texture); // La texture du dit bonus
		setPosition(pos); // La position du bonus
		setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2); // On centre la texture du bonus
	}	
	/// <summary>
	/// Détermine si le bonus est actif
	/// </summary>
	/// <returns>
	///   <c>true</c> si le bonus est actif; sinon, <c>false</c>.
	/// </returns>
	bool IsActive() 
	{
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
		return isPickedUp;
	}	
	/// <summary>
	/// Active le bonus
	/// </summary>
	void SetActive()
	{
		isActive = true;
	}
	/// <summary>
	/// Détruire le bonus
	/// </summary>
	void SetDestroyed()
	{
		isDestroyed = true;
	}
	/// <summary>
	/// Le bonus est pris par le joueur
	/// </summary>
	void SetIsPickedUp()
	{
		isPickedUp = true;
	}

};
