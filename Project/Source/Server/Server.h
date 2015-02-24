#pragma once

#include <map>
#include <vector>
#include <stack>
#include <tuple>
#include <winsock2.h>

#include "PlayerInfo.hpp"

// check out http://johnnie.jerrata.com/winsocktutorial/

#define BUFLEN 160

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

	int bestOfX;
	int mapID;

	bool gameOver;

	std::vector<PlayerInfo*> players;
	std::vector<PlayerInfo*> finishedPlayers;

	void handleIncomingTraffic(std::string packet, sockaddr_in clientInfo);
	void handleOutgoingTraffic();

public:
	Server();
	~Server();

	int getMaxPlayers();
	int getTickrate();

	bool sendToClient(PlayerInfo player, std::string data);
	bool sendToClient(PlayerInfo player, char* data, int size);
	bool sendToAllClients(char* data, int size);

	bool update();
};