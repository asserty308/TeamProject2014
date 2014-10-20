#include "Pausestate.h"


Pausestate::Pausestate(Game *game){
	this->game = game;
}

void Pausestate::init(){

}

void Pausestate::update(){

}

void Pausestate::render(){
	glColor3f(0.f, 0.f, 0.f);
	glRectf(0.f, 0.f, 4.f, 3.f);
}

void Pausestate::quit(){

}

void Pausestate::inputReceived(SDL_KeyboardEvent *key){
	if(key->keysym.sym == SDLK_p && key->type == SDL_KEYUP){
		game->setState(game->getGameplayState());
	}
}


