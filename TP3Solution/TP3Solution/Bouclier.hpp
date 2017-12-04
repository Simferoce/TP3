#pragma once
#include "Bonus.h"
#include "TypeWeapon.h"
#include <SFML/Graphics/Texture.hpp>
class Bouclier :
	public Bonus
{
private:
	static Texture textureActive;
	static const std::string texturePathActive;
protected:
	int ptsVie;
	TypeWeapon type;
public:
	Bouclier::Bouclier(int ptsVie, TypeWeapon type, Vector2f pos) : Bonus(textureActive, pos), ptsVie{ ptsVie }, type{ type }
	{
		if (type == TypeWeapon::EnemyGreen)
			setColor(sf::Color::Green);
		else if (type == TypeWeapon::EnemyRed)
			setColor(sf::Color::Red);
		else if (type == TypeWeapon::EnemyYellow)
			setColor(sf::Color::Yellow);
		setPosition(pos);
		setTexture(textureActive);
		setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
	}
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
		return ptsVie < 0 ? ptsVie : 0;
	};
	bool Detruit() const { return ptsVie <= 0; };
	static bool initTexture()
	{
		if (!textureActive.loadFromFile(texturePathActive))
			return false;
		return true;
	}
};

