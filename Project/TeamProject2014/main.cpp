#include "Game.hpp"

int main(int argc, char* args[])
{
	g_pLogfile->createLogfile();
	g_pLogfile->writeTopic("Alpha Strike", 2);

	g_pGame->init();
	g_pGame->eventLoop();
	g_pGame->cleanup();

	return 0;
}