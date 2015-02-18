#pragma once

#include <string>

#include <SDL.h>
#include <SDL_opengl.h>

#include "Logger.hpp"
#include "Timer.h"
#include "InputObserver.h"
#include "CollisionObserver.h"
#include "Gamestate.h"
#include "Gameplaystate.h"
#include "Pausestate.h"
#include "LobbyState.h"
#include "Singleton.hpp"
#include "MainMenuState.h"

#define g_pGame Game::Get()

//forward declarations
class Gameplaystate; 
class Pausestate;
class LobbyState;
class MainMenuState;

class Game : public Singleton < Game >
{
private:
	static std::string GAME_TITLE;

	int windowWidth, windowHeight;
	bool quit;
	SDL_Window *window;
	SDL_GLContext glContext;

	Gamestate *currentState;

	Gameplaystate *gameplayState;
	Pausestate *pauseState;
	LobbyState *lobbyState;
	MainMenuState *menuState;

	Client* client;

	int numberofPlayers;
	int bestOfX;
	int mapID;

	std::string name, serverIP;
	int serverPort, clientPort;

public:
	Game();
	~Game();

	void init();

	void eventLoop();
	void gameLoop();
	void renderFrame();

	void cleanup();

	void setState(Gamestate *state);

	Gamestate *getState();
	Gameplaystate* getGameplayState();
	Pausestate* getPauseState();
	LobbyState* getLobbyState();

	int getWindowWidth();
	int getWindowHeight();

	int getNumberOfPlayers();
	void setNumberOfPlayers(int n);
	int getBestOfX();
	void setBestOfX(int x);
	int getMapID();
	void setMapID(int mapID);

	void setName(std::string n);
	void setServerIP(std::string i);
	void setServerPort(int p);
	void setClientPort(int p);

	std::string getName();
	std::string getServerIP();
	int getServerPort();
	int getClientPort();

	void setClient(Client *c);
	Client* getClient();
};

