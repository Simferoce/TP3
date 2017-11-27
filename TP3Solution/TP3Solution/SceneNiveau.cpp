#include "SceneNiveau.h"

SceneNiveau::SceneNiveau() 
{
	isRunning = true;
}
SceneNiveau::~SceneNiveau()
{
	delete joueur;
}

Scene::scenes SceneNiveau::run()
{
	while(isRunning)
	{
		getInputs();
		update();
		draw();
	}
	return transitionVersScene;
}
void SceneNiveau::draw()
{
	mainWin->clear();
	mainWin->draw(ecranNiveau);
	mainWin->draw(*joueur);
	
	mainWin->display();
}

void SceneNiveau::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fenêtre ne mettrait pas nécessairement 
			//fin à l'application
			isRunning = false;
			transitionVersScene = scenes::Niveau1;
		}
		else if(event.type == Event::KeyPressed)
		{
			inputKeys[event.key.code] = true;
		}
		else if (event.type == Event::KeyReleased)
		{
			inputKeys[event.key.code] = false;
		}
	}
}
bool SceneNiveau::init(RenderWindow * const window)
{
	mainWin = window;
	if (!Joueur::initTexture())
		return false;
	if (!ecranNiveauT.loadFromFile("Ressources\\Background\\Niveau.jpg"))
		return false;	
	joueur = new Joueur();
	ecranNiveau.setTexture(ecranNiveauT);
	ecranNiveau.setOrigin(0, 0);

	return true;
}
void SceneNiveau::update()
{
	
}








