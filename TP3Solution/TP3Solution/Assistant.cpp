#include "Assistant.h"
#include "INiveau.h"
const std::string Assistant::texturePath = "Ressources\\Sprites\\Enemy\\Regulier\\Sentinelle\\sentinelle_16x16.png";
sf::Texture Assistant::texture = sf::Texture();
const float Assistant::vitesseDeBase = 0.01f;
const int Assistant::pointsVieDeBase = 1;
const float Assistant::modificateurVitesseReculDebase = 0.0f;
const sf::IntRect Assistant::textureRectBase[nbreAnimation] = { sf::IntRect(0,0,16,16), sf::IntRect(16,0,16,16),
sf::IntRect(32,0,16,16), sf::IntRect(48,0,16,16), sf::IntRect(64,0,16,16), sf::IntRect(80,0,16,16), sf::IntRect(96,0,16,16), sf::IntRect(112,0,16,16) };
const int Assistant::tempAnimation = 100;
const int Assistant::animationDeBase = 0;

TypeWeapon Assistant::genererTypeArmeEnemy()
{
	int typeArme = rand() % 3 + 0;
	return (TypeWeapon)typeArme;
}

Enemy * Assistant::TrouverLePlusProche(Vector2f pos, StructuresDonnees::list<Enemy*>& enemies)
{
	float distanceEnemy = INT32_MAX;
	Enemy* nearestEnemy = nullptr;
	for(auto iter = enemies.begin(); iter != enemies.end(); ++iter)
	{
		bool test = typeid(*(*iter)) != typeid(Assistant);
		int distance = sqrt(pow((*iter)->getPosition().x - pos.x, 2) + pow((*iter)->getPosition().y - pos.y, 2));
		if (typeid(*(*iter)) != typeid(Assistant) && distance < distanceEnemy)
		{
			nearestEnemy = (*iter);
			distanceEnemy = distance;
		}
	}
	return nearestEnemy;
}

Assistant::Assistant() : Enemy(texture, textureRectBase[animationDeBase], pointsVieDeBase, nullptr, vitesseDeBase, modificateurVitesseReculDebase, genererTypeArmeEnemy())
{
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
}


Assistant::~Assistant()
{
}

Personnage::ElementToModify Assistant::Update(INiveau& game)
{
	Personnage::ElementToModify elementToModify = Personnage::ElementToModify(false);
	Enemy* nearestEnemy = TrouverLePlusProche(getPosition(), game.GetAllEnemies());
	if(nearestEnemy != nullptr)
	{
		float variationX = nearestEnemy->getPosition().x - getPosition().x;
		float variationY = nearestEnemy->getPosition().y - getPosition().y;
		float distance = sqrtf(powf(variationX, 2) + powf(variationY, 2));
		if (distance < orbitationDistance && distance > orbitationDistnaceMinimal)
		{
			nearestEnemy->AjouterComposite(this);
			elementToModify.hasElementToModify = true;
			elementToModify.removeObject = true;
		}
		else if(distance > orbitationDistnaceMinimal)
		{
			this->direction = sf::Vector2f(variationX / distance, variationY / distance);
			Move(direction, game.GetBounds());
		}
	}
	return elementToModify;
}
void Assistant::Move(const Vector2f vectorDirection, const sf::FloatRect bounds)
{
	float newX = getPosition().x + direction.x*vitesse;
	float newY = getPosition().y + direction.y*vitesse;
	setPosition(newX, newY);
	RepositionnerDansLimite(bounds);
}
void Assistant::MoveAround(Vector2f pos)
{
	float variationX = pos.x - getPosition().x;
	float variationY = pos.y - getPosition().y;
	float distance = sqrtf(powf(variationX, 2) + powf(variationY, 2));
	float circonference = distance*3.1416;
	float angleCentre = vitesse * ((float)2 * 3.1416) / circonference;
	float angleCentreEnDegree = angleCentre * 360 / (2 * 3.1416);
	float angleActuelleSin = asin(variationY / distance);
	float angleActuelleSinDegree = angleActuelleSin * 360 / (2 * 3.1416);
	float angleActuelleCos = acos(variationX / distance);
	float angleActuelleCosDegree = angleActuelleCos * 360 / (2 * 3.1416);
	float angleActuel = atan2(variationY, variationX);
	float angleActuelEnDegree = angleActuel * 360 / (2 * 3.1416);
	float angleResultant = angleCentre + angleActuel;
	float angleResultantEnDegree = angleResultant * 360 / (2 * 3.1416);
	Vector2f vectorDeAngleResultant = Vector2f(cos(angleResultant), sin(angleResultant));
	Vector2f newPos = vectorDeAngleResultant*distance + pos;
	Vector2f position = getPosition();
	setPosition(newPos);
}
bool Assistant::initTexture()
{
	if (!texture.loadFromFile(texturePath))
		return false;
	return true;
}
