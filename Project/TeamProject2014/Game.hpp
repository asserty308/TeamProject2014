#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

#include <string>

class Game
{
	private:
		static std::string GAME_TITLE;

		int windowWidth, windowHeight;
		bool quit;
		SDL_Window *window;
		SDL_GLContext glContext;

	public:
		Game();
		~Game();

		void init();

		void eventLoop();
		void gameLoop();
		void renderFrame();

		void cleanup();
};

