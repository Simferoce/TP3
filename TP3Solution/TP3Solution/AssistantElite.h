#pragma once
#include "Assistant.h"
class AssistantElite :
	public Assistant
{
	static sf::Texture texture;
	static const std::string texturePath;
	static const int pointsVieDeBase;
	static const float vitesseDeBase;
	static Arme* GetArmeDefaut()
	{
		Arme* arme = new ArmeBase(Vector2f(0,0));
		arme->SetTempsEntreTir(sf::milliseconds(1000));
		return arme;
	}
public:
	AssistantElite();
	~AssistantElite();
	static bool initTexture();
	Personnage::ElementToModify update(INiveau& game) override;
};

