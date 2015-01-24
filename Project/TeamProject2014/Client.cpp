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
	recvfrom(clientSocket, initPackage, BUFLEN, 0, 0, 0);

	ZeroMemory(package, 256);
}

Client::~Client()
{
	// close socket
	closesocket(clientSocket);

	// shutdown winsock
	WSACleanup();
}

void Client::update(){

	if (sendto(clientSocket, package, sizeof(float) * 10, 0, (struct sockaddr*)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR){
		g_pLogfile->fLog("Could not send clientdata in update! Error: %d", WSAGetLastError());
	}

	//commented out because it caused the program to crash after a while
	int bytesReceived = recvfrom(clientSocket, receivedPackage, BUFLEN, 0, 0, 0);
	
	//memcpy(receivedPackage, dataFromServer.data(), sizeof(float) * 4);
}

void Client::setPackage(char* data, int size){
	memcpy(package, data, size);
}