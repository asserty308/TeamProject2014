#pragma once

#include <iostream>
#include <winsock2.h>

#define BUFLEN 512


// check out http://johnnie.jerrata.com/winsocktutorial/

class Client
{
	private:

		//The package that will be sent to the server
		char package[BUFLEN];
		//The package that will be received from the server
		char receivedPackage[BUFLEN];
		//The package that will be received from the server upon first contact
		char initPackage[BUFLEN];
		
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

		char* getInitPackage(){
			return initPackage;
		}
};