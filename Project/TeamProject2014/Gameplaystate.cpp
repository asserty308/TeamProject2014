#include "Gameplaystate.h"
#include "Game.hpp"


Gameplaystate::Gameplaystate(){
}

Gameplaystate::~Gameplaystate(){
	delete player;
}

void Gameplaystate::init(){
	player = new Player(Vector2(g_pGame->getWindowWidth() / 2.f, g_pGame->getWindowHeight() / 2.f), Vector2(1.f, 0.f));
}

void Gameplaystate::update(){
	if (player){
		player->updatePosition(g_pTimer->getDeltaTime());
		player->update();
	}
}

void Gameplaystate::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glColor3f(1.f, 0.f, 0.f);
	glRectf(100, 100, g_pGame->getWindowWidth() - 100.f, g_pGame->getWindowHeight() - 100.f);

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
