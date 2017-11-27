#include "SceneNiveau.h"

SceneNiveau::SceneNiveau() 
{
	isRunning = true;
}
SceneNiveau::~SceneNiveau()
{

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
	mainWin->display();
}

void SceneNiveau::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		//x sur la fen�tre
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fen�tre ne mettrait pas n�cessairement 
			//fin � l'application
			isRunning = false;
			transitionVersScene = scenes::Niveau1;
		}
	}
}
bool SceneNiveau::init(RenderWindow * const window)
{
	mainWin = window;

	if (!ecranNiveauT.loadFromFile("Ressources\\Background\\Niveau.jpg"))
		return false;	

	ecranNiveau.setTexture(ecranNiveauT);
	ecranNiveau.setOrigin(0, 0);

	return true;
}
void SceneNiveau::update()
{
	
}








