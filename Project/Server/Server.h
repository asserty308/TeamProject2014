#pragma once

#include <winsock.h>

// check out http://johnnie.jerrata.com/winsocktutorial/

#define MAX_PLAYERS 4

class Server
{
	private:
		SOCKET listeningSocket;
		SOCKET clientSocket[MAX_PLAYERS];

		std::string readData(int socket);

	public:
		Server();
		~Server();
};