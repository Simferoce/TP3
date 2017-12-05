#include "SceneTitre.h"



SceneTitre::SceneTitre()
{
	isRunning = true;
}


SceneTitre::~SceneTitre()
{
}

bool SceneTitre::init(RenderWindow* const window)
{

	mainWin = window;
	if (!ecranTitreT.loadFromFile("Ressources\\Background\\Title.jpg"))
		return false;
	if (!font.loadFromFile("Ressources/Fonts/PressStart2P-Regular.ttf"))
		return false;
	ecranTitre.setTexture(ecranTitreT);
	ecranTitre.setOrigin(0, 0);

	// Titre du jeu
	titreDuJeu.setFont(font);
	titreDuJeu.setPosition(130, LARGEUR_VUE/ 2);
	titreDuJeu.setCharacterSize(72);
	titreDuJeu.setOutlineColor(Color::Yellow);
	titreDuJeu.setOutlineThickness(3);
	titreDuJeu.setFillColor(Color::Red);
	titreDuJeu.setString("Space Survival");
	return true;
}

Scene::scenes SceneTitre::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}
	return transitionVersScene;
}

void SceneTitre::getInputs()
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
			transitionVersScene = scenes::Niveau1;				
			}
		}
		else if (event.type == Event::MouseButtonPressed)
		{
			isRunning = false;
			transitionVersScene = scenes::Niveau1;
		}
	}
}

void SceneTitre::update()
{
}

void SceneTitre::draw()
{
	mainWin->clear();
	mainWin->draw(ecranTitre);
	mainWin->draw(titreDuJeu);
	mainWin->display();
}




