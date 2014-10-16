#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

class Game
{
	private:
		const char* GAME_TITLE = "Alpha Strike";
		Uint16 m_windowWidth, m_windowHeight;
		bool m_quit;
		SDL_Window *m_window;
		SDL_GLContext m_glContext;

	public:
		Game();
		~Game();

		void init();

		void eventLoop();
		void gameLoop();
		void renderFrame();

		void cleanup();
};

