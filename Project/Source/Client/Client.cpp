#include "Client.h"
#include "Logger.hpp"

Client::Client()
{
	// we want winsock version 2.2
	WORD sockVersion = MAKEWORD(2, 2);

	// load up winsock
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		g_pLogfile->fLog("WSAStartup() error: %s", WSAGetLastError());
		return;
	}
	
	//create socket
	clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (clientSocket == INVALID_SOCKET)
	{
		g_pLogfile->fLog("socket() error: %s", WSAGetLastError());
		return;
	}

	//setup address structure
	memset((char*)&serverInfo, 0, sizeof(serverInfo));
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_port = htons(8888);
	serverInfo.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	// send our name to the server
	char buffer[BUFLEN];
	ZeroMemory(buffer, BUFLEN);
	strcpy(buffer, "SuP3R-H4xX0R");
	//buffer[12] = '\n';
	if (sendto(clientSocket, buffer, strlen(buffer), 0, (struct sockaddr*)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR)
	{
		g_pLogfile->textout("Failed to send data to server...");
		return;
	}

	//receive our "welcome package" i.e. spawnpoint and other data that differs between players
	memset(initPackage, '?', BUFLEN);
	recvfrom(clientSocket, initPackage, BUFLEN, 0, 0, 0);

	//Change socket to a non-blocking one
	u_long iMode = 1;
	if (ioctlsocket(clientSocket, FIONBIO, &iMode) == SOCKET_ERROR){
		g_pLogfile->textout("Clientsocket did not enter non-blocking mode!");
	}

	ZeroMemory(package, 128);
}

Client::~Client()
{
	delete[] receivedPackage;

	// close socket
	closesocket(clientSocket);

	// shutdown winsock
	WSACleanup();
}

void Client::init(int numberOfPlayers){
	receivedPackage = new char[BUFLEN * numberOfPlayers - 1];
	memset(receivedPackage, '?', BUFLEN);
}

void Client::update(){
	memset(receivedPackage, '?', BUFLEN);

	if (sendto(clientSocket, package, sizeof(float) * 10, 0, (struct sockaddr*)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR){
		g_pLogfile->fLog("Could not send clientdata in update! Error: %d", WSAGetLastError());
	}

	int bytesReceived = recvfrom(clientSocket, receivedPackage, BUFLEN * g_pGame->getNumberOfPlayers() - 1, 0, 0, 0);
	
}

void Client::setPackage(char* data, int size){
	memcpy(package, data, size);
}