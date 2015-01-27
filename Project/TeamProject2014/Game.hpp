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

#define g_pGame Game::Get()

//forward declarations
class Gameplaystate; 
class Pausestate;
class LobbyState;

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

	Client* client;

public:
	Game();
	~Game();

	void init();

	void eventLoop();
	void gameLoop();
	void renderFrame();

	void cleanup();

	void setState(Gamestate *state);

	Gameplaystate* getGameplayState();
	Pausestate* getPauseState();
	LobbyState* getLobbyState();

	int getWindowWidth();
	int getWindowHeight();
};

