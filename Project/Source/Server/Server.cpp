#include <iostream>
#include <sstream>

#include "Server.h"

Server::Server()
{
	// we want winsock version 2.2
	WORD sockVersion = MAKEWORD(2, 2);

	// load up winsock
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		std::cout << "Failed to start winsock library: " << WSAGetLastError() << std::endl;
		return;
	}

	do
	{
		std::cout << "Please enter desired player count (2-4): ";
		std::cin >> maxPlayers;
	} while (maxPlayers < 2 || maxPlayers > 4);

	connectedPlayers = 0;

	// create the listening socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		std::cout << "Failed to create socket." << std::endl;
		return;
	}

	//Change socket to a non-blocking one
	u_long iMode = 1;
	if (ioctlsocket(s, FIONBIO, &iMode) == SOCKET_ERROR)
	{
		std::cout << "Socket did not enter non-blocking mode." << std::endl;
		return;
	}

	do
	{
		std::cout << "Please enter desired port number (1000-99999): ";
		std::cin >> port;
	} while (port < 1000 || port > 99999);
		
	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = INADDR_ANY;
	serverInfo.sin_port = port;

	// bind the socket
	if (bind(s, (struct sockaddr*)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR)
	{
		std::cout << "Failed to bind socket." << std::endl;
		return;
	}

	do
	{
		std::cout << "Please enter desired tickrate (16-128): ";
		std::cin >> tickrate;
	} while (tickrate < 16 || tickrate > 128);

	data = new char[BUFLEN];

	state = ServerState_Waiting;
}

Server::~Server()
{
	closesocket(s);
	WSACleanup();
}

int Server::getMaxPlayers()
{
	return maxPlayers;
}

int Server::getTickrate()
{
	return tickrate;
}

bool Server::sendToClient(PlayerInfo player, std::string data)
{
	char d[BUFLEN];
	strcpy(d, data.c_str());
	return sendToClient(player, d, strlen(d));
}

bool Server::sendToClient(PlayerInfo player, char* data, int size)
{
	return sendto(s, data, size, 0, (struct sockaddr*)&player.getAddress(), sizeof(player.getAddress())) != SOCKET_ERROR;
}

void Server::update()
{
	//clear the buffer
	memset(data, '\0', BUFLEN);

	// read data from socket
	sockaddr_in clientInfo;
	int clientLen = sizeof(clientInfo);
	int bytesReceived = recvfrom(s, data, BUFLEN, 0, (struct sockaddr*)&clientInfo, &clientLen);

	while (bytesReceived > 0)
	// if there was something to read
	{
		std::string recString = data;

		if (state == ServerState_Waiting)
		{
			if (recString.substr(0, 7).compare("welcome") == 0)
			// if we received a welcome packet from a player signing up with their name
			{
				std::string nickname = recString.substr(8);
				std::cout << "Player \"" << nickname.c_str() << "\" connected (" << connectedPlayers + 1 << "/" << maxPlayers << ")" << std::endl;
				connectedPlayers++;

				players.push_back(new PlayerInfo(clientInfo, nickname));

				if (connectedPlayers == maxPlayers)
				{
					int startIndex = 0;

					for (PlayerInfo *i : players)
					{
						std::stringstream msg;
						msg << "start:";
						msg	<< startIndex;

						if (!sendToClient(*i, msg.str()))
							std::cout << "Failed to send start packet to a player." << std::endl;
						//else
							//std::cout << "Sent start packet \"" << msg.str() << "\" to player \"" << (*i).getName() << "\"."  << std::endl;

						startIndex++;
					}

					std::cout << std::endl << "All players connected, starting game..." << std::endl << std::endl;

					state = ServerState_Ingame;
				}
			}
			else
				std::cout << "Invalid packet received (\"" << data << "\") and discarded." << std::endl;
		}
		else if (state == ServerState_Ingame)
		{
			int index = 0;

			for (PlayerInfo *playerInfo : players)
			{
				if (clientInfo.sin_addr.S_un.S_addr == playerInfo->getAddress().sin_addr.S_un.S_addr && clientInfo.sin_port == playerInfo->getAddress().sin_port)
				{
					float *playerData = new float[10];
					memcpy(playerData, data, sizeof(float)* 10);

					playerInfo->positionX = playerData[0];
					playerInfo->positionY = playerData[1];
					playerInfo->forwardX = playerData[2];
					playerInfo->forwardY = playerData[3];
					playerInfo->angle = playerData[4];
					playerInfo->rocketPositionX = playerData[5];
					playerInfo->rocketPositionY = playerData[6];
					playerInfo->rocketForwardX = playerData[7];
					playerInfo->rocketForwardY = playerData[8];
					playerInfo->isDead = playerData[9];

					delete[] playerData;

					break;
				}

				index++;
			}
		}

		// read more data
		bytesReceived = recvfrom(s, data, BUFLEN, 0, (struct sockaddr*)&clientInfo, &clientLen);
	}

	if (state == ServerState_Ingame)
	{
		for (PlayerInfo *recipient : players)
		{
			char playerDataPacket[BUFLEN];

			for (PlayerInfo *playerInfo : players)
			{
				if (recipient == playerInfo)
					continue;

				float playerData[10] = { playerInfo->positionX, playerInfo->positionY,
					playerInfo->forwardX, playerInfo->forwardY,
					playerInfo->angle,
					playerInfo->rocketPositionX, playerInfo->rocketPositionY,
					playerInfo->rocketForwardX, playerInfo->rocketForwardY, playerInfo->isDead };

				//std::cout << "players: " << players.size() << " offset: " << offset << std::endl;
				//std::cout << "Net player \"" << playerInfo->getName() << "\" pos: " << playerInfo->positionX << "x" << playerInfo->positionY << std::endl;

				//memcpy(playerDataPacket + offset * (sizeof(float) * 10), playerData, sizeof(float) * 10);
				memcpy(playerDataPacket, playerData, sizeof(float)* 10);
			}

			sendToClient(*recipient, playerDataPacket, sizeof(float)* 10);
		}
	}
}

/*
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
int offset = 0;
for (int i = 0; i < MAX_PLAYERS; i++){
if (i != receiverID){
memcpy(buffer + (offset * BUFLEN), returnPackage + (i * BUFLEN), BUFLEN);
offset++;
}
}

if (sendto(respondingSocket, buffer, bufferSize, 0, (struct sockaddr*) &clientInfo, sizeof(clientInfo)) == SOCKET_ERROR){
std::cout << "Could not send data to client. Error: " << WSAGetLastError() << std::endl;
}

delete buffer;
}
*/
