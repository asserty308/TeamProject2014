#include <winsock.h>

#include <iostream>

// check out http://johnnie.jerrata.com/winsocktutorial/

void main()
{
	std::cout << "Alpha Strike server running..." << std::endl;

	// we want winsock version 1.1
	WORD sockVersion = MAKEWORD(1, 1);
	
	// load up winsock
	WSADATA wsaData;
	WSAStartup(sockVersion, &wsaData);

	// create the listening socket
	SOCKET listeningSocket;
	if ((listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		std::cout << "Failed to create listening socket." << std::endl;
		WSACleanup();
		return;
	}
	
	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = INADDR_ANY;
	serverInfo.sin_port = htons(8888);
	
	// bind the socket to our local server address
	if (bind(listeningSocket, (LPSOCKADDR)&serverInfo, sizeof(struct sockaddr)) == SOCKET_ERROR)
	{
		std::cout << "Failed to bind listening socket to local server address." << std::endl;
		WSACleanup();
		return;
	}
	
	if (listen(listeningSocket, 10) == SOCKET_ERROR)
	// up to 10 connections may wait at any one time to be accepted
	{
		std::cout << "Failed to listen for connecting clients." << std::endl;
		WSACleanup();
		return;
	} 

	std::cout << "Waiting for client connection..." << std::endl;
	
	// wait for a client
	SOCKET clientSocket;
	if ((clientSocket = accept(listeningSocket, NULL, NULL)) == INVALID_SOCKET)
	{
		std::cout << "Failed to accept client connection." << std::endl;
		WSACleanup();
		return;
	}
	
	std::cout << "Client connected." << std::endl;

	// TODO: do something with the client :p

	// close sockets
	closesocket(clientSocket);
	closesocket(listeningSocket);

	// shutdown winsock
	WSACleanup();
}