#include "SceneNiveau.h"
#include "ProjectileBase.h"
#include "Transporter.h"

const float SceneNiveau::vitesseDeBaseBackground = 5.0f;
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
	for (int i = 0; i < enemiesQueue.size(); i++)
		delete enemiesQueue[i].enemyInWaiting;
	for (Enemy* enemy : enemies)
	{
		delete enemy;
	}
	enemies.clear();
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
	mainWin->draw(ecranNiveau2);
	mainWin->draw(*joueur);
	for (Projectile* projectile : projectiles)
		mainWin->draw(*projectile);

	for (Enemy* enemy : enemies)
		mainWin->draw(*enemy);
	mainWin->draw(vieJoueur);
	mainWin->display();
}

const StructuresDonnees::list<Projectile*>& SceneNiveau::GetAllProjectiles() const
{
	return projectiles;
}

const StructuresDonnees::list<Enemy*>& SceneNiveau::GetAllEnemies() const
{
	return enemies;
}

const Joueur & SceneNiveau::GetPlayer() const
{
	return *joueur;
}

const FloatRect SceneNiveau::GetBounds() const
{
	return FloatRect(Vector2f(0,0), (Vector2f)mainWin->getSize());
}

void SceneNiveau::getInputs()
{
	srand(NULL);
	while (mainWin->pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
		{
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
	if (!font.loadFromFile("Ressources/Fonts/PressStart2P-Regular.ttf"))
		return false;
	if (!ArmeBase::initTexture())
		return false;
	if (!Joueur::initTexture())
		return false;
	if (!ProjectileBase::initTexture())
		return false;
	if (!EnemySentinelle::initTexture())
		return false;
	if (!Transporter::initTexture())
		return false;
	Enemy* initEnemy = new EnemySentinelle();
	initEnemy->setPosition(400, 400);
	enemiesQueue.push_back(EnemiesHolder(initEnemy, sf::milliseconds(1000)));
	joueur = new Joueur();
	joueur->setPosition(32, mainWin->getSize().y / 2);
	vieJoueur.setFont(font);
	vieJoueur.setString("Vie joueur: " + std::to_string(joueur->GetVie()));
	vieJoueur.setPosition(0, 0);
	ecranNiveau.setTexture(ecranNiveauT);
	ecranNiveau.setOrigin(0, 0);
	ecranNiveau2.setTexture(ecranNiveauT);
	ecranNiveau2.setOrigin(0, 0);
	ecranNiveau2.setPosition(ecranNiveau.getGlobalBounds().width, 0);
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
	if(bitsMask == 8 || bitsMask == 9 || bitsMask == 12)
	{
		ecranNiveau.move(-(vitesseDeBaseBackground + joueur->GetVitesse()), 0);
		ecranNiveau2.move(-(vitesseDeBaseBackground + joueur->GetVitesse()), 0);
	}
	else if (bitsMask == 2 || bitsMask == 3 || bitsMask == 6)
	{
		ecranNiveau.move(-(joueur->GetVitesseRecule() - vitesseDeBaseBackground), 0);
		ecranNiveau2.move(-(joueur->GetVitesseRecule() - vitesseDeBaseBackground), 0);
	}
	else
	{
		ecranNiveau.move(-vitesseDeBaseBackground, 0);
		ecranNiveau2.move(-vitesseDeBaseBackground, 0);
	}
	if (ecranNiveau.getPosition().x + ecranNiveau.getGlobalBounds().width < 0)
		ecranNiveau.setPosition(ecranNiveau.getGlobalBounds().width, 0);
	if (ecranNiveau2.getPosition().x + ecranNiveau2.getGlobalBounds().width < 0)
		ecranNiveau2.setPosition(ecranNiveau2.getGlobalBounds().width, 0);
	if (inputKeys[Keyboard::Space] && joueur->CanFire())
	{
		StructuresDonnees::list<Projectile*>* projectilesTemp = joueur->Fire();
		projectiles.splice(*projectilesTemp, projectiles.begin());
		delete projectilesTemp;
	}
	if (inputKeys[Keyboard::E]) joueur->nextWeapon();
	if (inputKeys[Keyboard::Q]) joueur->previousWeapon();
	if(!enemiesQueue.empty() && enemiesSpawnClock.getElapsedTime() - enemiesQueue.front().timeToWait > lastEnemySpawn)
	{
		enemies.push_back(enemiesQueue.front().enemyInWaiting);
		enemiesQueue.pop_back();
		lastEnemySpawn = enemiesSpawnClock.getElapsedTime();
	}
	for (auto iter = enemies.begin(); iter != enemies.end();)
	{
		Enemy::ElementToAdd elementToAdd = (*iter)->Update(*this);
		if (elementToAdd.hasElementToAdd)
		{
			if (!elementToAdd.projectiles.is_empty())
				projectiles.splice(elementToAdd.projectiles, projectiles.begin());
			if (!elementToAdd.enemies.is_empty())
				enemies.splice(elementToAdd.enemies, enemies.begin());
		}
		for (auto iterP = projectiles.begin(); iterP != projectiles.end();)
		{
			if((*iterP)->GetType() == TypeWeapon::Player && (*iterP)->getGlobalBounds().intersects((*iter)->getGlobalBounds()))
			{
				(*iter)->RecoitDommage((*iterP)->GetType(), (*iterP)->GetDommage());
				auto temp = iterP;
				++iterP;
				delete *temp;
				projectiles.erase(temp);
			}
			else
			{
				++iterP;
			}
		}
		if((*iter)->IsDead())
		{
			auto temp = iter;
			++iter;
			delete *temp;
			enemies.erase(temp);
		}
		else
		{
			++iter;
		}
	}
	for (auto iterP = projectiles.begin(); iterP != projectiles.end();)
	{
		if ((*iterP)->GetType() != TypeWeapon::Player && (*iterP)->getGlobalBounds().intersects(joueur->getGlobalBounds()))
		{
			joueur->RecoitDommage((*iterP)->GetType(), (*iterP)->GetDommage());
			auto temp = iterP;
			++iterP;
			delete *temp;
			projectiles.erase(temp);
		}
		else
		{
			++iterP;
		}
	}
	for (Projectile* projectile : projectiles)
		projectile->Update();
	vieJoueur.setString("Vie joueur: " + std::to_string(joueur->GetVie()));
}








