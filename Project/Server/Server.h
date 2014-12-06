#pragma once

#include <winsock2.h>

// check out http://johnnie.jerrata.com/winsocktutorial/

#define MAX_PLAYERS 4
#define BUFLEN 512

class Server
{
	private:
		SOCKET listeningSocket;

		void readData();

	public:
		Server();
		~Server();
};