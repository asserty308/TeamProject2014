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

	bool operator == (const sockaddr_in &other) const;
	bool operator == (const PlayerInfo &other) const;
	bool operator != (const sockaddr_in &other) const;
	bool operator != (const PlayerInfo &other) const;

	sockaddr_in getAddress();
	std::string getName();

	float positionX, positionY;
	float forwardX, forwardY;
	float angle;
	float rocketPositionX, rocketPositionY;
	float rocketForwardX, rocketForwardY;
	float isDead;
	bool hasAcknowledgedStartPacket;
};