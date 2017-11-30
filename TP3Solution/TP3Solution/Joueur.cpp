#include "Joueur.h"
#include <SFML/Graphics/Texture.hpp>
const std::string Joueur::texturePath = "Gem.png";
sf::Texture Joueur::texture = sf::Texture();
const float Joueur::vitesseDeBase = 3.0f;
const int Joueur::pointsVieDeBase = 0;
const float Joueur::modificateurVitesseReculDebase = 0.7f;
const ProjectileType Joueur::projectileTypeDeBase = ProjectileType::Player;

bool Joueur::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}

Joueur::Joueur() : Personnage(texture, pointsVieDeBase, GetArmeDefaut(), vitesseDeBase,modificateurVitesseReculDebase,projectileTypeDeBase)
{

}

Joueur::~Joueur()
{
	
}
