#include <iostream>

#include "Server.h"

Server::Server()
{
	// we want winsock version 2.2
	WORD sockVersion = MAKEWORD(2, 2);

	// load up winsock
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		std::cout << "WSAStartup() error: " << WSAGetLastError() << std::endl;
		return;
	}

	// create the listening socket
	if ((listeningSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		std::cout << "Failed to create listening socket." << std::endl;
		return;
	}

	//create the responding socket
	respondingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (respondingSocket == INVALID_SOCKET)
	{
		std::cout << "Failed to create responding socket." << std::endl;
		return;
	}

	//Change socket to a non-blocking one
	u_long iMode = 1;
	if (ioctlsocket(respondingSocket, FIONBIO, &iMode) == SOCKET_ERROR){
		std::cout << "Clientsocket did not enter non-blocking mode!" << std::endl;
	}

	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = INADDR_ANY;
	serverInfo.sin_port = htons(8888);

	// bind the socket to our local server address
	if (bind(listeningSocket, (struct sockaddr*)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR)
	{
		std::cout << "Failed to bind listening socket to local server address." << std::endl;
		return;
	}

	returnPackage = new char[BUFLEN * MAX_PLAYERS];

	//TODO: Remove magic numbers and get the spawnpoints from the map!
	spawnPoints.push(std::tuple<float, float>(750.0, 50.0));
	spawnPoints.push(std::tuple<float, float>(50.0, 550.0));
	spawnPoints.push(std::tuple<float, float>(750.0, 550.0));
	spawnPoints.push(std::tuple<float, float>(50.0, 50.0));


	readData();

}

Server::~Server()
{
	// close sockets
	closesocket(listeningSocket);

	delete returnPackage;

	// shutdown winsock
	WSACleanup();
}

void Server::readData()
{
	std::string data;
	sockaddr_in clientInfo;

	int clientLen = sizeof(clientInfo);
	
	while (true)
	{
		std::cout << "\nWaiting for data..." << std::endl;
		fflush(stdout);

		char buffer[BUFLEN];

		//clear the buffer
		memset(buffer, '\0', BUFLEN);

		int bytesReceived = recvfrom(listeningSocket, buffer, BUFLEN, 0, (struct sockaddr*)&clientInfo, &clientLen);
		
		if (bytesReceived == SOCKET_ERROR)
		{
			std::cout << "recvfrom() error: " << WSAGetLastError() << std::endl;
		}
		
		//print client's details and the data received ip:port
		std::cout << "Received packet from " << inet_ntoa(clientInfo.sin_addr) << ":" << ntohs(clientInfo.sin_port) << std::endl;

		//TODO: switch from port to ip-adress when migrating from localhost to real connections!
		unsigned int idCriteria = clientInfo.sin_port;
		
		//Check if package-sender is already in our "database"
		std::map<unsigned int, unsigned int>::iterator it;
		it = playerID.find(clientInfo.sin_port);
		
		if (it == playerID.end()){
			playerID.insert(std::pair<unsigned int, unsigned int>(idCriteria, playerID.size()));
			playerClientInfo.insert(std::pair<unsigned int, sockaddr_in>(playerID.at(clientInfo.sin_port), clientInfo));

			std::string data(buffer);
			std::cout << "Player \"" << data.c_str() << "\" (ID: " << playerID[idCriteria] << ") connected." << std::endl;

			size_t bufferSize = sizeof(float)* 2;
			char* spawnPointPacket = new char[bufferSize];
			std::tuple<float, float> currentSpawn = spawnPoints.top();
			spawnPoints.pop();
			float tempBuf[2] = { std::get<0>(currentSpawn), std::get<1>(currentSpawn) };
			memcpy(spawnPointPacket, tempBuf, sizeof(float)* 2);

			if (sendto(respondingSocket, spawnPointPacket, BUFLEN, 0, (struct sockaddr*) &clientInfo, sizeof(clientInfo)) == SOCKET_ERROR){
					std::cout << "Could not send spawnpoint to client. Error: " << WSAGetLastError() << std::endl;
			}


		}

		//Here we memorize from whom we already have received a package
		std::vector<unsigned int>::iterator it2 = std::find(playerIDsFromPackagesReceived.begin(), playerIDsFromPackagesReceived.end(), playerID.at(clientInfo.sin_port));
		if (it2 == playerIDsFromPackagesReceived.end()){
			playerIDsFromPackagesReceived.push_back(playerID.at(clientInfo.sin_port));
		}

		
		tiePackage(playerID.at(idCriteria), buffer);

		//Unless we don't have received a package from every player, we won't send anything to the clients
		if (playerIDsFromPackagesReceived.size() == MAX_PLAYERS){
			for (int i = 0; i < playerClientInfo.size(); i++){
				distributePackage(i, playerClientInfo.at(i));
			}
			playerIDsFromPackagesReceived.clear();
		}
		
	}
}

void Server::tiePackage(unsigned int id, char* data){
	char* dest = returnPackage + (id * BUFLEN);
	memcpy(dest, data, BUFLEN);
}

void Server::distributePackage(unsigned int receiverID, sockaddr_in& clientInfo){
	//Only send information of the other players to a client, not its own!
	size_t bufferSize = (MAX_PLAYERS - 1) * BUFLEN;
	char* buffer = new char[bufferSize];
	int bufferOffset = 0;
	for (int i = 0; i < MAX_PLAYERS; i++){
		if (i != receiverID){
			memcpy(buffer + bufferOffset, returnPackage + (i * BUFLEN), BUFLEN);
			bufferOffset++;
		}
	}

	if (sendto(respondingSocket, buffer, bufferSize, 0, (struct sockaddr*) &clientInfo, sizeof(clientInfo)) == SOCKET_ERROR){
		std::cout << "Could not send data to client. Error: " << WSAGetLastError() << std::endl;
	}
	
	delete buffer;
}