#include "Kamikaze.h"
#include "Joueur.h"
#include "ProjectileBase.h"
#include "INiveau.h"
#include "Assistant.h"


const std::string Kamikaze::texturePath = "Ressources\\Sprites\\Enemy\\Regulier\\Kamikaze\\Kamikaze_16x16.png";
sf::Texture Kamikaze::texture = sf::Texture();
const float Kamikaze::vitesseDeBase = 0.7f;
const int Kamikaze::pointsVieDeBase = 5;
const float Kamikaze::modificateurVitesseReculDebase = 0.0f;
const sf::IntRect Kamikaze::textureRectBase[nbreAnimation] = { sf::IntRect(0,0,16,16), sf::IntRect(16,0,16,16),
sf::IntRect(32,0,16,16), sf::IntRect(48,0,16,16), sf::IntRect(64,0,16,16), sf::IntRect(80,0,16,16), sf::IntRect(96,0,16,16), sf::IntRect(112,0,16,16) };
const int Kamikaze::tempAnimation = 6;
const int Kamikaze::animationDeBase = 0;

TypeWeapon Kamikaze::genererTypeArmeEnemy()
{
	int typeArme = rand() % 2;
	return (TypeWeapon)typeArme;
}

Kamikaze::Kamikaze() : Enemy(texture, textureRectBase[animationDeBase], pointsVieDeBase, nullptr, vitesseDeBase, modificateurVitesseReculDebase, genererTypeArmeEnemy())
{
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
}


Kamikaze::~Kamikaze()
{
}

Enemy::ElementToModify Kamikaze::update(INiveau& game)
{
	ElementToModify elementToAdd(false);
	float variationX = game.GetPlayer().getPosition().x - getPosition().x;
	float variationY = game.GetPlayer().getPosition().y - getPosition().y;
	float distance = sqrtf(powf(variationX, 2) + powf(variationY, 2));
	this->direction = sf::Vector2f(variationX / distance, variationY / distance);
	setRotation(atan2f(variationY / distance, variationX / distance) * (180 / 3.14));
	Move(direction, game.GetBounds());
	animateur++;
	if (animationSens > 0 && animateur > nbreAnimation*tempAnimation)
		animationSens = -1;
	else if (animationSens < 0 && abs(animateur) > nbreAnimation*tempAnimation)
		animationSens = 1;
	setTextureRect(textureRectBase[(animateur/tempAnimation) % nbreAnimation]);
	return elementToAdd;
}

void Kamikaze::Move(const Vector2f vectorDirection, const sf::FloatRect bounds)
{
	float newX = getPosition().x + direction.x*vitesse;
	float newY = getPosition().y + direction.y*vitesse;
	setPosition(newX, newY);
	RepositionnerDansLimite(bounds);
}

Personnage::ElementToModify Kamikaze::Collisionner(const Personnage& other)
{
	ElementToModify elem = Enemy::Collisionner(other);
	pointsDeVie = 0;
	return elem;
}


bool Kamikaze::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}


