#pragma once
#include "Scene.h"
#include "Joueur.h"
#include "Enemy.h"
#include "EnemySentinelle.h"
#include "INiveau.h"

class SceneNiveau : public Scene , public INiveau
{
public:
	SceneNiveau();
	~SceneNiveau();

	scenes run();
	bool init(RenderWindow * const window);
	void getInputs();
	void update();
	void draw();
	virtual const StructuresDonnees::list<Projectile*>& GetAllProjectiles() const override;
	virtual const StructuresDonnees::list<Enemy*>& GetAllEnemies() const override;
	virtual const Joueur& GetPlayer() const override;
private:
	//L'arrière plan de l'écran titre.
	Texture ecranNiveauT;
	Sprite ecranNiveau;
	//Le type de police utilisée
	Font font;
	Joueur* joueur;
	StructuresDonnees::list<Projectile*> projectiles;
	StructuresDonnees::list<Enemy*> enemies;
	std::map<Keyboard::Key, bool> inputKeys;
};
