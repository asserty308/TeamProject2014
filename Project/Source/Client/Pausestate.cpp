#include "Pausestate.h"
#include "AudioController.hpp"

Pausestate::Pausestate(){
}

void Pausestate::init()
{
	//initialize and play music
	//g_pAudioController->playMusic("Audio/Music/koz.mp3", true);
}

void Pausestate::receivePacket(std::string data)
{

}

void Pausestate::update(){

}

void Pausestate::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Pausestate::quit(){

}

void Pausestate::inputReceived(SDL_KeyboardEvent *key)
{
	if(key->keysym.sym == SDLK_p && key->type == SDL_KEYUP)
	{
		g_pGame->setState(g_pGame->getGameplayState());

		//tmp location because init() is not called on state-changes
		g_pAudioController->playMusic("Audio/Music/space2a.wav", true);
	}
}


