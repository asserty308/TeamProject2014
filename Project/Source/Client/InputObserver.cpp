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

void InputObserver::setListener(Inputlistener *l, Inputlistener *value){
	int index = std::find(listener.begin(), listener.end(), l) - listener.begin();
	listener.at(index) = value;
}

bool InputObserver::isListening(Inputlistener *l){
	if(std::find(listener.begin(), listener.end(), l) != listener.end()){
		return true;
	}else{
		return false;
	}
}

void InputObserver::fireChange(SDL_KeyboardEvent *key){
	for(Inputlistener *l: listener){
		l->inputReceived(key);
	}
}
