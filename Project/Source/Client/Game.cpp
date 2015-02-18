#include "Game.hpp"

std::string Game::GAME_TITLE = "Alpha Strike";

Game::Game()
{
	windowWidth = 800;
	windowHeight = 600;
	quit = false;
	g_pLogfile->log("Client running...");
	g_pCollisionObserver->setxAxis(Vector2(windowWidth, 0));
	g_pCollisionObserver->setyAxis(Vector2(0, windowHeight));

	//numberofPlayers = 4;

	gameplayState = new Gameplaystate();
	pauseState = new Pausestate();
	lobbyState = new LobbyState();
	menuState = new MainMenuState();

}

Game::~Game()
{
	delete client;
	delete gameplayState;
	delete pauseState;
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

	glOrtho(0.f, windowWidth, windowHeight, 0.f, -1.0, 1.0);

	//Init modules
	g_pTimer->init();
	//currentState->init();

	setState(menuState);
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

	currentState->update();

	renderFrame();
}

void Game::renderFrame()
{
	currentState->render();
	SDL_GL_SwapWindow(window);
}

void Game::cleanup()
{
	currentState->quit();
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::setState(Gamestate *state){
	if(g_pInputObserver->isListening(currentState)){
		g_pInputObserver->setListener(currentState, state);
	}else{
		g_pInputObserver->addListener(state);
	}
	this->currentState = state;
	currentState->init();
}

Gamestate *Game::getState()
{
	return currentState;
}

Gameplaystate* Game::getGameplayState(){
	return gameplayState;
}

Pausestate* Game::getPauseState(){
	return pauseState;
}

LobbyState* Game::getLobbyState(){
	return lobbyState;
}

int Game::getWindowWidth()
{
	return windowWidth;
}

int Game::getWindowHeight()
{
	return windowHeight;
}

int Game::getNumberOfPlayers(){
	return numberofPlayers;
}

void Game::setNumberOfPlayers(int n){
	this->numberofPlayers = n;
}

int Game::getBestOfX()
{
	return bestOfX;
}

void Game::setBestOfX(int x)
{
	bestOfX = x;
}

int Game::getMapID()
{
	return mapID;
}

void Game::setMapID(int mapID)
{
	this->mapID = mapID;
}

void Game::setName(std::string n)
{
	name = n;
}

void Game::setServerIP(std::string i)
{
	serverIP = i;
}

void Game::setServerPort(int p)
{
	serverPort = p;
}

void Game::setClientPort(int p)
{
	clientPort = p;
}

std::string Game::getName()
{
	return name;
}

std::string Game::getServerIP()
{
	return serverIP;
}

int Game::getServerPort()
{
	return serverPort;
}

int Game::getClientPort()
{
	return clientPort;
}

void Game::setClient(Client *c)
{
	client = c;

	//client->init(numberofPlayers - 1);
}

Client* Game::getClient(){
	return client;
}