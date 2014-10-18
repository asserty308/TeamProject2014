#pragma once
#include <SDL.h>

class Inputlistener
{
public:
	virtual void inputReceived(SDL_KeyboardEvent *key) = 0;	
};

