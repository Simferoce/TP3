#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

/// <summary>
/// La classe g�n�rique qui servira de base pour toutes les autres scenes.
/// Mika - 1640194
/// </summary>
class Scene
{
public: 
	enum scenes{Titre, Niveau1, GameOver ,Fin};
	virtual ~Scene() {};

	// M�thode de qui d�bute l'utilisation d'une scene
	virtual scenes run() = 0;

	//La boucle de jeu est maintenant g�r�e par la sc�ne
	virtual bool init(RenderWindow * const window) = 0;
	virtual void getInputs() = 0; // Les imputs du joueurs
	virtual void update() = 0; // Mise � jour de la sc�ne
	virtual void draw() = 0; // On dessine tous les �l�ments possibles

protected:
	RenderWindow *mainWin; // La fen�tre principale.
	Event event; // Garde en m�moire les interaction du joueur.
	View vueDuJeu; // La vue du jeu
	
	// Dimention de la vue
	const int LONGUEUR_VUE = 1280;
	const int LARGEUR_VUE = 720;


	/*Utile ???*/
	//// Dimention du monde
	//const int LONGUER_MONDE = 12800;
	//const int LARGEUR_MONDE = 7200;

	//// Limites de la vue
	//const int MIN_VUE_X = LONGUEUR_VUE / 2;
	//const int MAX_VUE_X = LONGUER_MONDE - MIN_VUE_X;
	//const int MIN_VUE_Y = LARGEUR_VUE / 2;
	//const int MAX_VUE_Y = LARGEUR_MONDE - MIN_VUE_Y;

	scenes transitionVersScene; // On change la prochaine sc�ne selon celle o� on devrait �tre rendu.
	bool isRunning; // S'il y a une interruption, on change de sc�ne et on arr�te le programme.
};