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
	delete enemyTest;
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
	mainWin->draw(*enemyTest);
	mainWin->display();
}

void SceneNiveau::getInputs()
{
	srand(NULL);
	while (mainWin->pollEvent(event))
	{
		//x sur la fen�tre
		if (event.type == Event::Closed)
		{
			//fin � l'application
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
	if (!EnemySentinelle::initTexture())
		return false;
	enemyTest = new EnemySentinelle();
	enemyTest->setPosition(mainWin->getSize().x/2, mainWin->getSize().y / 2);
	joueur = new Joueur();
	joueur->setPosition(32, mainWin->getSize().y / 2);
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
	if (inputKeys[Keyboard::Space] && joueur->CanFire())
	{
		StructuresDonnees::list<Projectile*>* projectilesTemp = joueur->Fire();
		projectiles.splice(*projectilesTemp, projectiles.begin());
		delete projectilesTemp;
	}
	if (inputKeys[Keyboard::E]) joueur->nextWeapon();
	if (inputKeys[Keyboard::Q]) joueur->previousWeapon();
	for (Projectile* projectile : projectiles)
		projectile->Update();
}








