#include "Game.h"
#include <vld.h>
#include "../StructuresDonnees/list.h"

int main()
{
	StructuresDonnees::list<int> test;
	test.push_back(1);
	test.push_back(1);
	Game game;
	return game.run();
}
