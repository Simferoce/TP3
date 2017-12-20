#include "FabriqueBonus.h"
#include "Bouclier.hpp"
#include "ArmeChargee.h"
#include "ArmeFusilAPompe.h"
#include "ArmeLaserPercant.h"
#include "BombeExplosive.h"
#include "MultiplicateurXp.h"
#include "BombeElectrique.h"

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
		nouveauBonus = new ArmeFusilAPompe(pos);
		break;
	case Bonus::ArmeSpecialeRayonLaser:
		nouveauBonus = new ArmeLaserPercant(pos);
		break;
	case Bonus::ArmeSpecialeSurpuissante:
		nouveauBonus = new ArmeChargee(pos);
		break;
	case Bonus::BombeExplosive:
		nouveauBonus = new BombeExplosive(pos);
		break;
	case Bonus::BombeElectromagnetique:
		nouveauBonus = new BombeElectrique(pos);
		break;
	case Bonus::MultiplicateurDePoints:
		nouveauBonus = new MultiplicateurXp(pos);
		break;
	default:
		break;
	}
	return  nouveauBonus;
}



