#include "Game.h"
#include <vld.h>
#include "../StructuresDonnees/queue.hpp"

int main()
{
	srand(time(NULL));
	Game game;
	return game.run();
}
