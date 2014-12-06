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

	/*if (listen(listeningSocket, MAX_PLAYERS) == SOCKET_ERROR)
	// up to MAX_PLAYERS connections may wait at any one time to be accepted
	{
		std::cout << "Failed to listen for connecting clients." << std::endl;
		return;
	}*/

	/*for (int socket = 0; socket < MAX_PLAYERS; ++socket)
	{
		std::cout << "Waiting for client " << socket << " to connect..." << std::endl;

		// wait for a client
		if ((clientSocket[socket] = accept(listeningSocket, NULL, NULL)) == INVALID_SOCKET)
		{
			std::cout << "Failed to accept client connection." << std::endl;
			return;
		}

		std::string playerName = readData(socket);
		std::cout << "Player \"" << playerName.c_str() << "\" (ID: " << socket << ") connected." << std::endl;
	}*/

	readData();

	char anykey;
	std::cin >> anykey;
}

Server::~Server()
{
	// close sockets

	closesocket(listeningSocket);

	/*for (int socket = 0; socket < MAX_PLAYERS; ++socket)
		closesocket(clientSocket[socket]);*/
	

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
		
		std::string playerName(buffer);
		std::cout << "Player \"" << playerName.c_str() << "\" (ID: " << "0" << ") connected." << std::endl;
	}
}