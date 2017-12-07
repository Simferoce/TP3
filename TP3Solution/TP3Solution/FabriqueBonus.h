#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include "Bonus.h"

using namespace sf;

class FabriqueBonus :
	public Sprite
{
public:
	FabriqueBonus();
	static Bonus* FabriquerUnBonus(Bonus::BonusType bonus, Vector2f pos);
	
};
