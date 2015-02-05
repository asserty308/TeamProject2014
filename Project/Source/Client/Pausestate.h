#pragma once
#include "gamestate.h"
#include "Game.hpp"

class Pausestate :
	public Gamestate
{
public:
	Pausestate();

	virtual void init();
	virtual void update();
	virtual void render();
	virtual void quit();

	virtual void inputReceived(SDL_KeyboardEvent *key);
	virtual void receivePacket(char* data);

private:
};

