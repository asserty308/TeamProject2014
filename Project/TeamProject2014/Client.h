#pragma once

#include <winsock.h>
#include <iostream>

// check out http://johnnie.jerrata.com/winsocktutorial/

class Client
{
	private:
		SOCKET serverSocket;
		char package[256];
		char receivedPackage[256];
		
		std::string readData();

	public:
		Client();
		~Client();

		void update();

		void setPackage(char* data, int size);
};