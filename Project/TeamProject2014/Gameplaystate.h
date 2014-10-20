#pragma once
#include "gamestate.h"
#include "Game.hpp"
#include "Player.hpp"
#include "Pausestate.h"

class Game; //forward declaration

class Gameplaystate :
	public Gamestate
{
public:
	Gameplaystate(Game *game);
	~Gameplaystate();
	
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void quit();

	virtual void inputReceived(SDL_KeyboardEvent *key);

private:
	Game *game;

	// temporary
	Player *player;

};

