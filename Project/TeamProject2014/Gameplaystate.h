#pragma once
#include <string.h>
#include "gamestate.h"
#include "Client.h"
#include "Player.hpp"
#include "Netplayer.h"
#include "Pausestate.h"
#include "Map.hpp"
#include "DebugCollider.h"

#define MATCHNUMBER 5

enum MATCHSTATE{SPAWN, MATCH, MATCHOVER, GAMEOVER};

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

	int matchCount;
	int scorePlayer;
	std::vector<int> scoreNetplayers;
	MATCHSTATE matchstate;
	

	//TEMP
	DebugCollider *dbc;
	//TEMP

	void handleConnection();
	void renderScore();
};

