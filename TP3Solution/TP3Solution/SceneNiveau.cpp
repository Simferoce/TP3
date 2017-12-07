#include "SceneNiveau.h"
#include "ProjectileBase.h"
#include "Transporter.h"
#include "Kamikaze.h"
#include "ProjectileCharge.h"
#include "Assistant.h"
#include "FabriqueBonus.h"

const float SceneNiveau::vitesseDeBaseBackground = 5.0f;
const int SceneNiveau::posXSpawner[] = { 200, 400 , 600 };
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
	for (Bonus* bonusToDelete : bonus)
	{
		delete bonusToDelete;
	}
	for (int i = 0; i < nbSpawner; i++)
		mainWin->draw(spawner[i]);
	enemies.clear();
	delete joueur;
}

Scene::scenes SceneNiveau::run()
{

	while (isRunning)
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
	for (Bonus* bonusToDraw : bonus)
		bonusToDraw->Draw(*mainWin);
	for (int i = 0; i < nbreEnemyNext; i++)
		mainWin->draw(nextEnemy[i]);
	mainWin->draw(vieJoueur);
	mainWin->draw(boucliersText);
	mainWin->draw(munitionArmes);
	mainWin->display();
}

StructuresDonnees::list<Projectile*>& SceneNiveau::GetAllProjectiles()
{
	return projectiles;
}

StructuresDonnees::list<Enemy*>& SceneNiveau::GetAllEnemies()
{
	return enemies;
}

const Joueur & SceneNiveau::GetPlayer() const
{
	return *joueur;
}

const FloatRect SceneNiveau::GetBounds() const
{
	return FloatRect(Vector2f(0, 0), (Vector2f)mainWin->getSize());
}

