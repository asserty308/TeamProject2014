#include "Client.h"
#include "Logger.hpp"

Client::Client()
{
	// we want winsock version 1.1
	WORD sockVersion = MAKEWORD(1, 1);

	// load up winsock
	WSADATA wsaData;
	WSAStartup(sockVersion, &wsaData);
	
	LPHOSTENT hostEntry;
	in_addr host;
	host.s_addr = inet_addr("127.0.0.1");
	if (!(hostEntry = gethostbyaddr((const char *)&host, sizeof(struct in_addr), AF_INET)))
	// get host by address
	{
		g_pLogfile->textout("Failed to get server by address...");
		return;
	}
	
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	// create the socket
	{
		g_pLogfile->textout("Failed to create server socket...");
		return;
	}
	
	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr = *((LPIN_ADDR)*hostEntry->h_addr_list);
	serverInfo.sin_port = htons(8888);
	
	if ((connect(serverSocket, (LPSOCKADDR)&serverInfo, sizeof(struct sockaddr))) == SOCKET_ERROR)
	// connect to the server
	{
		g_pLogfile->textout("Failed to connect to server...");
		return;
	}

	g_pLogfile->textout("Successfully connected to server...");

	// send our name to the server
	char buffer[256];
	ZeroMemory(buffer, 256);
	strcpy(buffer, "SuP3R-H4xX0R");
	buffer[12] = '\n';
	if (send(serverSocket, buffer, strlen(buffer), 0) == SOCKET_ERROR)
	{
		g_pLogfile->textout("Failed to send data to server...");
		return;
	}
}

Client::~Client()
{
	// close socket
	closesocket(serverSocket);

	// shutdown winsock
	WSACleanup();
}