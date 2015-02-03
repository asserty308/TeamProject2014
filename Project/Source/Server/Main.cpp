#include <iostream>
#include <SDL.h>

#include "Server.h"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_TIMER) != 0)
	{
		std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return -1;
	}

	std::cout << "Alpha Strike Server" << std::endl << std::endl;

	Server *server = new Server();

	std::cout << std::endl << "Waiting for " << server->getMaxPlayers() << " players to connect..." << std::endl << std::endl;

	unsigned int startTime, endTime, workTime;
	unsigned int cycleLength = 1000 / server->getTickrate();

	while (true)
	{
		startTime = SDL_GetTicks();

		server->update();

		endTime = SDL_GetTicks();

		workTime = endTime - startTime;

		if (workTime < cycleLength)
			SDL_Delay(cycleLength - workTime);
		else
			std::cout << "Server is stalling (max cycle: " << cycleLength << "ms time taken: " << workTime << "ms)." << std::endl;
	}

	delete server;

	SDL_Quit();

	return 0;
}