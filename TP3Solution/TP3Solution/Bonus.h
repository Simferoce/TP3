#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Sujet.h"
#include <SFML/Graphics/RenderWindow.hpp>

using namespace sf;

class Bonus
	: public Sprite, public Sujet
{
public:
	enum BonusType
	{
		BouclierVert,
		BouclierJaune,
		BouclierRouge,
		ArmeSpecialeShotgun,
		ArmeSpecialeRayonLaser,
		ArmeSpecialeSurpuissante,
		BombeExplosive,
		BombeElectromagnetique,
		MultiplicateurDePoints,
		ArmeDeBase
	};

	BonusType type;
	/// <summary>
	/// Création d'un bonus
	/// </summary>
	/// <param name="texture">La texture.</param>
	/// <param name="pos">La position.</param>
	Bonus(Texture& texture, BonusType newType, Vector2f pos) : type { newType }
	{
		setTexture(texture); // La texture du dit bonus
		setPosition(pos); // La position du bonus
		setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2); // On centre la texture du bonus
	}	
	
	void Draw(RenderWindow& window)
	{
		window.draw(*this);
	}

};
