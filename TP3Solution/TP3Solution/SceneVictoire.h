#pragma once
#include "Scene.h"
class SceneVictoire :
	public Scene
{
public:
	SceneVictoire();
	~SceneVictoire();

	scenes run();
	bool init(RenderWindow * const window);
	void getInputs();
	void update();
	void draw();

private:
	//L'arri�re plan de l'�cran titre.
	Texture ecranVictoireT;
	Sprite ecranVictoire;
};

