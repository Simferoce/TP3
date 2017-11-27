#pragma once
#include "Scene.h"

class SceneMenu : public Scene
{
public:
	SceneMenu();
	~SceneMenu();

	scenes run();
	bool init(RenderWindow * const window);
	void getInputs();
	void update();
	void draw();

private:
	//L'arri�re plan de l'�cran titre.
	Texture ecranMenuT;
	Sprite ecranMenu;
	//Le type de police utilis�e
	Font font;

};
