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

	ZeroMemory(package, 256);
}

Client::~Client()
{
	// close socket
	closesocket(serverSocket);

	// shutdown winsock
	WSACleanup();
}

void Client::update(){

	if (send(serverSocket, package, sizeof(float) * 2 + sizeof(char), 0) == SOCKET_ERROR){
		g_pLogfile->fLog("Could not send clientdata in update!");
	}

	std::string dataFromServer = readData();
	
	memcpy(receivedPackage, dataFromServer.data(), sizeof(float) * 4);
}

std::string Client::readData()
{
	std::string data;

	while (true)
	{
		char buffer;
		int bytesReceived = recv(serverSocket, &buffer, 1, 0);

		if (bytesReceived == SOCKET_ERROR){
			g_pLogfile->fLog("\nCould not receive Data from Server!\n");
			return "";
		}

		if (bytesReceived <= 0)
			return "";

		if (buffer == '\n')
			return data;
		else
			data.push_back(buffer);
	}
}

void Client::setPackage(char* data, int size){
	char c = '\n';
	size_t s = sizeof(c);
	memcpy(package, data, size);
	memcpy(package + size, &c, s);
}