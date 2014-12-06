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

	if (listen(listeningSocket, MAX_PLAYERS) == SOCKET_ERROR)
	// up to MAX_PLAYERS connections may wait at any one time to be accepted
	{
		std::cout << "Failed to listen for connecting clients." << std::endl;
		return;
	}

	for (int socket = 0; socket < MAX_PLAYERS; ++socket)
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
	}

}

Server::~Server()
{
	// close sockets
	closesocket(listeningSocket);

	for (int socket = 0; socket < MAX_PLAYERS; ++socket)
		closesocket(clientSocket[socket]);
	

	// shutdown winsock
	WSACleanup();
}




bool Server::update(){

	std::string dataFrom0 = readData(0);
	//std::cout << ("Player 1 Pos: " + dataFrom0 + "\n").c_str();
	
	std::string dataFrom1 = readData(1);
	//std::cout << ("Player 2 Pos: " + dataFrom1 + "\n").c_str();

	std::string endOfTransmission = "\n";

	size_t packageSize = dataFrom0.size() + dataFrom1.size() + endOfTransmission.size();

	char* package = new char[packageSize];

	memcpy(package, dataFrom0.data(), dataFrom0.size());
	memcpy(package + dataFrom0.size(), dataFrom1.data(), dataFrom1.size());
	memcpy(package + dataFrom0.size() + dataFrom1.size(), endOfTransmission.data(), endOfTransmission.size());

	int sendBytes = 0;
	for (int i = 0; i < MAX_PLAYERS; i++){
		sendBytes = send(clientSocket[i], package, packageSize, 0);

		if (sendBytes == SOCKET_ERROR){
			printf("Could not send data from server to client %d Error: %d\n", i, WSAGetLastError());
		}
	}

	delete package;
	
	//TODO: Check if connection is lost/cancelled and if so, return false
	return true;
}


std::string Server::readData(int socket)
{
	std::string data;
	
	while (true)
	{
		char buffer;
		int bytesReceived = recv(clientSocket[socket], &buffer, 1, 0);
		
		if (bytesReceived <= 0)
			return "";
		
		if (buffer == '\n')
			return data;
		else
			data.push_back(buffer);
	}
}