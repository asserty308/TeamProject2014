#pragma once

#include <winsock2.h>

#define BUFLEN 512

// check out http://johnnie.jerrata.com/winsocktutorial/

class Client
{
	private:
		//SOCKET serverSocket;
		sockaddr_in serverInfo;
		SOCKET clientSocket;

	public:
		Client();
		~Client();
};