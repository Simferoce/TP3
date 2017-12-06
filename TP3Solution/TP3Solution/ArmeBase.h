#pragma once
#include "Arme.hpp"
#include <string>
#include <SFML/System/Time.hpp>

class ArmeBase :
	public Arme // Dérive de la classe arme
{
	static sf::Texture texture; // La texture de l'arme de base
	static const std::string texturePath; // L'emplacement de la texture de base
	static const int munition; // Le nombre de munition de l'arme de base soit infini
	static const sf::Time delaiEntreLesTirsDeBase; // Delais entre chaque tir avec l'arme de base
	static const std::string nomArme;
public:
	static bool initTexture(); // Initialisation de la texture de l'arme de base	
/// <summary>
/// Tir avec l'arme principale
/// </summary>
/// <param name="origineDuTir">L'origine du tir.</param>
/// <param name="type">Le type d'arme utilisé (joueur/ennemu).</param>
/// <param name="angle">L'angle de la balle.</param>
/// <returns></returns>
	StructuresDonnees::list<Projectile*>* Tire(sf::Vector2f origineDuTir, TypeWeapon type, float angle) override;
	std::string GetNomArme() const override;
	ArmeBase(); // Constructeur de l'arme de base
	~ArmeBase(); // Destructeur de l'arme de base
};

