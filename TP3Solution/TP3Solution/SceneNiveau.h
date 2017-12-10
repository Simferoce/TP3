#pragma once
#include "Scene.h"
#include "Joueur.h"
#include "Enemy.h"
#include "EnemySentinelle.h"
#include "INiveau.h"
#include "../StructuresDonnees/queue.hpp"
#include "Spawner.h"

class SceneNiveau : public Scene , public INiveau
{
public:
	SceneNiveau();
	SceneNiveau(const SceneNiveau& other);
	~SceneNiveau();

	scenes run();
	bool init(RenderWindow * const window);
	void getInputs();
	void update();
	void draw();
	virtual StructuresDonnees::list<Projectile*>& GetAllProjectiles() override;
	virtual StructuresDonnees::list<Enemy*>& GetAllEnemies() override;
	virtual const Joueur& GetPlayer() const override;
	virtual const FloatRect GetBounds() const override;
private:
	//L'arrière plan de l'écran titre.
	Texture ecranNiveauT;
	Sprite ecranNiveau;
	Sprite ecranNiveau2;
	static const int posXNextEnemy = 1150;
	static const int posYNextEnemy = 50;
	static const int distanceNextEnemy = 30;
	static const int nbreEnemyNext = 5;
	bool spaceReleased = false;
	Sprite nextEnemy[nbreEnemyNext];
	//Le type de police utilisée
	Font font;
	Text vieJoueur;
	Text munitionArmes;
	Text boucliersText;
	Joueur* joueur;
	
	StructuresDonnees::list<Projectile*> projectiles;
	StructuresDonnees::list<Enemy*> enemies;
	StructuresDonnees::list<Bonus*> bonus;
	static const int nbSpawner = 3;
	static const int DistanceAvecLeFond = 50;
	static const int posYSpawner[nbSpawner];
	static const int nbEnemy = 100;
	Spawner spawner[nbSpawner];
	sf::Clock enemiesSpawnClock;
	sf::Time lastEnemySpawn = sf::milliseconds(0);
	static const float vitesseDeBaseBackground;
	struct EnemiesHolder
	{
		sf::Time timeToWait;
		Enemy* enemyInWaiting;
		EnemiesHolder(Enemy* enemyInWaiting = nullptr, sf::Time timeToWait = sf::milliseconds(0)) : enemyInWaiting(enemyInWaiting), timeToWait{timeToWait} {}
	};
	StructuresDonnees::Queue<EnemiesHolder> enemiesQueue;
	std::map<Keyboard::Key, bool> inputKeys;
};
