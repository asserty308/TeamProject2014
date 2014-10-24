#include "Gameplaystate.h"
#include "Game.hpp"


Gameplaystate::Gameplaystate(){
}

Gameplaystate::~Gameplaystate(){
	delete player;
}

void Gameplaystate::init(){
	map = new Map();
	map->setPlayerSpawn(Vector2(g_pGame->getWindowWidth() / 2.f, g_pGame->getWindowHeight() / 2.f));

	Obstacle obstacle;
	obstacle.addVertex(Vector2(100.f, 100.f));
	obstacle.addVertex(Vector2(140.f, 80.f));
	obstacle.addVertex(Vector2(240.f, 120.f));
	obstacle.addVertex(Vector2(200.f, 300.f));
	obstacle.addVertex(Vector2(110.f, 270.f));
	obstacle.addVertex(Vector2(90.f, 140.f));
	map->addObstacle(obstacle);

	player = new Player(map->getPlayerSpawn(), Vector2(1.f, 0.f));
}

void Gameplaystate::update(){
	if (player){
		player->updatePosition(g_pTimer->getDeltaTime());
		player->update();
	}
}

void Gameplaystate::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (map)
		map->render();

	// temporary
	if (player)
		player->render();
}

void Gameplaystate::quit(){

}

void Gameplaystate::inputReceived(SDL_KeyboardEvent *key){
	if(key->keysym.sym == SDLK_p && key->type == SDL_KEYUP){
		g_pGame->setState(g_pGame->getPauseState());
	}
}