void SceneNiveau::getInputs()
{
	spaceReleased = false;
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
		else if (event.type == Event::KeyPressed)
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
	if (!Assistant::initTexture())
		return false;
	spawner[0].setPosition(mainWin->getSize().x - DistanceAvecLeFond, posXSpawner[0]);
	spawner[1].setPosition(mainWin->getSize().x - DistanceAvecLeFond, posXSpawner[1]);
	spawner[2].setPosition(mainWin->getSize().x - DistanceAvecLeFond, posXSpawner[2]);
	/*for(int i = 0; i < nbEnemy; i++)
	{
		const int random = rand() % nbSpawner;
		const Spawner::EnemiesEnum random2 = static_cast<Spawner::EnemiesEnum>(rand() % Spawner::EnemiesEnum::NumEnemies);
		enemiesQueue.push_back(EnemiesHolder(spawner[random].FabriquerEnemy(random2), sf::milliseconds(2000)));
	}*/
	enemiesQueue.push_back(EnemiesHolder(spawner[0].FabriquerEnemy(Spawner::AssistantEnum), sf::milliseconds(2000)));
	enemiesQueue.push_back(EnemiesHolder(spawner[0].FabriquerEnemy(Spawner::KamikazeEnum), sf::milliseconds(2000)));
	joueur = new Joueur();
	joueur->setPosition(32, mainWin->getSize().y / 2);
	joueur->AjouterArme(new ArmeChargee());
	bonus.push_back(FabriqueBonus::FabriquerUnBonus(Bonus::BouclierVert, Vector2f(LONGUEUR_VUE / 2, LARGEUR_VUE / 2)));
	vieJoueur.setFont(font);
	vieJoueur.setString("Vie joueur: " + std::to_string(joueur->GetVie()));
	vieJoueur.setPosition(0, 0);
	boucliersText.setFont(font);
	const Bouclier* bouclierActif = joueur->GetBouclier();
	if (bouclierActif != nullptr)
	{
		switch (bouclierActif->GetTypeBouclier())
		{
		case EnemyGreen:
			boucliersText.setFillColor(Color::Green);
			break;
		case EnemyRed:
			boucliersText.setFillColor(Color::Red);
			break;
		case EnemyYellow:
			boucliersText.setFillColor(Color::Yellow);
			break;
		default:
			boucliersText.setFillColor(Color::White);
			break;
		}
	}
	else
	{
		boucliersText.setFillColor(Color::White);
	}
	boucliersText.setString("Bouclier: " + std::to_string(bouclierActif != nullptr ? bouclierActif->GetVie() : 0));
	boucliersText.setPosition(vieJoueur.getPosition().x, vieJoueur.getPosition().y + vieJoueur.getCharacterSize());
	munitionArmes.setFont(font);
	munitionArmes.setString(joueur->GetArme()->GetNomArme() + ": " + (joueur->GetArme()->GetMunition() == -1 ? "infini" : std::to_string(joueur->GetArme()->GetMunition())));
	munitionArmes.setPosition(0, mainWin->getSize().y - munitionArmes.getCharacterSize());
	ecranNiveau.setTexture(ecranNiveauT);
	ecranNiveau.setOrigin(0, 0);
	ecranNiveau2.setTexture(ecranNiveauT);
	ecranNiveau2.setOrigin(0, 0);
	ecranNiveau2.setPosition(ecranNiveau.getGlobalBounds().width, 0);
	for (int i = 0; i < enemiesQueue.size() && i < nbreEnemyNext; ++i)
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
	joueur->Move(bitsMask, FloatRect(Vector2f(0, 0), (Vector2f)mainWin->getSize()));
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
	if (!enemiesQueue.empty() && enemiesSpawnClock.getElapsedTime() - enemiesQueue.front().timeToWait > lastEnemySpawn)
	{
		enemies.push_back(enemiesQueue.front().enemyInWaiting);
		enemiesQueue.pop_front();
		for (int i = 0; i < nbreEnemyNext; ++i)
		{
			if (enemiesQueue.size() > i)
			{
				nextEnemy[i].setTexture(*enemiesQueue[i].enemyInWaiting->getTexture());
				nextEnemy[i].setTextureRect(enemiesQueue[i].enemyInWaiting->getTextureRect());
				nextEnemy[i].setPosition(posXNextEnemy + i*distanceNextEnemy, posYNextEnemy);
			}
			else
			{
				nextEnemy[i].setTextureRect(IntRect(0, 0, 0, 0));
			}
		}
		lastEnemySpawn = enemiesSpawnClock.getElapsedTime();
	}
	for (auto iter = enemies.begin(); iter != enemies.end();)
	{
		Personnage::ElementToModify elementToAdd = (*iter)->Update(*this);
		if (elementToAdd.hasElementToModify)
		{
			if (!elementToAdd.projectilesToAdd.is_empty())
				projectiles.splice(elementToAdd.projectilesToAdd, projectiles.begin());
			if (!elementToAdd.enemiesToAdd.is_empty())
				enemies.splice(elementToAdd.enemiesToAdd, enemies.begin());
			if (elementToAdd.deleteObjectReturning)
			{
				auto temp = iter;
				++iter;
				delete *temp;
				enemies.erase(temp);
				if (iter == enemies.end())
					break;
			}
			else if (elementToAdd.removeObject)
			{
				auto temp = iter;
				++iter;
				enemies.erase(temp);
				if (iter == enemies.end())
					break;
			}
		}
		for (auto iterP = projectiles.begin(); iterP != projectiles.end();)
		{
			if ((*iterP)->GetType() == TypeWeapon::Player && (*iterP)->getGlobalBounds().intersects((*iter)->getGlobalBounds()))
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
		for (auto iterP = projectiles.begin(); iterP != projectiles.end();)
		{
			bool destroyedProjectile = false;
			for (auto iterC = (*iter)->GetComposites().begin(); iterC != (*iter)->GetComposites().end();)
			{
				if (Enemy* enemy = dynamic_cast<Enemy*>(*iterC))
				{
					if ((*iterP)->GetType() == TypeWeapon::Player && (*iterP)->getGlobalBounds().intersects(enemy->getGlobalBounds()))
					{
						enemy->RecoitDommage((*iterP)->GetType(), (*iterP)->GetDommage());
						auto temp = iterP;
						++iterP;
						destroyedProjectile = true;
						delete *temp;
						projectiles.erase(temp);
						if(enemy->IsDead())
						{
							delete *iterC;
							(*iter)->GetComposites().erase(iterC);
						}
						break;
					}
					++iterC;
				}
			}
			if(!destroyedProjectile)
					++iterP;
		}
		if(joueur->getGlobalBounds().intersects((*iter)->getGlobalBounds()))
		{
			joueur->Collisionner(*(*iter));
			(*iter)->Collisionner(*joueur);
		}
		if ((*iter)->IsDead())
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
		else if ((*iterP)->getPosition().x < 0 || (*iterP)->getPosition().x > mainWin->getSize().x
			|| (*iterP)->getPosition().y < 0 || (*iterP)->getPosition().y > mainWin->getSize().y)
		{
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
	for (auto iterB = bonus.begin(); iterB != bonus.end();)
	{
		if ((*iterB)->getGlobalBounds().intersects(joueur->getGlobalBounds()))
		{
			(*iterB)->notifierTousLesObservateurs();
			joueur->AjouterBonus(*iterB);
			auto temp = iterB;
			++iterB;
			delete *temp;
			bonus.erase(temp);
		}
		else
		{
			++iterB;
		}
	}
	vieJoueur.setString("Vie joueur: " + std::to_string(joueur->GetVie()));
	boucliersText.setFont(font);
	const Bouclier* bouclierActif = joueur->GetBouclier();
	if (bouclierActif != nullptr)
	{
		switch (bouclierActif->GetTypeBouclier())
		{
		case EnemyGreen:
			boucliersText.setFillColor(Color::Green);
			break;
		case EnemyRed:
			boucliersText.setFillColor(Color::Red);
			break;
		case EnemyYellow:
			boucliersText.setFillColor(Color::Yellow);
			break;
		default:
			boucliersText.setFillColor(Color::White);
			break;
		}
	}
	else
	{
		boucliersText.setFillColor(Color::White);
	}
	boucliersText.setString("Bouclier: " + std::to_string(bouclierActif != nullptr ? bouclierActif->GetVie() : 0));
	boucliersText.setPosition(vieJoueur.getPosition().x, vieJoueur.getPosition().y + vieJoueur.getCharacterSize());
	munitionArmes.setString(joueur->GetArme()->GetNomArme() + ": " + (joueur->GetArme()->GetMunition() == -1 ? "infini" : std::to_string(joueur->GetArme()->GetMunition())));
	if (joueur->IsDead())
	{
		isRunning = false;
		transitionVersScene = GameOver;
	}
}








