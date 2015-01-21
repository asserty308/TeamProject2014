#include "Netplayer.h"

Netplayer::Netplayer() : TransformCollidable(Vector2(0.0, 0.0), Vector2(0.0f, -1.0f), Vector2(0.0f, 0.0f)){

}

Netplayer::Netplayer(Vector2 position, Vector2 forward) : TransformCollidable(position, forward, Vector2(0.0f, 0.0f)){
	sprite = new Sprite("fighter4.png", position, Vector2(200.f, 150.f));
	netRocket = new NetRocket(this, Vector2(-100.0, -100.0), Vector2(0.0f, 0.0f));

	boundingBox = new CircleBoundingBox(position, 25.0f);

	this->setTag("netPlayer");
	netRocket->setTag("netRocket");
	
	g_pCollisionObserver->addListener(this);
}

Netplayer::~Netplayer(){
	delete sprite;
	delete netRocket;
}

void Netplayer::CollisionDetected(TransformCollidable *other, Vector2 penetration){
	
}

void Netplayer::update(Vector2 pos, Vector2 forward, float angle, Vector2 rocketPos, Vector2 rocketForward){
	this->setPosition(pos);
	sprite->setPosition(pos);

	this->setForward(forward);
	sprite->setAngle(angle);

	netRocket->update(rocketPos, rocketForward);
}

void Netplayer::render(){

	netRocket->render();

}

void Netplayer::rocketDestroyed(){
	netRocket->update(Vector2(-100.0, -100.0), Vector2(0.0, 0.0));
}