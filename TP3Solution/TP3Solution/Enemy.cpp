#include "Enemy.h"

Enemy::Enemy(sf::Texture& texture, const sf::IntRect& rectTexture, int pointsDeVie, Arme* armeEquipe, float vitesse, float modificateurVitesseRecul, TypeWeapon projectiletype) 
	: Personnage(texture, rectTexture, pointsDeVie, armeEquipe, vitesse, modificateurVitesseRecul, projectiletype)
{
	
}
Enemy::~Enemy()
{

}
void Enemy::notifier(Sujet* sujet)
{
	
}
Personnage::ElementToModify Enemy::Collisionner(const Personnage& other)
{
	ElementToModify elem = Personnage::ElementToModify(false);
	return elem;
}
void Enemy::Move(int bitMask, sf::FloatRect bounds)
{
	
}
