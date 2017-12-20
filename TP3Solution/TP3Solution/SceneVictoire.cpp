#include "SceneVictoire.h"



SceneVictoire::SceneVictoire()
{
	isRunning = true;
}


SceneVictoire::~SceneVictoire()
{
}


bool SceneVictoire::init(RenderWindow* const window)
{

	mainWin = window;
	if (!ecranVictoireT.loadFromFile("Ressources\\Background\\Victory.jpg"))
		return false;
	ecranVictoire.setTexture(ecranVictoireT);
	ecranVictoire.setOrigin(0, 0);

	return true;
}


Scene::scenes SceneVictoire::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}
	return transitionVersScene;
}

void SceneVictoire::getInputs()
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

void SceneVictoire::update()
{
}

void SceneVictoire::draw()
{
	mainWin->clear();
	mainWin->draw(ecranVictoire);
	mainWin->display();
}
