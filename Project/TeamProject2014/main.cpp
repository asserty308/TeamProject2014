#include "Game.hpp"

int main(int argc, char* args[])
{
	Game game;
	
	game.init();
	game.eventLoop();
	game.cleanup();

	return 0;
}