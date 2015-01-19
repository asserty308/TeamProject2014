#pragma once

#include <map>
#include <vector>
#include <winsock2.h>

// check out http://johnnie.jerrata.com/winsocktutorial/


#define MAX_PLAYERS 2
#define BUFLEN 512


class Server
{
	private:
		SOCKET listeningSocket;

		//<port / ip-Address, PlayerID>
		std::map<unsigned int, unsigned int> playerID;
		//<playerID, adress>
		std::map<unsigned int, sockaddr_in> playerClientInfo;

		std::vector<unsigned int> playerIDsFromPackagesReceived;

		char* returnPackage;


		void readData();
		void tiePackage(unsigned int id, char* data);
		void distributePackage(unsigned int receiverID, sockaddr_in& clientInfo);

	public:
		Server();
		~Server();

};