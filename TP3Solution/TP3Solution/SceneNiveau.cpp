#include "SceneNiveau.h"
#include "ProjectileBase.h"

SceneNiveau::SceneNiveau() 
{
	isRunning = true;
}
SceneNiveau::~SceneNiveau()
{
	for (Projectile* projectile : projectiles)
	{
		delete projectile;
	}
	projectiles.clear();
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
	for (Projectile* projectile : projectiles)
		mainWin->draw(*projectile);
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
			transitionVersScene = scenes::Fin;
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
	if (!ecranNiveauT.loadFromFile("Ressources\\Background\\Niveau.jpg"))
		return false;	
	if (!ArmeBase::initTexture())
		return false;
	if (!Joueur::initTexture())
		return false;
	if (!ProjectileBase::initTexture())
		return false;
	joueur = new Joueur();
	ecranNiveau.setTexture(ecranNiveauT);
	ecranNiveau.setOrigin(0, 0);

	return true;
}
void SceneNiveau::update()
{
	int bitsMask = 0;
	if (inputKeys[Keyboard::W]) bitsMask += 1;
	if (inputKeys[Keyboard::A]) bitsMask += 2;
	if (inputKeys[Keyboard::S]) bitsMask += 4;
	if (inputKeys[Keyboard::D]) bitsMask += 8;
	joueur->Move(bitsMask,FloatRect(Vector2f(0,0),(Vector2f)mainWin->getSize()));
	if(inputKeys[Keyboard::Space] && joueur->CanFire())
	{
		StructuresDonnees::list<Projectile*>* projectilesTemp = joueur->Fire();
		projectiles.splice(*projectilesTemp, projectiles.begin());
		delete projectilesTemp;
	}
	for(Projectile* projectile : projectiles)
		projectile->Update();
}








