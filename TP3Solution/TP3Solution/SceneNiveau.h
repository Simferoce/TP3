#pragma once
#include "Scene.h"
#include "Joueur.h"
#include "Enemy.h"
#include "EnemySentinelle.h"
#include "INiveau.h"
#include "../StructuresDonnees/queue.hpp"

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
	virtual const StructuresDonnees::list<Projectile*>& GetAllProjectiles() const override;
	virtual const StructuresDonnees::list<Enemy*>& GetAllEnemies() const override;
	virtual const Joueur& GetPlayer() const override;
	virtual const FloatRect GetBounds() const override;
private:
	//L'arrière plan de l'écran titre.
	Texture ecranNiveauT;
	Sprite ecranNiveau;
	Sprite ecranNiveau2;
	//Le type de police utilisée
	Font font;
	Text vieJoueur;
	Joueur* joueur;
	StructuresDonnees::list<Projectile*> projectiles;
	StructuresDonnees::list<Enemy*> enemies;
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
