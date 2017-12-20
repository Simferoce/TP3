#include "Joueur.h"
#include <SFML/Graphics/Texture.hpp>
#include "Kamikaze.h"
#include "ArmeLaserPercant.h"
#include "ArmeFusilAPompe.h"
#include "BombeExplosive.h"
#include "FabriqueBonus.h"
#include "MultiplicateurXp.h"

const std::string Joueur::texturePath = "Ressources/Sprites/Joueur/Joueur_32x16.png";
sf::Texture Joueur::texture = sf::Texture();
const float Joueur::vitesseDeBase = 3.0f; // 3 avant
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

Personnage::ElementToModify Joueur::Collisionner(const Personnage& other)
{
	ElementToModify elem = ElementToModify(false);
	if (typeid(other) == typeid(Kamikaze))
		pointsDeVie -= other.GetVie();
	return elem;
}

Joueur::Joueur() : Personnage(texture, textureRectBase[animationDeBase], pointsVieDeBase, GetArmeDefaut(), vitesseDeBase,modificateurVitesseReculDebase, projectileTypeDeBase), score{0}
{
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
	boucliers.push(new Bouclier(2, Bonus::BouclierRouge, getPosition(),true));
	boucliers.push(new Bouclier(2, Bonus::BouclierJaune, getPosition(), true));
	boucliers.push(new Bouclier(2, Bonus::BouclierVert, getPosition(), true));
	multiplicateurActif = false;
	delaisEntreActivationBonus.restart();
	dernierBonusActif = delaisEntreActivationBonus.getElapsedTime();
}

Joueur::~Joueur()
{
	size_t tailleTableau = boucliers.size();
	for(int i = 0; i < tailleTableau; i++)
	{
		delete boucliers.top();
		boucliers.pop();
	}
}

void Joueur::notifier(Sujet* sujet)
{
	if (typeid(*(sujet)) == typeid(ArmeLaserPercant)) 
	{
		auto iterArmeJoueur = std::find(armes.begin(), armes.end(), armeEquipe);
		while (armeEquipe->type != Bonus::BonusType::ArmeSpecialeRayonLaser) // recherche nouvelle arme
		{
			if (armeEquipe->type == Bonus::ArmeSpecialeShotgun)
				previousWeapon();
			else if (armeEquipe->type == Bonus::ArmeDeBase)
				nextWeapon();
			else if (armeEquipe->type == Bonus::ArmeSpecialeSurpuissante)
				nextWeapon();
		}
		auto iterArmeRamassee = std::find(armes.begin(), armes.end(), armeEquipe);
		armeEquipe = *iterArmeRamassee;
		armeEquipe->SetMunition(5);
		armeEquipe = *iterArmeJoueur;
	}
	else if (typeid(*(sujet)) == typeid(ArmeFusilAPompe))
	{
		auto iterArmeJoueur = std::find(armes.begin(), armes.end(), armeEquipe);
		while (armeEquipe->type != Bonus::BonusType::ArmeSpecialeShotgun) // recherche nouvelle arme
		{
			nextWeapon();
		}
		auto iterArmeRamassee = std::find(armes.begin(), armes.end(), armeEquipe);
		armeEquipe = *iterArmeRamassee;
		armeEquipe->SetMunition(50);
		armeEquipe = *iterArmeJoueur;
	}
	else if (typeid(*(sujet)) == typeid(ArmeChargee))
	{
		auto iterArmeJoueur = std::find(armes.begin(), armes.end(), armeEquipe);
		while (armeEquipe->type != Bonus::BonusType::ArmeSpecialeSurpuissante) // recherche nouvelle arme
		{
			if (armeEquipe->type == Bonus::ArmeSpecialeShotgun)
				previousWeapon();
			else if (armeEquipe->type == Bonus::ArmeDeBase)
				nextWeapon();
			else if (armeEquipe->type == Bonus::ArmeSpecialeRayonLaser)
				previousWeapon();
		}
		auto iterArmeRamassee = std::find(armes.begin(), armes.end(), armeEquipe);
		armeEquipe = *iterArmeRamassee;
		armeEquipe->SetMunition(2000);
		armeEquipe = *iterArmeJoueur;
	}
	else if (typeid(*(sujet)) == typeid(MultiplicateurXp))
	{
		multiplicateurActif = true;
		dernierBonusActif = delaisEntreActivationBonus.getElapsedTime();
	}
}

Arme* Joueur::GetArme()
{
	return armeEquipe;
}

void Joueur::AjouterBonus(Bonus* bonus)
{
	if(bonus->type == Bonus::BouclierVert)
		boucliers.push(new Bouclier(2, Bonus::BouclierVert, getPosition(), true));

	else if (bonus->type == Bonus::BouclierJaune)
		boucliers.push(new Bouclier(2, Bonus::BouclierJaune, getPosition(), true));
	
	else if (bonus->type == Bonus::BouclierRouge)
		boucliers.push(new Bouclier(2, Bonus::BouclierRouge, getPosition(), true));

}
int Joueur::GetScore() const
{
	return score;
}

void Joueur::SetScore(int points)
{
	if(MultiplicateurActif())
		score += points*2;
	else
		score += points;
}

bool Joueur::MultiplicateurActif()
{
	if (multiplicateurActif && delaisEntreActivationBonus.getElapsedTime().asMilliseconds() - dernierBonusActif.asMilliseconds() < dureeTempsBonus)
		return multiplicateurActif;
	else
		return multiplicateurActif = false;
}







