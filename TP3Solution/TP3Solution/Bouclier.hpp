#pragma once
#include "Bonus.h"
#include "TypeWeapon.h"

class Bouclier :
	public Bonus // Dérive de la classe bonus
{
protected:
	int ptsVie; // Le nombre de point de vie que le bouclier possède
	TypeWeapon type; // Le type du bouclier (vert/jaune/rouge)
public:	
	/// <summary>
	/// Créeation du dit bouclier
	/// </summary>
	/// <param name="texture">La texture.</param>
	/// <param name="ptsVie">Les PTS de vie.</param>
	/// <param name="type">Le type du bouclier.</param>
	/// <param name="pos">Sa position.</param>
	Bouclier::Bouclier(sf::Texture& texture, int ptsVie, TypeWeapon type, Vector2f pos) : Bonus(texture, pos), ptsVie{ ptsVie }, type{ type }
	{
		setTexture(texture); // On lui donne sa texture
		// On change sa couleur selon le type reçu en paramètre
		if (type == TypeWeapon::EnemyGreen)
			setColor(sf::Color::Green);
		else if (type == TypeWeapon::EnemyRed)
			setColor(sf::Color::Red);
		else if (type == TypeWeapon::EnemyYellow)
			setColor(sf::Color::Yellow);
		setPosition(pos); // On applique sa position
		setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2); // On place son origine au centre de la texture
	}	
	/// <summary>
	/// Retourne le type du bouclier.
	/// </summary>
	/// <returns></returns>
	TypeWeapon GetTypeBouclier() const { return type; };
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
		return ptsVie < 0 ? ptsVie * -1 : ptsVie;
	};	
	/// <summary>
	/// Si le bouclier est détruit, retourne vrai, sinon faux.
	/// </summary>
	/// <returns></returns>
	bool Detruit() const { return ptsVie <= 0; };
};

