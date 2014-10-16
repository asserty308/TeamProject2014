#include "Game.hpp"

Game::Game()
{
	m_windowWidth = 800.f;
	m_windowHeight = 600.f;
	m_quit = false;
}


Game::~Game()
{
}

/*
 Initializes SDL and the Game
*/
void Game::init()
{
	Uint16 contextFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
	int error = SDL_Init(SDL_INIT_EVERYTHING);

	// Turn on double buffering.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Create the window
	m_window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_windowWidth, m_windowHeight, contextFlags);
	m_glContext = SDL_GL_CreateContext(m_window);

	//4:3 resolution (800 x 600)
	glOrtho(0.0, 4.f, 0.0, 3.f, -1.0, 1.0);
}

// Event-related functions
void Game::eventLoop()
{
	SDL_Event event;

	while ((!m_quit))
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					m_quit = true;
					break;
			}
		}

		gameLoop();
	}
}

void Game::gameLoop()
{
	renderFrame();
}

void Game::renderFrame()
{
	glColor3f(1.f, 0.f, 0.f);
	glRectf(1.f, 2.f, 3.f, 1.f);
	SDL_GL_SwapWindow(m_window);
}

void Game::cleanup()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}