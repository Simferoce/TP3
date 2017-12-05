#pragma once
#include "Scene.h"
class SceneTitre :
	public Scene
{
public:
	SceneTitre();
	~SceneTitre();

	scenes run();
	bool init(RenderWindow * const window);
	void getInputs();
	void update();
	void draw();

private:
	//L'arri�re plan de l'�cran titre.
	Texture ecranTitreT;
	Sprite ecranTitre;
	//Le type de police utilis�e
	Font font;
	// Titre du jeu
	Text titreDuJeu;
};

