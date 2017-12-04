#include "Joueur.h"
#include <SFML/Graphics/Texture.hpp>
#include "Kamikaze.h"
const std::string Joueur::texturePath = "Ressources/Sprites/Joueur/Joueur_32x16.png";
sf::Texture Joueur::texture = sf::Texture();
const float Joueur::vitesseDeBase = 12.0f; // 3 avant
const int Joueur::pointsVieDeBase = 100;
const float Joueur::modificateurVitesseReculDebase = 0.7f;
const TypeWeapon Joueur::projectileTypeDeBase = TypeWeapon::Player;
const sf::IntRect Joueur::textureRectBase[nbreAnimation] = { sf::IntRect(0,0,32,16), sf::IntRect(32,0,32,16),
												 sf::IntRect(64,0,32,16), sf::IntRect(96,0,32,16), sf::IntRect(128,0,32,16) };
const sf::Time Joueur::tempAnimation = sf::milliseconds(300);
const int Joueur::animationDeBase = 2;
bool Joueur::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}

void Joueur::Move(int bitMask, sf::FloatRect bounds)
{
	Personnage::Move(bitMask, bounds);
	if(bitMask == 1 || bitMask == 3 || bitMask == 9)
	{
		const int timePass = (animationHorloge.getElapsedTime().asMilliseconds() - (animateur - animationDeBase)*tempAnimation.asMilliseconds());
		animateur = timePass > 0 && animateur < nbreAnimation - 1 ? ++animateur : animateur;
	}
	else if (bitMask == 4 || bitMask == 6 || bitMask == 12)
	{
		const int timePass2 = (animationHorloge.getElapsedTime().asMilliseconds() - (animationDeBase - animateur)*tempAnimation.asMilliseconds());
		animateur = timePass2 > 0 && animateur > 0 ? --animateur : animateur;
	}
	else
	{
		animateur = animationDeBase;
		animationHorloge.restart();
	}
	setTextureRect(textureRectBase[animateur]);
	if(!boucliers.is_empty())
	boucliers.top()->setPosition(getPosition());
}

Personnage::ElementToAdd Joueur::Collisionner(const Personnage& other)
{
	ElementToAdd elem = ElementToAdd(false);
	if (typeid(other) == typeid(Kamikaze))
		pointsDeVie -= other.GetVie();
	return elem;
}

Joueur::Joueur() : Personnage(texture, textureRectBase[animationDeBase], pointsVieDeBase, GetArmeDefaut(), vitesseDeBase,modificateurVitesseReculDebase, projectileTypeDeBase)
{
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
	boucliers.push(new Bouclier(2, TypeWeapon::EnemyYellow, getPosition()));
}

Joueur::~Joueur()
{
	
}

void Joueur::notifier(Sujet* sujet)
{
	
}



