#pragma once
#include "Scene.h"
#include "Joueur.h"
#include "Enemy.h"
#include "EnemySentinelle.h"

class SceneNiveau : public Scene
{
public:
	SceneNiveau();
	~SceneNiveau();

	scenes run();
	bool init(RenderWindow * const window);
	void getInputs();
	void update();
	void draw();

private:
	//L'arrière plan de l'écran titre.
	Texture ecranNiveauT;
	Sprite ecranNiveau;
	//Le type de police utilisée
	Font font;
	Joueur* joueur;
	Enemy* enemyTest;
	StructuresDonnees::list<Projectile*> projectiles;
	std::map<Keyboard::Key, bool> inputKeys;
};
