#pragma once

#include "Sprite.hpp"
#include "Transform.hpp"
#include "NetRocket.h"
#include "CollisionObserver.h"

class NetRocket;

class Netplayer : public TransformCollidable{
public:
	Netplayer();
	Netplayer(Vector2 position, Vector2 forward);
	
	~Netplayer();

	virtual void CollisionDetected(TransformCollidable *other, Vector2 penetration);

	void update(Vector2 pos, Vector2 forward, float angle, Vector2 rocketPos, Vector2 rocketForward);
	void render();

	void rocketDestroyed();

private:
	Sprite *sprite;
	NetRocket* netRocket;

};