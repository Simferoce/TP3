#pragma once
#include "Bonus.h"
#include <SFML/System/Time.hpp>
#include "../StructuresDonnees/list.hpp"
#include "Projectile.hpp"
class Arme
	:public Bonus // Dérive de la classe bonus, car les armes peuvent être rammassées
{
protected:
	sf::Time tempsEntreTir; // Temps de tir entre chaque coup. Différent entre chaque arme
	int munition; // Nombre d emunition que chaque arme possède
public:	
	/// <summary>
	/// ICréation d'une nouvelle arme
	/// </summary>
	/// <param name="texture">La texture.</param>
	/// <param name="tempsEntreTir">Le temps entre les tirs.</param>
	/// <param name="munition">Les munitions.</param>
	/// <param name="pos">La position.</param>
	Arme(sf::Texture& texture, sf::Time tempsEntreTir, int munition, Vector2f pos = Vector2f(0, 0)) : Bonus(texture, pos), tempsEntreTir{ tempsEntreTir }, munition{ munition }
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
};
