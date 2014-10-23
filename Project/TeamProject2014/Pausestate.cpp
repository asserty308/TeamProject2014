#include "Pausestate.h"


Pausestate::Pausestate(){
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
		g_pGame->setState(g_pGame->getGameplayState());
	}
}


