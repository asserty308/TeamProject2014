#pragma once

#include <iostream>
#include <winsock2.h>
#include "Game.hpp"

#define BUFLEN 128


// check out http://johnnie.jerrata.com/winsocktutorial/
class Game;

class Client
{
	private:

		//The package that will be sent to the server
		char package[BUFLEN];
		//The package that will be received from the server
		char* receivedPackage;
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

		void init(int numberOfPlayers);

		char* getReceivedPackage(){
			return receivedPackage;
		}

		char* getInitPackage(){
			return initPackage;
		}
};