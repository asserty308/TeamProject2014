#pragma once

#include <iostream>
#include <winsock2.h>

#define BUFLEN 512


// check out http://johnnie.jerrata.com/winsocktutorial/

class Client
{
	private:

		char package[BUFLEN];
		char receivedPackage[BUFLEN];
		
		//SOCKET serverSocket;
		sockaddr_in serverInfo;
		SOCKET clientSocket;


	public:
		Client();
		~Client();

		void update();

		void setPackage(char* data, int size);

		char* getReceivedPackage(){
			return receivedPackage;
		}
};