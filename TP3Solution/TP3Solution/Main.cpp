#include "Game.h"
#include <vld.h>
#include "../StructuresDonnees/queue.hpp"

int main()
{
	StructuresDonnees::Queue<int> test;
	test.push_back(1);
	test.push_back(2);
	test.pop_front();
	Game game;
	return game.run();
}
