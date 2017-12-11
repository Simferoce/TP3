#include "FabriqueBonus.h"
#include "Bouclier.hpp"
#include "ArmeChargee.h"

FabriqueBonus::FabriqueBonus()
{
}

Bonus* FabriqueBonus::FabriquerUnBonus(Bonus::BonusType bonus, Vector2f pos)
{
	Bonus* nouveauBonus = nullptr;
	switch(bonus)
	{
	case Bonus::BouclierVert:
		nouveauBonus = new Bouclier(rand() % 3+1, Bonus::BouclierVert, pos,false);
		break;
	case Bonus::BouclierJaune:
		nouveauBonus = new Bouclier(rand() % 3+1, Bonus::BouclierJaune, pos, false);
		break;
	case Bonus::BouclierRouge:
		nouveauBonus = new Bouclier(rand() % 3 + 1, Bonus::BouclierRouge, pos, false);
		break;
	case Bonus::ArmeSpecialeShotgun:
		nouveauBonus = new Bouclier(rand() % 3 + 1, Bonus::BouclierVert, pos, false);
		break;
	case Bonus::ArmeSpecialeRayonLaser:
		nouveauBonus = new Bouclier(rand() % 3 + 1, Bonus::BouclierVert, pos, false);
		break;
	case Bonus::ArmeSpecialeSurpuissante:
		nouveauBonus = new ArmeChargee();
		break;
	default:
		break;
	}
	return  nouveauBonus;
}



