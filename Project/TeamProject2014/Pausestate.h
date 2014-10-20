#pragma once
#include "gamestate.h"
#include "Game.hpp"

class Game; //forward declaration

class Pausestate :
	public Gamestate
{
public:
	Pausestate(Game *game);

	virtual void init();
	virtual void update();
	virtual void render();
	virtual void quit();

	virtual void inputReceived(SDL_KeyboardEvent *key);

private:
	Game *game;
	
};

