#include "Netplayer.h"

Netplayer::Netplayer() : Transform(Vector2(0.0, 0.0), Vector2(0.0f, -1.0f), Vector2(0.0f, 0.0f)){

}

Netplayer::Netplayer(Vector2 position, Vector2 forward) : Transform(position, forward, Vector2(0.0f, 0.0f)){
	sprite = new Sprite("fighter4.png", position, Vector2(200.f, 150.f));
}

Netplayer::~Netplayer(){
	delete sprite;
}

void Netplayer::update(Vector2 pos){
	this->setPosition(pos);
	sprite->setPosition(pos);
}

void Netplayer::render(){

}