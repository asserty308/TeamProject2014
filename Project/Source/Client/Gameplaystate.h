#pragma once
#include <string.h>
#include "gamestate.h"
#include "Client.h"
#include "Player.hpp"
#include "Netplayer.h"
#include "Pausestate.h"
#include "Map.hpp"
#include "DebugCollider.h"
#include "Countdown.h"
#include "Sprite.hpp"

#define MATCHNUMBER 5

enum MATCHSTATE{ SPAWN, MATCH, MATCHOVER, GAMEOVER };

class Client;

class Gameplaystate :
	public Gamestate
{
public:
	Gameplaystate();
	~Gameplaystate();

	virtual void init();
	virtual void receivePacket(char* packet);
	virtual void update();
	virtual void render();
	virtual void quit();

	int playerID;

	virtual void inputReceived(SDL_KeyboardEvent *key);

	void addNetplayer(std::string name);

private:
	Client *client;
	Player *player;
	std::vector<Netplayer*> netplayers;
	Map *map;
	Countdown countdown;
	Sprite *backgroundSprite;

	int matchCount;
	int scorePlayer;
	MATCHSTATE matchstate;


	//TEMP
	DebugCollider *dbc;
	//TEMP

	void sendOurStuffToServer();
	void renderScore();
};

