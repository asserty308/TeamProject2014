#pragma once
#include <string.h>
#include "gamestate.h"
#include "Client.h"
#include "Player.hpp"
#include "Netplayer.h"
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
	Client *client;
	Player *player;
	Netplayer *netplayer;
	Map *map;

	//TEMP
	DebugCollider *dbc;
	//TEMP
};

