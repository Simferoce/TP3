#include "SceneNiveau.h"
#include "ProjectileBase.h"
#include "Transporter.h"
#include "Kamikaze.h"
#include "ProjectileCharge.h"

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
	joueur->Draw(*mainWin);
	for (Projectile* projectile : projectiles)
		projectile->Draw(*mainWin);
	for (Enemy* enemy : enemies)
		enemy->Draw(*mainWin);
	for (int i = 0; i < nbreEnemyNext; i++)
		mainWin->draw(nextEnemy[i]);
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
	spaceReleased = false;
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
		if (event.key.code == Keyboard::Escape)
		{
			isRunning = false;
			transitionVersScene = scenes::Titre; // À changer???
		}
		else if(event.type == Event::KeyPressed)
		{
			inputKeys[event.key.code] = true;
		}
		else if (event.type == Event::KeyReleased)
		{
			if (event.key.code == Keyboard::Space)
				spaceReleased = true;
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
	if (!ProjectileCharge::initTexture())
		return false;
	if (!EnemySentinelle::initTexture())
		return false;
	if (!Transporter::initTexture())
		return false;
	if (!Kamikaze::initTexture())
		return false;
	if (!Bouclier::initTexture())
		return false;
	Enemy* initEnemy = new EnemySentinelle();
	initEnemy->setPosition(400, 400);
	Enemy* initEnemy2 = new Transporter();
	initEnemy2->setPosition(400, 400);
	Enemy* initEnemy3 = new Kamikaze();
	initEnemy3->setPosition(400, 400);
	enemiesQueue.push_back(EnemiesHolder(initEnemy, sf::milliseconds(2000)));
	enemiesQueue.push_back(EnemiesHolder(initEnemy2, sf::milliseconds(2000)));
	enemiesQueue.push_back(EnemiesHolder(initEnemy3, sf::milliseconds(2000)));
	joueur = new Joueur();
	joueur->setPosition(32, mainWin->getSize().y / 2);
	joueur->AjouterArme(new ArmeChargee());
	vieJoueur.setFont(font);
	vieJoueur.setString("Vie joueur: " + std::to_string(joueur->GetVie()));
	vieJoueur.setPosition(0, 0);
	ecranNiveau.setTexture(ecranNiveauT);
	ecranNiveau.setOrigin(0, 0);
	ecranNiveau2.setTexture(ecranNiveauT);
	ecranNiveau2.setOrigin(0, 0);
	ecranNiveau2.setPosition(ecranNiveau.getGlobalBounds().width, 0);
	for(int j = 0; j < nbreEnemyNext; j++)
	{
		nextEnemy.push_back(Sprite());
	}
	for(int i = 0; i < enemiesQueue.size() && i < nbreEnemyNext; ++i)
	{
		nextEnemy[i].setTexture(*enemiesQueue[i].enemyInWaiting->getTexture());
		nextEnemy[i].setTextureRect(enemiesQueue[i].enemyInWaiting->getTextureRect());
		nextEnemy[i].setPosition(posXNextEnemy + i*distanceNextEnemy, posYNextEnemy);
	}
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
	ecranNiveau.move(-vitesseDeBaseBackground, 0);
	ecranNiveau2.move(-vitesseDeBaseBackground, 0);
	if (ecranNiveau.getPosition().x + ecranNiveau.getGlobalBounds().width < 0)
		ecranNiveau.setPosition(ecranNiveau.getGlobalBounds().width, 0);
	if (ecranNiveau2.getPosition().x + ecranNiveau2.getGlobalBounds().width < 0)
		ecranNiveau2.setPosition(ecranNiveau2.getGlobalBounds().width, 0);
	if (inputKeys[Keyboard::Space])
		joueur->chargerArme();
	if (((joueur->GetArmeType() != Arme::ArmeType::Charger && inputKeys[Keyboard::Space])
		|| (joueur->GetArmeType() == Arme::ArmeType::Charger && spaceReleased)) && joueur->CanFire())
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
		enemiesQueue.pop_front();
		nextEnemy.pop_front();
		for (int i = 0; i < enemiesQueue.size() && i < nbreEnemyNext; ++i)
		{
			nextEnemy[i].setTexture(*enemiesQueue[i].enemyInWaiting->getTexture());
			nextEnemy[i].setTextureRect(enemiesQueue[i].enemyInWaiting->getTextureRect());
			nextEnemy[i].setPosition(posXNextEnemy + i*distanceNextEnemy, posYNextEnemy);
		}
		lastEnemySpawn = enemiesSpawnClock.getElapsedTime();
	}
	for (auto iter = enemies.begin(); iter != enemies.end();)
	{
		Personnage::ElementToAdd elementToAdd = (*iter)->Update(*this);
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
		if(joueur->getGlobalBounds().intersects((*iter)->getGlobalBounds()))
		{
			joueur->Collisionner(*(*iter));
			(*iter)->Collisionner(*joueur);
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

	if(joueur->IsDead())
	{
		isRunning = false;
		transitionVersScene = GameOver;
	}
}








