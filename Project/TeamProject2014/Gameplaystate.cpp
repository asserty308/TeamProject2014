#include "CollisionObserver.h"
#include "Gameplaystate.h"
#include "Game.hpp"
#include "MapParser.h"
#include "SpriteRenderer.hpp"
#include "AudioController.hpp"

Gameplaystate::Gameplaystate()
{
	player = nullptr;
	map = nullptr;
	dbc = nullptr;
}

Gameplaystate::~Gameplaystate()
{
	delete player;
	delete dbc;
	delete map;

	player = nullptr;
	map = nullptr;
	dbc = nullptr;
}

void Gameplaystate::init()
{
	map = MapParser::loadMap("testmap.xml");

	Vector2 playerSpawn(g_pGame->getWindowWidth() / 2, g_pGame->getWindowHeight() / 2);

	if (map)
		playerSpawn = map->getPlayerSpawn();

	player = new Player(playerSpawn, Vector2(0.f, -1.f));

	//TEMP
	dbc = new DebugCollider(Vector2(600, 400), Vector2(1.f, 0.f), 20.0f);
	//TEMP

	//initialize and play music
	g_pAudioController->playMusic("Audio/Music/space2a.wav", true);
}

void Gameplaystate::update()
{
	g_pCollisionObserver->checkCollisionRoutine();

	//play all sounds currently active
	g_pAudioController->playSound();

	if (player){
		player->updatePosition(g_pTimer->getDeltaTime());
		player->update();
	}
}

void Gameplaystate::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (map)
		map->render();

	// temporary
	if (player)
		player->render();

	dbc->render();

	g_pSpriteRenderer->renderScene();
}

void Gameplaystate::quit()
{

}

void Gameplaystate::inputReceived(SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_p && key->type == SDL_KEYUP)
	{
		g_pGame->setState(g_pGame->getPauseState());

		//tmp location because init() is not called on state-changes
		g_pAudioController->playMusic("Audio/Music/science-0f-22mi.wav", true);
	}
}
