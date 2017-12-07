#include "Enemy.h"
#include "Assistant.h"

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
Personnage::ElementToModify Enemy::Update(INiveau & game)
{
	for (Composite* composite : composites)
	{
		if (Assistant* assistant = dynamic_cast<Assistant*>(composite))
		{
			assistant->MoveAround(getPosition());
		}
	}
	return ElementToModify(false);
}
void Enemy::Draw(RenderWindow & window)
{
	Personnage::Draw(window);
	for (Composite* composite : composites)
	{
		if (Enemy* assistant = dynamic_cast<Enemy*>(composite))
			assistant->Draw(window);
	}
}
void Enemy::Move(int bitMask, sf::FloatRect bounds)
{
	
}
