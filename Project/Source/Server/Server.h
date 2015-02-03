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

	std::vector<PlayerInfo*> players;

	//<port / ip-Address, PlayerID>
	//std::map<unsigned int, unsigned int> playerID;
	//<playerID, adress>
	//std::map<unsigned int, sockaddr_in> playerClientInfo;
	//std::vector<unsigned int> playerIDsFromPackagesReceived;

	//The spawnpoints that are available
	//std::stack<std::tuple<float, float>> spawnPoints;

public:
	Server();
	~Server();

	int getMaxPlayers();
	int getTickrate();

	bool sendToClient(PlayerInfo player, std::string data);
	bool sendToClient(PlayerInfo player, char* data, int size);
	void update();
};