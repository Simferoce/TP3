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
/// Cr�ation d'un bonus
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
	/// D�termine si le bonus est actif
	/// </summary>
	/// <returns>
	///   <c>true</c> si le bonus est actif; sinon, <c>false</c>.
	/// </returns>
	bool IsActive() 
	{
		return isActive;
	}
	/// <summary>
	/// D�termine si le bonus est d�truit (pris par un ennemi) 
	/// </summary>
	/// <returns>
	///   <c>true</c> si le bonus est actif; sinon, <c>false</c>.
	/// </returns>
	bool IsDestroyed()
	{
		return isDestroyed;
	}
	/// <summary>
	/// D�termine si le bonus est actif (pris par le joueur)
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
	/// D�truire le bonus
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
