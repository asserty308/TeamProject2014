#pragma once

#include "Gamestate.h"
#include "Client.h"
#include "Game.hpp"
#include "FontRenderer.h"

class LobbyState : public Gamestate{
public:
	LobbyState(Client* client, int numberOfPlayers);
	~LobbyState();

	virtual void init();
	virtual void update();
	virtual void render();
	virtual void quit();

	virtual void inputReceived(SDL_KeyboardEvent *key);

private:
	Client* client;
	int numberOfPlayers;

};