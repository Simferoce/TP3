#pragma once
#include "Bonus.h"
#include "TypeWeapon.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Bouclier :
	public Bonus // Dérive de la classe bonus
{
private:
	static Texture textureInactive;
	static const std::string texturePathInactive;
	static Texture textureActive;
	static const std::string texturePathActive;
	
protected:
	int ptsVie; // Le nombre de point de vie que le bouclier possède

public:	


	/// <summary>
	/// Créeation du dit bouclier
	/// </summary>
	/// <param name="texture">La texture.</param>
	/// <param name="ptsVie">Les PTS de vie.</param>
	/// <param name="type">Le type du bouclier.</param>
	/// <param name="pos">Sa position.</param>
	Bouclier::Bouclier(int ptsVie, BonusType type, Vector2f pos, bool activeTextureOn) : Bonus(textureInactive, type, pos), ptsVie{ ptsVie }
	{
		if (type == BouclierVert)
			setColor(sf::Color::Green);
		else if (type == BouclierRouge)
			setColor(sf::Color::Red);
		else if (type == BouclierJaune)
			setColor(sf::Color::Yellow);
		if(activeTextureOn)
		{
			setPosition(pos);
			setTexture(textureActive);
			setTextureRect(IntRect(0,0,32,32));
			setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
		}
		else
		{
			setPosition(pos);
			setTexture(textureInactive);
			setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
		}
	}
	BonusType GetTypeBouclier() const { return type; };
	virtual ~Bouclier(){};
	
	/// <summary>
	/// Recoit le dommage.
	/// </summary>
	/// <param name="type">Le type de dommage</param>
	/// <param name="dommage">Le dommage</param>
	/// <returns>Le nbre de dommage non absorbé.</returns>
	virtual int RecoitDommage(TypeWeapon type, int dommage)
	{
		if (this->type == type)
			ptsVie -= dommage;
		return ptsVie < 0 ? ptsVie : 0;
	};	
	/// <summary>
	/// Si le bouclier est détruit, retourne vrai, sinon faux.
	/// </summary>
	/// <returns></returns>
	bool Detruit() const { return ptsVie <= 0; };
	int GetVie() const
	{
		return ptsVie;
	}
	static bool initTexture()
	{
		if (!textureActive.loadFromFile(texturePathActive))
			return false;
		if (!textureInactive.loadFromFile(texturePathInactive))
			return false;
		return true;
	}

};

