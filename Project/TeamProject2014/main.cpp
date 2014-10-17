#include "Game.hpp"

int main(int argc, char* args[])
{
	g_pLogfile->createLogfile();
	g_pLogfile->writeTopic("Alpha Strike", 2);

	Game game;
	
	game.init();
	game.eventLoop();
	game.cleanup();

	return 0;
}