#include "Enemy.h"
#include "Assistant.h"
#include "BombeExplosive.h"
#include "BombeElectrique.h"

Enemy::Enemy(sf::Texture& texture, const sf::IntRect& rectTexture, int pointsDeVie, Arme* armeEquipe, float vitesse, float modificateurVitesseRecul, TypeWeapon projectiletype) 
	: Personnage(texture, rectTexture, pointsDeVie, armeEquipe, vitesse, modificateurVitesseRecul, projectiletype)
{
	bombeElectriqueActive = false;
	delaisEntreActivationBombe.restart();
	dernierBombeActif = delaisEntreActivationBombe.getElapsedTime();
	switch (projectiletype)
	{
	case TypeWeapon::EnemyGreen:
		setColor(Color::Green);
		break;
	case TypeWeapon::EnemyRed:
		setColor(Color::Red);
		break;
	case TypeWeapon::EnemyYellow:
		setColor(Color::Yellow);
		break;
	default:
		break;
	}
}
Enemy::~Enemy()
{

}
void Enemy::notifier(Sujet* sujet)
{
	if (typeid(*(sujet)) == typeid(BombeExplosive))
	{
		RecoitDommage(Laser, 999);
	}
	else if (typeid(*(sujet)) == typeid(BombeElectrique))
	{
		bombeElectriqueActive = true;
		dernierBombeActif = delaisEntreActivationBombe.getElapsedTime();
	}
}
Personnage::ElementToModify Enemy::Collisionner(const Personnage& other)
{
	ElementToModify elem = Personnage::ElementToModify(false);
	return elem;
}
Personnage::ElementToModify Enemy::Update(INiveau & game)
{
	ElementToModify elemToModify(&game);
	if (!BombeElectriqueActive())
	{
		Vector2f posBefore = getPosition();
		elemToModify = update(game);
		Vector2f deplacement = getPosition() - posBefore;
		for (Composite* composite : composites)
		{
			if (Assistant* assistant = dynamic_cast<Assistant*>(composite))
			{
				ElementToModify elem = assistant->Update(game);
				if (!elem.projectilesToAdd.is_empty())
				{
					elemToModify.hasElementToModify = true;
					elemToModify.projectilesToAdd.splice(elem.projectilesToAdd, elemToModify.projectilesToAdd.begin());
				}
				assistant->move(deplacement);
			}
		}
	}
	return elemToModify;
	
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

int Enemy::GetValeurPoints() const
{
	return valeurPoints;
}

bool Enemy::BombeElectriqueActive()
{
	if (bombeElectriqueActive && delaisEntreActivationBombe.getElapsedTime().asMilliseconds() - dernierBombeActif.asMilliseconds() < dureeTempsBonus)
		return bombeElectriqueActive;
	else
		return bombeElectriqueActive = false;
}

bool Enemy::SpawnBonus()
{
	int chanceApparition = rand() % 100;
	if (chanceApparition < 10)
		return true;
	else
		return false;
}




