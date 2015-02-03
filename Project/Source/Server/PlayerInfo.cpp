#include "PlayerInfo.hpp"

PlayerInfo::PlayerInfo(sockaddr_in address, std::string name)
{
	this->address = address;
	this->name = name;
}

sockaddr_in PlayerInfo::getAddress()
{
	return address;
}

std::string PlayerInfo::getName()
{
	return name;
}