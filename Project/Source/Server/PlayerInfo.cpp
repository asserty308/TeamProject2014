#include "PlayerInfo.hpp"

PlayerInfo::PlayerInfo(sockaddr_in address, std::string name)
{
	this->address = address;
	this->name = name;

	setScore(0);

	hasAcknowledgedStartPacket = false;
}

bool PlayerInfo::operator == (const sockaddr_in &other) const
{
	return address.sin_addr.S_un.S_addr == other.sin_addr.S_un.S_addr && address.sin_port == other.sin_port;
}

bool PlayerInfo::operator == (const PlayerInfo &other) const
{
	return *this == other.address;
}

bool PlayerInfo::operator != (const sockaddr_in &other) const
{
	return !(*this == other);
}

bool PlayerInfo::operator != (const PlayerInfo &other) const
{
	return !(*this == other);
}

sockaddr_in PlayerInfo::getAddress()
{
	return address;
}

std::string PlayerInfo::getName()
{
	return name;
}

int PlayerInfo::getScore()
{
	return score;
}

void PlayerInfo::setScore(int score)
{
	this->score = score;
}