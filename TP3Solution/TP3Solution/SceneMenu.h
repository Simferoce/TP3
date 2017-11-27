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
	//L'arrière plan de l'écran titre.
	Texture ecranMenuT;
	Sprite ecranMenu;
	//Le type de police utilisée
	Font font;

};
