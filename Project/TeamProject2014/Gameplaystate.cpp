#include "Gameplaystate.h"


Gameplaystate::Gameplaystate(Game *game){
	this->game = game;
}

Gameplaystate::~Gameplaystate(){
	delete player;
}

void Gameplaystate::init(){
	player = new Player(Vector2(2.0f, 1.5f), Vector2(1.f, 0.f));
}

void Gameplaystate::update(){
	if (player){
		player->updatePosition(g_pTimer->getDeltaTime());
		player->update();
	}
}

void Gameplaystate::render(){
	// draw a fullscreen black rectangle to clear the frame
	glColor3f(0.f, 0.f, 0.f);
	glRectf(0.f, 0.f, 4.f, 3.f);

	glColor3f(1.f, 0.f, 0.f);
	glRectf(1.f, 2.f, 3.f, 1.f);

	// temporary
	if (player)
		player->render();
}

void Gameplaystate::quit(){

}

void Gameplaystate::inputReceived(SDL_KeyboardEvent *key){
	if(key->keysym.sym == SDLK_p && key->type == SDL_KEYUP){
		game->setState(game->getPauseState());
	}
}
