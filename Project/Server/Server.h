#pragma once

#include <map>
#include <vector>
#include <stack>
#include <tuple>
#include <winsock2.h>

// check out http://johnnie.jerrata.com/winsocktutorial/


#define MAX_PLAYERS 2
#define BUFLEN 128


class Server
{
	private:
		SOCKET listeningSocket;
		SOCKET respondingSocket;

		//<port / ip-Address, PlayerID>
		std::map<unsigned int, unsigned int> playerID;
		//<playerID, adress>
		std::map<unsigned int, sockaddr_in> playerClientInfo;

		std::vector<unsigned int> playerIDsFromPackagesReceived;

		char* returnPackage;


		void readData();
		void tiePackage(unsigned int id, char* data);
		void distributePackage(unsigned int receiverID, sockaddr_in& clientInfo);

		//The spawnpoints that are available
		std::stack<std::tuple<float, float>> spawnPoints;

	public:
		Server();
		~Server();

};