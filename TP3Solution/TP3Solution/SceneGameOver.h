#pragma once
#include "Scene.h"
class SceneGameOver :
	public Scene
{
public:
	SceneGameOver();
	~SceneGameOver();

	scenes run();
	bool init(RenderWindow * const window);
	void getInputs();
	void update();
	void draw();

private:
	//L'arri�re plan de l'�cran titre.
	Texture ecranGameOverT;
	Sprite ecranGameOver;
};

