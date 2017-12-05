#pragma once
#include "Bonus.h"
#include <SFML/System/Time.hpp>
#include "../StructuresDonnees/list.hpp"
#include "Projectile.hpp"
class Arme
	:public Bonus // D�rive de la classe bonus, car les armes peuvent �tre rammass�es
{
protected:
	sf::Time tempsEntreTir; // Temps de tir entre chaque coup. Diff�rent entre chaque arme
	int munition; // Nombre d emunition que chaque arme poss�de
public:	
	/// <summary>
	/// ICr�ation d'une nouvelle arme
	/// </summary>
	/// <param name="texture">La texture.</param>
	/// <param name="tempsEntreTir">Le temps entre les tirs.</param>
	/// <param name="munition">Les munitions.</param>
	/// <param name="pos">La position.</param>
	Arme(sf::Texture& texture, sf::Time tempsEntreTir, int munition, Vector2f pos = Vector2f(0, 0)) : Bonus(texture, pos), tempsEntreTir{ tempsEntreTir }, munition{ munition }
	{
		setTexture(texture); // On positionne correctement la texture de l'arme
		setPosition(pos); // On positionne la texture � 0,0 par d�faut
		setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2); // On centre l'origine de la texture

	}
	virtual ~Arme() // Destructeur de la classe arme
	{
		
	}
	virtual StructuresDonnees::list<Projectile*>* Tire(sf::Vector2f origineDuTir, TypeWeapon type, float angle) = 0; // � caque tir on retourne une liste de balle puisque chaque arme � un comportement diff�rent	
/// <summary>
/// Retourne le temps de tir de l'arme en utilisation
/// </summary>
/// <returns></returns>
	sf::Time GetTempsEntreTir() const
	{
		return tempsEntreTir;
	}
};
