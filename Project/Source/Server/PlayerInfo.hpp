#pragma once

#include <winsock.h>
#include <string>

class PlayerInfo
{
private:
	sockaddr_in address;
	std::string name;

public:
	PlayerInfo(sockaddr_in address, std::string name);
	sockaddr_in getAddress();
	std::string getName();

	float positionX, positionY;
	float forwardX, forwardY;
	float angle;
	float rocketPositionX, rocketPositionY;
	float rocketForwardX, rocketForwardY;
	float isDead;
};