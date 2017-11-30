#include "EnemySentinelle.h"
#include "Joueur.h"


const std::string EnemySentinelle::texturePath = "Ressources\\Sprites\\Enemy\\Regulier\\Sentinelle\\sentinelle_16x16.png";
sf::Texture EnemySentinelle::texture = sf::Texture();
const float EnemySentinelle::vitesseDeBase = 0.0f;
const int EnemySentinelle::pointsVieDeBase = 1;
const float EnemySentinelle::modificateurVitesseReculDebase = 0.0f;
const TypeWeapon EnemySentinelle::projectileTypeDeBase = TypeWeapon::EnemyGreen;
const sf::IntRect EnemySentinelle::textureRectBase[nbreAnimation] = { sf::IntRect(0,0,16,16), sf::IntRect(16,0,16,16),
sf::IntRect(32,0,32,16), sf::IntRect(48,0,16,16), sf::IntRect(64,0,16,16), sf::IntRect(80,0,16,16), sf::IntRect(96,0,16,16), sf::IntRect(112,0,16,16) };
const sf::Time EnemySentinelle::tempAnimation = sf::milliseconds(300);
const int EnemySentinelle::animationDeBase = 0;

EnemySentinelle::EnemySentinelle() : Enemy(texture, textureRectBase[animationDeBase], pointsVieDeBase, GetArmeDefaut(), vitesseDeBase, modificateurVitesseReculDebase, projectileTypeDeBase)
{
}


EnemySentinelle::~EnemySentinelle()
{
}

void EnemySentinelle::Move(int bitMask, sf::FloatRect bounds)
{
	
}

bool EnemySentinelle::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}





