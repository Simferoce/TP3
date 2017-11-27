#include "Game.h"
#include "Scene.h"
#include "SceneMenu.h"
#include "SceneNiveau.h"

Game::Game()
{
	//On place dans le contructeur ce qui permet à la game elle-même de fonctionner

	mainWin.create(VideoMode(LARGEUR, HAUTEUR, 32), "Le titre de mon jeu");  // , Style::Titlebar); / , Style::FullScreen);
	view = mainWin.getDefaultView();

	//Synchonisation coordonnée à l'écran!  Normalement 60 frames par secondes. À faire absolument
	mainWin.setVerticalSyncEnabled(true);
	//mainWin.setFramerateLimit(60);  //Équivalent... normalement, mais pas toujours. À utiliser si la synchonisation de l'écran fonctionne mal.
	//https://www.sfml-dev.org/tutorials/2.0/window-window.php#controlling-the-framerate
}

int Game::testTest()
{
	return 0;
}

int Game::run()
{
	if (!init())
	{
		return EXIT_FAILURE;
	}

	//deux enums et un pointeur de scene pour faire la manipulation de scène
	Scene::scenes selecteurDeScene = Scene::scenes::Niveau1;
	Scene::scenes sceneEnRetour;
	Scene* sceneActive = nullptr; //Pointeur de la super-classe, peut pointer sur n'imprte quelle scène

	while (true)
	{
		//Seule condition de sortie de toute l'app
		if (selecteurDeScene == Scene::scenes::Fin)
		{
			return EXIT_SUCCESS;
		}
		else
		{
			//Vous allez ajouter d'autre scènes, alors elles devront
			//être ajoutées ici
			switch (selecteurDeScene)
			{
			/*case Scene::scenes::Menu:
				sceneActive = new SceneMenu();
				break;*/
			case Scene::scenes::Niveau1:
				sceneActive = new SceneNiveau();
				break;
			}

			if (sceneActive->init(&mainWin))
			{
				sceneEnRetour = sceneActive->run();
				//À la fin d'une scène, s'il y a des sauvegardes à faire
				//C'est aussi possible de les faire là.
			}
			else
			{
				//cleap-up à faire pour s'assurer  de ne pas avoir de leak
				//(malgré l'échec)
				return EXIT_FAILURE;
			}
		}
		selecteurDeScene = sceneEnRetour;
		delete sceneActive;
		sceneActive = nullptr;
	}
}

bool Game::init()
{
	return true;
}

void Game::getInputs()
{
	//On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
	while (mainWin.pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
		{
			mainWin.close();
		}
	}
}

void Game::update()
{

}

void Game::draw()
{
	//Toujours important d'effacer l'écran précédent
	mainWin.clear();

	mainWin.display();
}