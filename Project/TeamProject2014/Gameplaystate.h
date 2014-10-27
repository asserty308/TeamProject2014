#pragma once
#include "gamestate.h"
#include "Player.hpp"
#include "Pausestate.h"
#include "Map.hpp"
#include "DebugCollider.h"

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
	Player *player;
	Map *map;

	//TEMP
	DebugCollider *dbc;
	//TEMP
};

