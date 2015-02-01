#pragma once
#include "Singleton.hpp"
#include "Inputlistener.h"
#include <SDL.h>
#include <vector>

#define g_pInputObserver InputObserver::Get()

class InputObserver :
	public Singleton<InputObserver>
{
public:
	InputObserver(void);

	void addListener(Inputlistener *l);
	void removeListener(Inputlistener *l);

	void setListener(Inputlistener *l, Inputlistener *value);

	bool isListening(Inputlistener *l);

	void fireChange(SDL_KeyboardEvent *key);

	
	
private:
	std::vector<Inputlistener*> listener;
};

