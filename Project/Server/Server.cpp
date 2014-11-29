#include <iostream>

#include "Server.h"

Server::Server()
{
	// we want winsock version 1.1
	WORD sockVersion = MAKEWORD(1, 1);

	// load up winsock
	WSADATA wsaData;
	WSAStartup(sockVersion, &wsaData);

	// create the listening socket
	if ((listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		std::cout << "Failed to create listening socket." << std::endl;
		return;
	}

	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = INADDR_ANY;
	serverInfo.sin_port = htons(8888);

	// bind the socket to our local server address
	if (bind(listeningSocket, (LPSOCKADDR)&serverInfo, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		std::cout << "Failed to bind listening socket to local server address." << std::endl;
		return;
	}

	if (listen(listeningSocket, 10) == SOCKET_ERROR)
	// up to 10 connections may wait at any one time to be accepted
	{
		std::cout << "Failed to listen for connecting clients." << std::endl;
		return;
	}

	std::cout << "Waiting for client connection..." << std::endl;

	// wait for a client
	if ((clientSocket = accept(listeningSocket, NULL, NULL)) == INVALID_SOCKET)
	{
		std::cout << "Failed to accept client connection." << std::endl;
		return;
	}

	std::string playerName = readData();
	std::cout << "Player \"" << playerName.c_str() << "\" connected." << std::endl;

	char anykey;
	std::cin >> anykey;
}

Server::~Server()
{
	// close sockets
	closesocket(clientSocket);
	closesocket(listeningSocket);

	// shutdown winsock
	WSACleanup();
}

std::string Server::readData()
{
	std::string data;
	char buffer;
	
	while (true)
	{
		int bytesReceived = recv(clientSocket, &buffer, 1, 0);
		
		if (bytesReceived <= 0)
			return "";
		
		if (buffer == '\n')
			return data;
		else
			data.push_back(buffer);
	}
}