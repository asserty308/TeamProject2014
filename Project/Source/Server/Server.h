#pragma once

#include <map>
#include <vector>
#include <stack>
#include <tuple>
#include <winsock2.h>

#include "PlayerInfo.hpp"

// check out http://johnnie.jerrata.com/winsocktutorial/

#define BUFLEN 128

enum ServerState
{
	ServerState_Waiting,
	ServerState_Ingame
};

class Server
{
private:
	SOCKET s;
	char *data;
	ServerState state;

	int maxPlayers, port, tickrate;
	int connectedPlayers;
	int readyPlayers; // number of players which have acknowledged the start packet

	std::vector<PlayerInfo*> players;

public:
	Server();
	~Server();

	int getMaxPlayers();
	int getTickrate();

	bool sendToClient(PlayerInfo player, std::string data);
	bool sendToClient(PlayerInfo player, char* data, int size);
	void update();
};