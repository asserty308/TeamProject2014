#include "InputObserver.h"


InputObserver::InputObserver(void)
{
}

void InputObserver::addListener(Inputlistener *l){
	listener.push_back(l);
}

void InputObserver::removeListener(Inputlistener *l){
	listener.erase(std::find(listener.begin(), listener.end(), l));
}

void InputObserver::fireChange(SDL_KeyboardEvent *key){
	for(Inputlistener *l: listener){
		l->inputReceived(key);
	}
}
