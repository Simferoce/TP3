#pragma once
#include "../StructuresDonnees/list.hpp"
#include "Projectile.h"
#include "Enemy.h"
#include "Joueur.h"

class INiveau
{
public:
	INiveau(){};
	virtual StructuresDonnees::list<Projectile*>& GetAllProjectiles() = 0;
	virtual StructuresDonnees::list<Enemy*>& GetAllEnemies() = 0;
	virtual const Joueur& GetPlayer() const = 0;
	virtual const FloatRect GetBounds() const = 0;
	virtual ~INiveau() = default;
};
