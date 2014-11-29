#pragma once

#include <winsock.h>

// check out http://johnnie.jerrata.com/winsocktutorial/

class Server
{
	private:
		SOCKET listeningSocket;
		SOCKET clientSocket;

		std::string readData();

	public:
		Server();
		~Server();
};