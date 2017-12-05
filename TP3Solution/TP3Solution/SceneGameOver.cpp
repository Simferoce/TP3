#include "SceneGameOver.h"



SceneGameOver::SceneGameOver()
{
	isRunning = true;
}


SceneGameOver::~SceneGameOver()
{
}

bool SceneGameOver::init(RenderWindow* const window)
{

	mainWin = window;
	if (!ecranGameOverT.loadFromFile("Ressources\\Background\\GameOver.jpg"))
		return false;
	ecranGameOver.setTexture(ecranGameOverT);
	ecranGameOver.setOrigin(0, 0);

	return true;
}

Scene::scenes SceneGameOver::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}
	return transitionVersScene;
}

void SceneGameOver::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
		{
			//fin à l'application
			isRunning = false;
			transitionVersScene = scenes::Fin;
		}
		else if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
			{
				isRunning = false;
				transitionVersScene = scenes::Fin; // À changer???
			}
			else
			{
				isRunning = false;
				transitionVersScene = scenes::Titre;
			}
		}
		else if (event.type == Event::MouseButtonPressed)
		{
			isRunning = false;
			transitionVersScene = scenes::Titre;
		}
	}
}

void SceneGameOver::update()
{
}

void SceneGameOver::draw()
{
	mainWin->clear();
	mainWin->draw(ecranGameOver);
	mainWin->display();
}
