#include "Game.h"
#include <vld.h>
#include "../StructuresDonnees/list.hpp"

int main()
{
	StructuresDonnees::list<int> test;
	test.assign(1, 1);
	Game game;
	return game.run();
}
