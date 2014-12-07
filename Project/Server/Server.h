#pragma once

#include <map>
#include <winsock2.h>

// check out http://johnnie.jerrata.com/winsocktutorial/


#define MAX_PLAYERS 2
#define BUFLEN 512


class Server
{
	private:
		SOCKET listeningSocket;
		SOCKET respondingSocket;

		//<port / ip-Address, PlayerID>
		std::map<unsigned int, unsigned int> playerID;
		std::map<unsigned int, sockaddr_in> playerClientInfo;

		char* returnPackage;


		void readData();
		void tiePackage(unsigned int id, char* data);
		void distributePackage(unsigned int receiverID, sockaddr_in& clientInfo);

	public:
		Server();
		~Server();

};