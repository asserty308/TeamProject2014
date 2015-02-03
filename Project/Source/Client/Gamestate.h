#pragma once
#include "Inputlistener.h"

#include <string>

class Gamestate : 
	public Inputlistener
{
public:
	virtual void init() = 0;
	virtual void receivePacket(std::string) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void quit() = 0;
};

