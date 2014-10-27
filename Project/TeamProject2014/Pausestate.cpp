#include "Pausestate.h"


Pausestate::Pausestate(){
}

void Pausestate::init(){

}

void Pausestate::update(){

}

void Pausestate::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Pausestate::quit(){

}

void Pausestate::inputReceived(SDL_KeyboardEvent *key){
	if(key->keysym.sym == SDLK_p && key->type == SDL_KEYUP){
		g_pGame->setState(g_pGame->getGameplayState());
	}
}


