#pragma once
#include "gamestate.h"
#include "Player.hpp"
#include "Pausestate.h"

class Gameplaystate :
	public Gamestate
{
public:
	Gameplaystate();
	~Gameplaystate();
	
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void quit();

	virtual void inputReceived(SDL_KeyboardEvent *key);

private:
	// temporary
	Player *player;
};

