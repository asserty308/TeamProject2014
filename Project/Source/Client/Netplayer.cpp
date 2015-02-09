#include "Netplayer.h"

Netplayer::Netplayer() : TransformCollidable(Vector2(0.0, 0.0), Vector2(0.0f, -1.0f), Vector2(0.0f, 0.0f)){

}

Netplayer::Netplayer(Vector2 position, Vector2 forward) : TransformCollidable(position, forward, Vector2(0.0f, 0.0f)){
	sprite = new Sprite(/*"Sprites\\fighter4.png"*/"Sprites\\new_fighter.png", position, Vector2(/*200.f, 150.f*/80.f, 80.f));
	netRocket = new NetRocket(this, Vector2(-100.0, -100.0), Vector2(0.0f, 0.0f));

	boundingBox = new CircleBoundingBox(position, 25.0f);

	this->setTag("netPlayer");
	netRocket->setTag("netRocket");

	isDead = false;
	
	updateElapsed = 0;

	g_pCollisionObserver->addListener(this);
}

Netplayer::~Netplayer(){
	delete sprite;
	delete netRocket;
}

void Netplayer::CollisionDetected(TransformCollidable *other, Vector2 penetration){
	
}

void Netplayer::update(){
	updateElapsed += g_pTimer->getDeltaTime();
	float currentFraction = updateElapsed / EXPECTEDTICKRATE;
	float alpha = clamp(0.0f, 1.0f, currentFraction);

	Vector2 pos = lerp(backHistoryCache.pos, frontHistoryCache.pos, alpha);
	this->setPosition(pos);
	sprite->setPosition(pos);

	Vector2 forward = lerp(backHistoryCache.forward, frontHistoryCache.forward, alpha);
	this->setForward(forward);

	float angle = lerp(backHistoryCache.angle, frontHistoryCache.angle, alpha);
	sprite->setAngle(angle);

	this->isDead = frontHistoryCache.isDead;

	Vector2 rocketPos = lerp(backHistoryCache.rocketPos, backHistoryCache.rocketPos, alpha);
	Vector2 rocketForward = lerp(backHistoryCache.rocketForward, backHistoryCache.rocketForward, alpha);
	netRocket->update(rocketPos, rocketForward);

}

/*
void Netplayer::render(){

	netRocket->render();

}
*/

void Netplayer::updateNetData(Vector2 pos, Vector2 forward, float angle, Vector2 rocketPos, Vector2 rocketForward, bool isDead){
	
	backHistoryCache = frontHistoryCache;

	frontHistoryCache.pos = pos;
	frontHistoryCache.forward = forward;
	frontHistoryCache.angle = angle;
	frontHistoryCache.rocketPos = rocketPos;
	frontHistoryCache.rocketForward = rocketForward;
	frontHistoryCache.isDead = isDead;
	
	updateElapsed = 0;
}

void Netplayer::rocketDestroyed(){
	netRocket->update(Vector2(-100.0, -100.0), Vector2(0.0, 0.0));
}

bool Netplayer::getIsDead(){
	return isDead;
}