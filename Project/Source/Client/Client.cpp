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

	// create socket
	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s == INVALID_SOCKET)
	{
		g_pLogfile->fLog("socket() error: %s", WSAGetLastError());
		return;
	}

	SOCKADDR_IN clientInfo;
	clientInfo.sin_family = AF_INET;
	clientInfo.sin_addr.s_addr = INADDR_ANY;
	clientInfo.sin_port = g_pGame->getClientPort();

	// bind the socket
	if (bind(s, (struct sockaddr*)&clientInfo, sizeof(clientInfo)) == SOCKET_ERROR)
	{
		g_pLogfile->fLog("Failed to bind socket.");
		return;
	}

	//Change socket to a non-blocking one
	u_long iMode = 1;
	if (ioctlsocket(s, FIONBIO, &iMode) == SOCKET_ERROR)
	{
		g_pLogfile->fLog("Socket did not enter non-blocking mode.");
		return;
	}

	//setup address structure
	memset((char*)&serverInfo, 0, sizeof(serverInfo));
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_port = g_pGame->getServerPort();
	serverInfo.sin_addr.S_un.S_addr = inet_addr(g_pGame->getServerIP().c_str());

	data = new char[BUFLEN];
}

Client::~Client()
{
	delete[] data;
	closesocket(s);
	WSACleanup();
}

bool Client::sendToServer(std::string data)
{
	char d[BUFLEN];
	strcpy(d, data.c_str());
	return sendToServer(d, strlen(d));
}

bool Client::sendToServer(char *data, int size)
{
	return sendto(s, data, size, 0, (struct sockaddr*)&serverInfo, sizeof(serverInfo)) != SOCKET_ERROR;
}

void Client::update()
{
	// read data from socket
	int bytesReceived = recvfrom(s, data, BUFLEN, 0, 0, 0);

	while (bytesReceived > 0)
	// if there was something to read
	{
		// pass the received packet on to the current game state
		g_pGame->getState()->receivePacket(data);

		// read more data
		bytesReceived = recvfrom(s, data, BUFLEN, 0, 0, 0);
	}
}