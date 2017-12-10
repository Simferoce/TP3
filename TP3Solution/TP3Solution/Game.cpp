#include "Game.h"
#include "Joueur.h"
#include "Scene.h"
#include "SceneNiveau.h"
#include "SceneTitre.h"
#include "SceneGameOver.h"

Game::Game()
{
	//On place dans le contructeur ce qui permet � la game elle-m�me de fonctionner

	mainWin.create(VideoMode(LARGEUR, HAUTEUR, 32), "Le titre de mon jeu");  // , Style::Titlebar); / , Style::FullScreen);
	view = mainWin.getDefaultView();

	//Synchonisation coordonn�e � l'�cran!  Normalement 60 frames par secondes. � faire absolument
	mainWin.setVerticalSyncEnabled(true);
	//mainWin.setFramerateLimit(60);  //�quivalent... normalement, mais pas toujours. � utiliser si la synchonisation de l'�cran fonctionne mal.
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
	//deux enums et un pointeur de scene pour faire la manipulation de sc�ne
	Scene::scenes selecteurDeScene = Scene::scenes::Titre;
	Scene::scenes sceneEnRetour;
	Scene* sceneActive = nullptr; //Pointeur de la super-classe, peut pointer sur n'imprte quelle sc�ne

	while (true)
	{
		//Seule condition de sortie de toute l'app
		if (selecteurDeScene == Scene::scenes::Fin)
		{
			return EXIT_SUCCESS;
		}
		else
		{
			//Vous allez ajouter d'autre sc�nes, alors elles devront
			//�tre ajout�es ici
			switch (selecteurDeScene)
			{
			case Scene::scenes::Titre:
				sceneActive = new SceneTitre();
				break;
			case Scene::scenes::Niveau1:
				sceneActive = new SceneNiveau();
				break;
			case Scene::scenes::GameOver:
				sceneActive = new SceneGameOver();
				break;
			case Scene::scenes::Fin: //N'est pas une scene. On ferme simplement la fen�tre
				mainWin.close();
				break;
			}

			if (sceneActive->init(&mainWin))
			{
				sceneEnRetour = sceneActive->run();
				//� la fin d'une sc�ne, s'il y a des sauvegardes � faire
				//C'est aussi possible de les faire l�.
			}
			else
			{
				//cleap-up � faire pour s'assurer  de ne pas avoir de leak
				//(malgr� l'�chec)
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
	//On passe l'�v�nement en r�f�rence et celui-ci est charg� du dernier �v�nement re�u!
	while (mainWin.pollEvent(event))
	{
		//x sur la fen�tre
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
	//Toujours important d'effacer l'�cran pr�c�dent
	mainWin.clear();

	mainWin.display();
}