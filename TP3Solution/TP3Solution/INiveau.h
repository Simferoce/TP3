#pragma once
#include "../StructuresDonnees/list.hpp"
#include "Projectile.hpp"
#include "Enemy.h"
#include "Joueur.h"

class INiveau
{
public:
	INiveau(){};
	virtual const StructuresDonnees::list<Projectile*>& GetAllProjectiles() const = 0;
	virtual const StructuresDonnees::list<Enemy*>& GetAllEnemies() const = 0;
	virtual const Joueur& GetPlayer() const = 0;
	virtual const FloatRect GetBounds() const = 0;
	virtual ~INiveau() = default;
};
