#include "Timer.h"
#include <SDL.h>

Timer::Timer(void)
{
}

void Timer::init(){
	currentTime = 0.0f;
	lastTime = SDL_GetTicks() / 1000.0f;
	deltaTime = 0.0f;
}

void Timer::update(){
	currentTime = SDL_GetTicks() / 1000.0f;
	deltaTime = currentTime - lastTime; 
	lastTime = currentTime;
}

float Timer::getDeltaTime(){
	return deltaTime;
}

