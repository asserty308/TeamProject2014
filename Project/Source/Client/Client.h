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

	sockaddr_in serverInfo;
	SOCKET s;
	char *data;

public:
	Client();
	~Client();

	bool sendToServer(std::string data);
	bool sendToServer(char* data, int size);

	void update();
};