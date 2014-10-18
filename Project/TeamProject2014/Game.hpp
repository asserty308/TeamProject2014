#pragma once

#include <string>

#include <SDL.h>
#include <SDL_opengl.h>

#include "Player.hpp"
#include "Logger.hpp"
#include "Timer.h"
#include "InputObserver.h"

class Game
{
	private:
		static std::string GAME_TITLE;

		int windowWidth, windowHeight;
		bool quit;
		SDL_Window *window;
		SDL_GLContext glContext;

		// temporary, TODO: delete
		Player *player;

	public:
		Game();
		~Game();

		void init();

		void eventLoop();
		void gameLoop();
		void renderFrame();

		void cleanup();
};

