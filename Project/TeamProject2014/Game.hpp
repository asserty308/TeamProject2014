#pragma once

#include <string>

#include <SDL.h>
#include <SDL_opengl.h>

#include "Logger.hpp"
#include "Timer.h"
#include "InputObserver.h"
#include "Gamestate.h"
#include "Gameplaystate.h"
#include "Pausestate.h"
#include "Singleton.hpp"

#define g_pGame Game::Get()

//forward declarations
class Gameplaystate; 
class Pausestate;

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

	int getWindowWidth();
	int getWindowHeight();
};

