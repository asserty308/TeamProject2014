#include "Game.hpp"

std::string Game::GAME_TITLE = "Alpha Strike";

Game::Game()
{
	windowWidth = 800;
	windowHeight = 600;
	quit = false;
	g_pLogfile->log("start game");
}

Game::~Game()
{
	g_pLogfile->log("quit game");
}

/*
 Initializes SDL and the Game
*/
void Game::init()
{
	int contextFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

	// TODO: error checking
	int error = SDL_Init(SDL_INIT_EVERYTHING);

	// Turn on double buffering.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Create the window
	window = SDL_CreateWindow(GAME_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, contextFlags);
	glContext = SDL_GL_CreateContext(window);

	// 4:3 resolution (800 x 600)
	glOrtho(0.0, 4.f, 0.0, 3.f, -1.0, 1.0);

	// temporary, TODO: delete
	player = new Player(Vector2(2.0f, 1.5f), Vector2(1.f, 0.f));

	//Init modules
	g_pTimer->init();
}

// Event-related functions
void Game::eventLoop()
{
	SDL_Event event;

	while ((!quit))
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYUP:
				case SDL_KEYDOWN:
					g_pInputObserver->fireChange(&event.key);
					break;

				case SDL_QUIT:
					quit = true;
					break;
			}
		}

		gameLoop();
	}
}

void Game::gameLoop()
{
	g_pTimer->update();

	if (player){
		player->updatePosition(g_pTimer->getDeltaTime());
		player->update();
	}

	renderFrame();
}

void Game::renderFrame()
{
	// draw a fullscreen black rectangle to clear the frame
	glColor3f(0.f, 0.f, 0.f);
	glRectf(0.f, 0.f, 4.f, 3.f);

	glColor3f(1.f, 0.f, 0.f);
	glRectf(1.f, 2.f, 3.f, 1.f);

	// temporary, TODO: delete
	if (player)
		player->render();

	SDL_GL_SwapWindow(window);
}

void Game::cleanup()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}