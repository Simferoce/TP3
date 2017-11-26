#include "Game.h"
#include <vld.h>
#include "../StructuresDonnees/queue.hpp"

int main()
{
	StructuresDonnees::Queue<int> test;
	test.push(1);
	test.push(2);
	test.pop();
	Game game;
	return game.run();
}
