#include "CollisionObserver.h"
#include "Gameplaystate.h"
#include "Game.hpp"
#include "MapParser.h"
#include "SpriteRenderer.hpp"

Gameplaystate::Gameplaystate()
{
	player = nullptr;
	map = nullptr;
	dbc = nullptr;
}

Gameplaystate::~Gameplaystate()
{
	delete player;
	delete map;
}

void Gameplaystate::init()
{
	map = MapParser::loadMap("testmap.xml");

	Vector2 playerSpawn(g_pGame->getWindowWidth() / 2, g_pGame->getWindowHeight() / 2);

	if (map)
		playerSpawn = map->getPlayerSpawn();

	player = new Player(playerSpawn, Vector2(0.f, -1.f));

}

void Gameplaystate::update()
{
	g_pCollisionObserver->checkCollisionRoutine();

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

	g_pSpriteRenderer->renderScene();
}

void Gameplaystate::quit()
{

}

void Gameplaystate::inputReceived(SDL_KeyboardEvent *key)
{
	if(key->keysym.sym == SDLK_p && key->type == SDL_KEYUP)
		g_pGame->setState(g_pGame->getPauseState());
}
