#pragma once

#include <winsock.h>

// check out http://johnnie.jerrata.com/winsocktutorial/

class Client
{
	private:
		SOCKET serverSocket;

	public:
		Client();
		~Client();
};